#!/usr/bin/ruby

require 'fileutils'

### Script description ###

# For a given TPG (TPG/XXX in the hierarchy), using the SEED passed as input param,
# launch the program mainPreCalcul 
# See the corresponding README.md in TPG

def check_exit_status(code)
    if code != 0
      puts "\033[1;91mERROR\033[0m --- Something wrong happened, last exit code is #{code}, exiting script"
      exit 1
    end
end

def training_done?(d)
    training_dir = File.join(d, 'training')
    if File.directory?(training_dir)
      true
    else
      puts "\033[1;36mSkip #{d} \033[1;31m(training dir is missing)\033[0m\n"
      false
    end
end
  
def codegen_done?(d)
    codegen_dir = File.join(d, 'CodeGen')
    if File.directory?(codegen_dir)
      true
    else
      puts "\033[1;36mSkip #{d} \033[0m(CodeGen is missing)\n"
      false
    end
end

def precalcul_done?(d)
    precalcul_dir = File.join(d, 'PreCalcul')
    if File.directory?(precalcul_dir)
      puts "\033[1;36mSkip #{d} \033[0m(PreCalcul already done)\n"
      true
    else
      false
    end
end
  

### Script ###

# Check if script is called properly
if ARGV.length < 3
    puts "Usage: ruby script_name.rb <verbose: true/false> <seed> <name of TPG dir (default: \"TPG\")>"
    exit 1
end
  
# Convert the string input to boolean value for verbose
verbose = ARGV[0].casecmp('true').zero?

# Extract seed from command line argument
seed = ARGV[1].to_i

# Ensure the third argument is a non-empty string
TPG_dir = ARGV[2]
if TPG_dir.nil? || TPG_dir.strip.empty?
    puts "Error: The name of TPG dir must be a non-empty string."
    puts "Usage: ruby script_name.rb <verbose: true/false> <seed> <name of TPG dir (default: \"TPG\")>"
    exit 1
end
    

# move from the current dir to Trainer-Generator 
script_dir = File.expand_path(File.dirname(__FILE__))
Dir.chdir(File.join(script_dir, '..'))
check_exit_status($?.to_i)

# Trainer-Generator CMake configuration 
FileUtils.rm_r('Trainer-Generator/bin')
check_exit_status($?.to_i)

FileUtils.mkdir('Trainer-Generator/bin')
check_exit_status($?.to_i)

Dir.chdir('Trainer-Generator/bin')
check_exit_status($?.to_i)

`cmake ..`
check_exit_status($?.to_i)


# launch Cmake command
trainor_cmake_string = "cmake .."
unless (verbose)
  trainor_cmake_string += " > /dev/null 2>&1"
end
system(trainor_cmake_string)
check_exit_status($?.to_i)


# go to TPG dir
Dir.chdir("../../#{TPG_dir}") 
check_exit_status($?.to_i)


# Select directories for which there is a need to do CodeGen
dirs = Dir.entries('.').reject { |d| d == '.' || d == '..' || d == 'README.md'}

  
# check if the object is a dir, if training has been done 
# (required) and if codegen has as well already been done
dirs = dirs.reject do |d|
    if File.directory?(d) && training_done?(d) && !precalcul_done?(d) # codegen_done?(d)
        false
        #puts "Valid dir #{d}"
    else
        true #reject
    end
end


Dir.chdir('..') 
check_exit_status($?.to_i)


#Do PreCalcul
dirs.each do |d|
    # Be aware that folder name #{d} can cause encoding problems during the copy operation
    puts "\033[1;36mPrecalcul for #{d}\033[0m"

    # required files for inference on x86
    system("cp #{TPG_dir}/#{d}/src/instructions.cpp Trainer-Generator/src/")
    check_exit_status($?.to_i)
    system("cp #{TPG_dir}/#{d}/src/params.json Trainer-Generator/")
    check_exit_status($?.to_i)
  
    Dir.chdir('Trainer-Generator/bin') do

        trainor_cmake_string = "cmake"
        
        # Specify that we are doing Precalcul on int data type
        # the data needs to be scaled accordingly
        if d.include?('int')   
            trainor_cmake_string += " -DTYPE_INT=1 .."
        else
            trainor_cmake_string += " -DTYPE_INT=0 .."
        end

        unless (verbose)
            trainor_cmake_string += " > /dev/null 2>&1"
        end
        
        system(trainor_cmake_string)
        check_exit_status($?.to_i)

        trainor_compilation_string = "make PreCalcul"
        unless (verbose)
            trainor_compilation_string += " > /dev/null 2>&1"
        end

        system(trainor_compilation_string)
        check_exit_status($?.to_i)

        Dir.chdir('Release') do

            # Launch the PreCalcul of pairs {seed, nbActionsToTerminal}            
            system("./PreCalcul ../../../#{TPG_dir}/#{d}/training/best_root_training.dot #{seed}")# best root training
            check_exit_status($?.to_i)
            
            # Save the results of the Precalcul into the concerned TPG dir
            system("mv Results ../../../#{TPG_dir}/#{d}/PreCalcul")
            check_exit_status($?.to_i)
        
        end
    end
end
