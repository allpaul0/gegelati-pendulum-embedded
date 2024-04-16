#!/usr/bin/ruby

# Built-in gems
require 'fileutils'
require 'optparse'
require 'json'
require 'timeout'

require 'serialport'

require_relative 'scripts/logToJson'


C_UINT_MAX = 4294967295     # C language max unsigned int constant value from limits.h

# =====[ Script parameters ]=====

# Change these parameters ONLY if you want to change the default values, otherwise use the script command line arguments.


# Path to the serial port corresponding to the STM32 board
serialPortPath = "/dev/ttyACM0"

# Set to true if you want to display generated graphs. Image files will still be generated.
showGraph = false

# Set to true if you want to give all TPGs during measurement the same seed, and thus the same inital conditions
sameSeed = false

# Prefix used for result directories (Measure stage)
resultDirPrefix = Time.now.strftime("%Y-%m-%d_%H-%M-%S")

# Only used if sameSeed parameter is true
common_seed = rand(C_UINT_MAX)

#will display information about compilation, execution, ...
verbose = false

# ===============================



# Get all subdirectories of dir that contained all the required files, given as an array of relative path from dir/subdirectory/.
#
# The returned array contains relative paths from dir for all valid subdirectories.
def getValidDirectories (dir, requiredFiles)

    valid_TPG_directories = []  # Store all subdirectories path containing the required TPG CodeGen files
    Dir.open(dir) { |d|

        d.each_child { |child|
            tpgDirName = d.path + '/' + child
            
            if File.directory? tpgDirName

                # Condition return the first missing file, otherwise nil is returned
                missing_file = requiredFiles.find { |f| not File.exist? "#{tpgDirName}/#{f}" }
                
                if missing_file.nil?
                    valid_TPG_directories << tpgDirName
                else
                    puts "Missing file in #{tpgDirName}: #{missing_file}"
                end

            end
        }

    }

    return valid_TPG_directories

end

# Exit the script with an error message if the last call to a subprocess returns an exit code different from 0
def checkExitstatus(error_message)
    if  $?.nil? || $?.exitstatus != 0
        puts "Exit point: #{error_message}"
        exit 1
    end
end


# =====[ Program arguments managment ]=====

# CodeGen : generate CodeGen files for all TPG .dot files in valid subdirectories of TPG/
# Measure : compile, load and run measurements on the STM32 board, and store results, for all valid subdirectories of TPG/
# AnalyzeExecutions : from the measurement results, compute new data and export statistics about the execution that has been measured
# PlotResults : take all statistics from the previous step and render graphs and plots using julia script and module PlotlyJS 
# Skip multiple phases
# $./startAllEnergyBenches.rb --skip CodeGen --skip Analysis --skip PlotResults --same-seed 0

# If false, the step is skipped
stages = { "CodeGen" => true, "Measures" => true, "Analysis" => true, "PlotResults" => true}


OptionParser.new{ |parser|

    parser.on("-p PORT", "--port PORT", "tty device of the serial port (default is #{serialPortPath})"){ |port|
        serialPortPath = port
    }

    parser.on("--skip STAGE", "don't execute a specific stage in : #{stages.keys.join(", ")}"){ |to_skip|
        if stages.key?(to_skip)
            stages[to_skip] = false
            puts "Skipping stage #{to_skip}"
        else
            puts "Unknown stage #{to_skip}"
        end
    }

    parser.on("--show", "open all generated plots in browser"){
        showGraph = true
    }

    parser.on("--same-seed [SEED]", "use the same seed for each measures (i.e. same initial conditions for all TPGs), if no seed is given, generate one randomly"){ |seed|
        common_seed = seed unless seed.nil?
        sameSeed = true;
    }

    parser.on("--prefix PREFIX", "set a custom prefix for the result directories (Measure stage), must not contain any whitespace or /. Default is the current time with the format YYYY-MM-DD_HH-MM-SS"){ |prefix|
        resultDirPrefix = prefix
    }

    parser.on("-h", "--help", "print this message"){
        puts parser
        exit
    }

    parser.on("-v", "verbose"){
        verbose = true;
    }
    
}.parse!



Dir.chdir "#{__dir__}"  # Set current script current directory, so we can execute it from everywhere


# =====[ CodeGen stage ]=====

if stages["CodeGen"]
    
    puts "\033[1;32m=====[ CodeGen stage ]=====\033[0m"

    system("./scripts/start_generation.rb #{verbose}")
    checkExitstatus("start_generation")

end


# =====[ Measurments stage ]=====

if stages["Measures"]

    puts "\033[1;32m=====[ Measurments stage ]=====\033[0m"

    requiredFiles = ["CodeGen/TPGGraph.c", "CodeGen/TPGGraph.h", "CodeGen/TPGprograms.c", "CodeGen/TPGprograms.h"]
    valid_TPG_directories = getValidDirectories("TPG", requiredFiles)

    if valid_TPG_directories.empty?
        puts "\033[0;31mError: There are no valid TPG subdirectories. Please verify the content of your /TPG folder."
        puts "\033[0;31mEnsure that it respects the structure described in: https://github.com/allpaul0/gegelati-pendulum-embedded/tree/master/TPG/README.md"
        exit 1
    else 
        puts "Valid TPG subdirectories are #{valid_TPG_directories}"
    end

    # Add ARM g++ compiler to the path if not set yet
    # Passing the compiler to the PATH is necessary for reproducing the build from STM32CubeIDE
    # Otherwise, we get "arm-none-eabi-g++: error: unrecognized command-line option '-fcyclomatic-complexity'"

    new_path = "/opt/st/stm32cubeide_1.13.2/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.linux64_1.1.1.202309131626/tools/bin"
    existing_path = ENV["PATH"] || ""

    # Check if the new path is already included in the PATH variable
    unless existing_path.split(File::PATH_SEPARATOR).include?(new_path)
    # Add the new path before the existing PATH variable
    ENV["PATH"] = "#{new_path}#{File::PATH_SEPARATOR}#{existing_path}"
    end

    # Compiling, flashing on STM32, do inference and analyse results for each TPG

    currentAvgs = {}
    powerAvgs = {}
    executionTimeAvgs = {}
    timeUnits = {}
    totalEnergyConsumption = {}
    ratioInterruptCompute = {}

    
    valid_TPG_directories.each { |tpgDirName|

        puts "\033[1;33m#{tpgDirName}\033[0m"

        # === Moving file for cross-compilation ===

        # Source files
        dest = "PendulumEmbeddedSTMProject/Core/Src/Pendulum"
        ["TPGGraph.c", "TPGprograms.c"].each { |f|
            
            src = "#{tpgDirName}/CodeGen/#{f}"
            FileUtils.cp(src, dest)
            checkExitstatus("cp src dest Measures")
        }

        # Header files
        dest = "PendulumEmbeddedSTMProject/Core/Inc/Pendulum"
        ["TPGGraph.h", "TPGprograms.h"].each { |f|

            src = "#{tpgDirName}/CodeGen/#{f}"
            FileUtils.cp(src, dest)
            checkExitstatus("cp src dest Measures")
        }

        # === Compiling executable ===

        seed = sameSeed ? common_seed : rand(C_UINT_MAX)

        # Set the seed value and inform the compiler whether we are using INT or not

        if tpgDirName.include?("int")
            system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DTYPE_INT=[0-9][0-9]*/-DTYPE_INT=1/g' {} +")
        else
            system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DTYPE_INT=[0-9][0-9]*/-DTYPE_INT=0/g' {} +")
        end
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i TYPE_INT")

        system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DTPG_SEED=[0-9][0-9]*/-DTPG_SEED=#{seed}/g' {} +")
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i TPG_SEED")

        #system("find PendulumEmbeddedSTMProject -type f -exec grep -Hn -- \"-DTYPE_INT=[0-9][0-9]*\" {} +")
        #checkExitstatus("find PendulumEmbeddedSTMProject grep")

        # display changes
        #find PendulumEmbeddedSTMProject -type f -exec grep -Hn -- "-DTYPE_INT=[0-9][0-9]*" {} +
        #find PendulumEmbeddedSTMProject -type f -exec grep -Hn -- "-DTPG_SEED=[0-9][0-9]*" {} +

        puts "\tCompilation of the embedded binary"

        # Usefull compilation bash commands
        # make clean -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench //clean repo
        # make -j20 all -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench //build repo
        # -j20 = 20 jobs; 
    
        # No matter the TPG, the program on the STM32 will always initialise itself the same 
        # way and its random number generator too.
        # We want the TPGs to have a random initial state, so the seed used to initialise 
        # it is geerated via this ruby script.
        
        embedded_binary_compilation_string = "make clean -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench |make -j20 all -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench"

        if(!verbose)
            embedded_binary_compilation_string += " > /dev/null 2>&1"
        end

        system(embedded_binary_compilation_string)

        checkExitstatus("make all -C CodeGen")
    
        # Moving .elf binary to the current TPG subdirectory
        srcElf = "PendulumEmbeddedSTMProject/ReleaseEnergyBench/PendulumEmbeddedSTMProject.elf"
        destElf = "#{tpgDirName}/CodeGen"
        FileUtils.cp(srcElf, destElf)
    
    
        # === Loading program on STM32 flash memory ===

        #puts "\033[1;32m\t- Loading the binary\033[0m"
        puts "\tLoading the binary"

        # Loading is done using the program STM32_Programer_CLI
        embedded_binary_loading_string = "STM32_Programmer_CLI -c port=SWD -w #{destElf}/PendulumEmbeddedSTMProject.elf -rst"
        if(!verbose)
            embedded_binary_loading_string += " > /dev/null 2>&1"
        end
        system(embedded_binary_loading_string) # c: connect | rst: reset system
        checkExitstatus("STM32_Programmer_CLI")
    

        # === Start serial interface and inference ===

        #puts "\033[1;32m\t- Inference on the board\033[0m"
        puts "\tInference on the board"

        # Create subdirectory to save results
        inferencePath = "#{tpgDirName}/inference"
        unless Dir.exist?("#{inferencePath}")
            Dir.mkdir(inferencePath)
        end
        resultPath = "#{inferencePath}/#{resultDirPrefix}" # a timestamp marks the identity of the folder containing the data
        FileUtils.mkdir(resultPath)
        checkExitstatus("mkdir resultPath timestamp")

        # energy.log stores messages received from the STM32 board
        logPath = "#{resultPath}/energy.log"
        logFile = File.open(logPath, "w+");

        SerialPort.open(serialPortPath, baud = 115200) { |serialport|

            # The ruby script synchronizes with the STM32 using a periodic retry on the board

            begin
                Timeout.timeout(10) do
                until (serialport.readline == "START\r\n") do end   # Waiting for STM32 to send the first signal (SYN)
                serialport << "\n"  # Sending back to the STM32 a newline character (ACK), which will start the inference

                continue = true
                while continue
                    line = serialport.readline
        
                    if(verbose)
                        puts line   
                    end
                    logFile << line
        
                    continue = (line != "END\r\n")
                end
            end
            rescue Timeout::Error
                puts "\033[0;31mSynchronization failed. Timed out after 10 seconds.\033[0m"
                puts "\033[0;31mDeleting generated results dir.\033[0m"
                
                # Delete the generated incomplete directory since its presence will be an obstacle for 
                # the rest of the script and it has no meaningfull informations
                logFile.close
                system("rm #{resultPath}/energy.log")
                system("rmdir #{resultPath}")
                exit 1
            end
        }

        logFile.close
    
    
        # === Extract and export meaningfull data from log file ===
    
        dataPath = "#{resultPath}/energy_data.json"
        dataJson = logToJson(logPath, dataPath, seed)

        currentAvgs[tpgDirName] = dataJson["summary"]["averageCurrent"]
        powerAvgs[tpgDirName] = dataJson["summary"]["averagePower"]
        executionTimeAvgs[tpgDirName] = dataJson["summary"]["executionTavg"]
        totalEnergyConsumption[tpgDirName] = dataJson["summary"]["totalEnergy"]
        ratioInterruptCompute[tpgDirName] = dataJson["summary"]["ratioInterruptCompute"]
    }



    # Displaying global results

    puts "\033[1;32m=====[ Measurement summary ]=====\033[0m"

    valid_TPG_directories.sort!.each { |tpgDirName|
        #puts "#{tpgDirName}"
        puts "\033[1;33m#{tpgDirName}\033[0m"
        puts "\tAverage current : #{(currentAvgs[tpgDirName] * 1000).round(4)} mA"
        puts "\tAverage power : #{powerAvgs[tpgDirName].round(4)} W"
        puts "\tAverage step execution time : \033[0;35m#{executionTimeAvgs[tpgDirName]}\033[0m"
        puts "\tTotal energy consumption : \033[1;32m#{(totalEnergyConsumption[tpgDirName] * 1000).round(4)} mJ\033[0m"
        puts "\tRatio Measure/Compute : #{ratioInterruptCompute[tpgDirName]}"
    }

end



# =====[ Analysis stage ]=====

if stages["Analysis"]

    puts "\033[1;32m=====[ Analysis stage ]=====\033[0m"

    Dir.glob("TPG/*/inference/*")
        .filter { |d| not File.exist? "#{d}/executionStats.json" }  # if the file executionStats.json exists, the processing has already been done in the past  
        .filter { |d| File.exist? "#{d}/energy_data.json" }  # make sure the file energy_data.json exists
        .each { |d|

            match = d.match(/TPG\/(.*?)\/inference/)
            directory = "TPG/" + match[1] if match
            
            srcPath = "#{d}/../../src"
            trainingPath= "#{d}/../../training"

            # Copying required files for generating Executions stats
            puts "\033[1;33m#{directory}\033[0m"
            FileUtils.cp("#{srcPath}/instructions.cpp", "Trainer-Generator/src")
            FileUtils.cp("#{srcPath}/params.json", "Trainer-Generator")
            checkExitstatus("cp src dest ExecutionStats")

            Dir.chdir('Trainer-Generator/bin') do

                if d.include?('int')
                    # Specify that we are training on int data type
                    # the data needs to be scaled accordingly
                    system("cmake ExecutionStats .. -DTYPE_INT=1 > /dev/null 2>&1")
                    checkExitstatus("cmake -DTYPE_INT=1 ..")
                else
                    system("cmake -DTYPE_INT=0 .. > /dev/null 2>&1")
                    checkExitstatus("cmake ExecutionStats -DTYPE_INT=0")
                end


                # CMake ExecutionStats target compilation
                execution_stats_compilation_string = "make ExecutionStats"
                if(!verbose)
                    execution_stats_compilation_string += " > /dev/null 2>&1"
                end
                system(execution_stats_compilation_string)
                checkExitstatus("make ExecutionStats")
            end

                # Get initial values from results of the energy bench
                energyData = {}
                File.open("#{d}/energy_data.json") { |io| energyData = JSON.load(io) }
            
                # Start replay and execution stats export for 1000 inferences

                system("./Trainer-Generator/bin/Release/ExecutionStats #{trainingPath}/out_best.dot #{energyData["metadata"]["startAngle"]} #{energyData["metadata"]["startVelocity"]}")
                checkExitstatus("./ExecutionStats")

                # Move executions_stats.json to result directory
                FileUtils.mv("#{trainingPath}/executionStats.json", "#{d}")
        }

end


# =====[ Plot results stage ]=====

if stages["PlotResults"]
    
    puts "\033[1;32m=====[ PlotResults stage ]=====\033[0m"
    
    if showGraph
        system("julia --project ./scripts/generate_energy_plots.jl --show")
        checkExitstatus("julia generate_energy_plots.jl --show")
    else
        system("julia --project ./scripts/generate_energy_plots.jl")
        checkExitstatus("julia generate_energy_plots.jl")
    end
end
