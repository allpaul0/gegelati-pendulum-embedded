#!/usr/bin/ruby

# Built-in gems
require 'fileutils'
require 'optparse'
require 'json'
require 'timeout'

require 'serialport'

require_relative 'scripts/instructionLevelLogToJson'
require_relative 'scripts/graphLevelLogToJson'


C_UINT_MAX = 4294967295     # C language max unsigned int constant value from limits.h

# =====[ Script parameters ]=====

# Change these parameters ONLY if you want to change the default values, otherwise use the script command line arguments.


# Path to the serial port corresponding to the STM32 board
serialPortPath = nil

# Set to true if you want to display generated graphs. Image files will still be generated.
showGraph = false

# Set to true if you want to give all TPGs during measurement the same seed, and thus the same inital conditions
sameSeed = false

# Prefix used for result directories (Measure stage)
resultDirPrefix = Time.now.strftime("%Y-%m-%d_%H-%M-%S")

# Only used if sameSeed parameter is true
common_seed = rand(C_UINT_MAX)

# will display information about compilation, execution, ...
verbose = false

# will display acions of pendulum 
pendulumTrace = 0 

# will perform instruction level analysis
instructionLevelAnalysis = 0

# will perform graph level analysis
graphLevelAnalysis = 0

# ===============================

def check_serial_ports
    available_port = nil

    # Iterate over possible ports (assuming only one port can be available)
    (0..9).each do |index|
        port = "/dev/ttyACM#{index}"
        if File.exist?(port)
            available_port = port
            #puts "#{port} exists."
            break  # Exit loop early since we found the port
        #else
            #puts "#{port} does not exist."
        end
    end

    available_port  # Return the available port, or nil if not found
end


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

def synchronize_with_stm32(serialPortPath, resultPath, logFile, verbose)
    attempts = 0
    max_attempts = 2

    available_port = check_serial_ports

    # Check if available_port is nil and exit the function if so
    if available_port.nil?
    puts "No serial port available. Exiting function."
    return  # This will exit the current function or method
    end
    
    while attempts < max_attempts
        attempts += 1
        first_attempt = (attempts == 1)

        SerialPort.open(serialPortPath, baud = 115200) do |serialport|

            begin
                Timeout.timeout(2) do
                    if first_attempt
                        until (serialport.readline == "START\r\n") do end   # Waiting for STM32 to send the first signal (SYN)
                    end
                end
                serialport << "\n"  # Sending back to the STM32 a newline character (ACK), which will start the inference
                return true  # Exit the method once synchronization is successful
            rescue Timeout::Error
                if attempts < max_attempts
                    puts "\033[0;33mSynchronization failed. Retrying...\033[0m"
                else
                    puts "\033[0;31mSynchronization failed. Timed out after #{attempts} attempts.\033[0m"
                    puts "\033[0;31mDeleting generated results dir.\033[0m"

                    # Delete the generated incomplete directory since its presence will be an obstacle for 
                    # the rest of the script and it has no meaningful information
                    logFile.close
                    system("rm #{resultPath}/energy.log")
                    system("rmdir #{resultPath}")
                    exit 1
                end
            end
            
        end
    end
end


# =====[ Program arguments managment ]=====

# CodeGen : generate CodeGen files for all TPG .dot files in valid subdirectories of the #{TPG_dir}
# Measure : compile, load and run measurements on the STM32 board, and store results, for all valid subdirectories of #{TPG_dir}
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

    parser.on("--pendulum_trace", "set the preprocessor directive PENDULUM_TRACE=1, will print action of pendulum"){
        pendulumTrace = 1
    }

    parser.on("--instruction_level_analysis", "set the preprocessor directive INSTRUCTION_LEVEL_ANALYSIS=1, will measure 
        at instruction level"){
        instructionLevelAnalysis = 1
    }

    parser.on("--graph_level_analysis", "set the preprocessor directive GRAPH_LEVEL_ANALYSIS=1, will measure 
        at graph level"){
        graphLevelAnalysis = 1
    }

    parser.on("-v", "verbose"){
        verbose = true;
    }
    
}.parse!

# Ensure TPG_dir is provided
if ARGV.empty?
  puts "Error: TPG_dir must be provided."
  puts "Usage: startAllEnergyBenches.rb [options] TPG_dir"
  exit(1)
else
  TPG_dir = ARGV.shift
end

# Debugging information if verbose
if verbose
  puts "Serial Port: #{serialPortPath}"
  puts "Stages: #{stages}"
  puts "Show Graph: #{showGraph}"
  puts "Same Seed: #{sameSeed}"
  puts "Common Seed: #{common_seed}" if common_seed
  puts "Result Dir Prefix: #{resultDirPrefix}"
  puts "TPG_dir: #{TPG_dir}"
  puts "pendulum trace : #{pendulumTrace}"
  puts "instruction-level analysis : #{instructionLevelAnalysis}"
  puts "graph-level analysis : #{graphLevelAnalysis}" 
end



Dir.chdir "#{__dir__}"  # Set current script current directory, so we can execute it from everywhere


# =====[ CodeGen stage ]=====

if stages["CodeGen"]
    
    puts "\033[1;32m=====[ CodeGen stage ]=====\033[0m"
    puts TPG_dir

    system("./scripts/start_code_generation.rb #{verbose} #{TPG_dir}")
    checkExitstatus("start_generation")

end



# =====[ Measurements stage ]=====

if stages["Measures"]

    puts "\033[1;32m=====[ Measurements stage ]=====\033[0m"

    requiredFiles = ["CodeGen/src/TPGGraph.c", "CodeGen/src/TPGGraph.h", "CodeGen/src/TPGPrograms.c", "CodeGen/src/TPGPrograms.h"]
    valid_TPG_directories = getValidDirectories("#{TPG_dir}", requiredFiles)

    if valid_TPG_directories.empty?
        puts "\033[0;31mError: There are no valid #{TPG_dir} subdirectories. Please verify the content of your /#{TPG_dir} folder."
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
    
    # Compiling, flashing on STM32, do inference and analyze results for each TPG

    sample_size = {}
    ratioInterruptCompute = {}

    executionTime = {}
    executionTimeUnit = {}
    stdDevExecutionTime = {}

    energyConsumption = {}
    energyConsumptionUnit = {}
    stdDevEnergyConsumption = {}
    

    valid_TPG_directories.each do |tpgDirName|
        
        puts "\033[1;33m#{tpgDirName}\033[0m"
      
        # === Moving file for cross-compilation ===
      
        # Source files
        dest = "PendulumEmbeddedSTMProject/Core/Src/Pendulum/."
        ["TPGGraph.c", "TPGPrograms.c"].each do |f|
            src = "#{tpgDirName}/CodeGen/src/#{f}"
            system("cp #{src} #{dest}")
            checkExitstatus("cp src dest Measures 1")
        end
      
        # Header files
        dest = "PendulumEmbeddedSTMProject/Core/Inc/Pendulum/."
        ["TPGGraph.h", "TPGPrograms.h"].each do |f|
            src = "#{tpgDirName}/CodeGen/src/#{f}"
            system("cp #{src} #{dest}")
            checkExitstatus("cp src dest Measures 2")
        end

        system("cp #{tpgDirName}/PreCalcul/seeds_nbActionsToTerminal.h PendulumEmbeddedSTMProject/Core/Inc/Pendulum/.")
            
        # === Compiling executable ===
      
        seed = sameSeed ? common_seed : rand(C_UINT_MAX)
      
        # Set the seed value and inform the compiler whether we are using INT or not
        type_int = tpgDirName.include?("int") ? 1 : 0
      
        system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DTYPE_INT=[0-9][0-9]*/-DTYPE_INT=#{type_int}/g' {} +")
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i TYPE_INT")

        # display changes
        #system("grep -r -n -H "TYPE_INT" PendulumEmbeddedSTMProject")

        system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DPENDULUM_TRACE=[0-9][0-9]*/-DPENDULUM_TRACE=#{pendulumTrace}/g' {} +")
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i PENDULUM_TRACE")

        system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DINSTRUCTION_LEVEL_ANALYSIS=[0-9][0-9]*/-DINSTRUCTION_LEVEL_ANALYSIS=#{instructionLevelAnalysis}/g' {} +")
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i INSTRUCTION_LEVEL_ANALYSIS")

        system("find PendulumEmbeddedSTMProject -type f -exec sed -i 's/-DGRAPH_LEVEL_ANALYSIS=[0-9][0-9]*/-DGRAPH_LEVEL_ANALYSIS=#{graphLevelAnalysis}/g' {} +")
        checkExitstatus("find PendulumEmbeddedSTMProject sed -i GRAPH_LEVEL_ANALYSIS")

      
        puts "\tCompilation of the embedded binary"
      
        embedded_binary_compilation_string = "make clean -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench" 
        embedded_binary_compilation_string += " > /dev/null 2>&1" unless verbose
        embedded_binary_compilation_string +=" && make -j20 all -C ./PendulumEmbeddedSTMProject/ReleaseEnergyBench"
        embedded_binary_compilation_string += " > /dev/null 2>&1" unless verbose
      
        system(embedded_binary_compilation_string)
        checkExitstatus("make all -C CodeGen")
      
        # Moving .elf binary to the current TPG subdirectory
        srcElf = "PendulumEmbeddedSTMProject/ReleaseEnergyBench/PendulumEmbeddedSTMProject.elf"
        destElf = "#{tpgDirName}/CodeGen"
        FileUtils.cp(srcElf, destElf)
        checkExitstatus("cp srcElf, destElf")

        # === Loading program on STM32 flash memory ===
      
        puts "\tLoading the binary"
      
        embedded_binary_loading_string = "STM32_Programmer_CLI -c port=SWD -w #{destElf}/PendulumEmbeddedSTMProject.elf -rst"
        embedded_binary_loading_string += " > /dev/null 2>&1" unless verbose
        system(embedded_binary_loading_string)
        checkExitstatus("STM32_Programmer_CLI")
      
        # === Start serial interface and inference ===
      
        puts "\tInference on the board"
      
        # Create subdirectory to save results
        inferencePath = "#{tpgDirName}/inference"
        Dir.mkdir(inferencePath) unless Dir.exist?(inferencePath)
      
        resultPath = "#{inferencePath}/#{resultDirPrefix}"
        FileUtils.mkdir(resultPath)
        checkExitstatus("mkdir resultPath timestamp")
      
        # energy.log stores messages received from the STM32 board
        logPath = "#{resultPath}/energy.log"
        dataPath = "#{resultPath}/energy_data.json"
        logFile = File.open(logPath, "w+");

        serialPortPath = check_serial_ports

        # Check if available_port is nil and exit the function if so
        if serialPortPath.nil?
        puts "No serial port available. Exiting function."
        return  # This will exit the current function or method
        end
        
        # Main execution starts here
        synchronize_with_stm32(serialPortPath, resultPath, logFile, verbose)

        continue = true
        
        SerialPort.open(serialPortPath, baud = 115200) do |serialport|
            while continue
                line = serialport.readline
                
                if verbose
                    puts line   
                end
                logFile << line
                
                continue = (line != "END\r\n")
            end
        end        


        logFile.close

        # Convert log file to JSON
        if instructionLevelAnalysis == 1
            dataJson = instructionLevelLogToJson(logPath, dataPath, seed)

            # Store summary values
            tpgDirName = tpgDirName.to_s  # Convert to string if necessary
            sample_size[tpgDirName] = dataJson["summary"]["parameters"]["nbSamples"]
            ratioInterruptCompute[tpgDirName] = dataJson["summary"]["overall"]["ratioInterruptCompute"]
            
            executionTime[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionExecutionTime"]
            executionTimeUnit[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionExecutionTimeUnit"]
            stdDevExecutionTime[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionstdDevExecutionTime"]

            energyConsumption[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionEnergyConsumption"]
            energyConsumptionUnit[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionEnergyConsumptionUnit"]
            stdDevEnergyConsumption[tpgDirName] = dataJson["summary"]["singleInstruction"]["singleInstructionstdDevEnergyConsumption"]
        else 
            dataJson = graphLevelLogToJson(logPath, dataPath)
        end
    end
    
    if instructionLevelAnalysis == 1
        # Displaying global results
        puts "\033[1;32m=====[ Instruction-level Analysis summary ]=====\033[0m"
        valid_TPG_directories.sort.each do |tpgDirName|
            puts "\033[1;33m#{tpgDirName}\033[0m"
            puts "\tSample size: #{sample_size[tpgDirName]}"
            puts "\tInstruction execution time : \033[0;35m#{executionTime[tpgDirName]}+-#{stdDevExecutionTime[tpgDirName]} #{executionTimeUnit[tpgDirName]}\033[0m"
            puts "\tInstruction energy consumption : \033[1;32m#{energyConsumption[tpgDirName]}+-#{stdDevEnergyConsumption[tpgDirName]} #{energyConsumptionUnit[tpgDirName]}\033[0m"
            puts "\tRatio Measure/Compute : #{ratioInterruptCompute[tpgDirName]}%"
        end
    end
end




# =====[ Analysis stage ]=====

if stages["Analysis"]

    puts "\033[1;32m=====[ Analysis stage ]=====\033[0m"

    Dir.glob("#{TPG_dir}/*/inference/*")
    .filter { |d| not File.exist? "#{d}/executionStats.json" }  # if the file executionStats.json exists, the processing has already been done in the past  
    .filter { |d| File.exist? "#{d}/energy_data.json" }  # make sure the file energy_data.json exists
    .each { |d|

        match = d.match("#{TPG_dir}\/(.*?)\/inference")
        directory = "#{TPG_dir}/" + match[1] if match
        
        puts "\033[1;33m#{directory}\033[0m"

        srcPath = "#{directory}/src"
        srcPathInstr = "#{srcPath}/instructions.cpp"
        srcPathParams = "#{srcPath}/params.json"
        codegenPath = "#{directory}/CodeGen"
        destPath = "Trainer-Generator/."
        destPathSrc = "Trainer-Generator/src/."


        # Copying required files for generating Executions stats            
        FileUtils.cp("#{srcPathInstr}", "#{destPathSrc}")
        checkExitstatus("cp src dest ExecutionStats1")
        FileUtils.cp("#{srcPathParams}", "#{destPath}")
        checkExitstatus("cp src dest ExecutionStats2")

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

        system("./Trainer-Generator/bin/Release/ExecutionStats #{codegenPath}/best_root_pruned.dot #{energyData["metadata"]["startAngle"]} #{energyData["metadata"]["startVelocity"]}")
        checkExitstatus("./ExecutionStats")

        # Move executions_stats.json to result directory
        FileUtils.mv("#{codegenPath}/executionStats.json", "#{d}")
    }

end


# =====[ Plot results stage ]=====

if stages["PlotResults"]
    
    puts "\033[1;32m=====[ PlotResults stage ]=====\033[0m"
    
    execution_stats_string = "julia --project ./scripts/generate_energy_plots.jl"
    if showGraph
        execution_stats_string += " --show"        
    end
    system(execution_stats_string)
    checkExitstatus("julia generate_energy_plots.jl")
end
