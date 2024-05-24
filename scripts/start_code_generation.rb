#!/usr/bin/ruby

require 'fileutils'

### Script description ###

# For a given TPG (TPG/XXX in the hierarchy), start the CodeGen if this TPG hasn't been 
# instrumented, pruned and generated for inference yet.
# Which means that the repo doesn't contain a "CodeGen" subdir)
# See the corresponding README.md in TPG


### Functions ###

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
      puts "\033[1;36mSkip #{d} \033[0m(CodeGen already done)\n"
      true
    else
      
      false
    end
end
  

### Script ###

# Check if script is called properly, using a verbose param
if ARGV.empty?
    puts "Usage: ruby script_name.rb <value of verbose (true/false)>"
    exit 1
end
  
# Convert the string input to a boolean value
verbose = ARGV[0].casecmp('true').zero?

# hardcoded for tracability
seed = 0

# move from the current dir to root dir
# used to get the absolute path of the directory containing the current script.
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


# launch Cmake command
trainor_compilation_string = "cmake .."
unless (verbose)
  trainor_compilation_string += " > /dev/null 2>&1"
end
system(trainor_compilation_string)
check_exit_status($?.to_i)


# go to TPG dir
Dir.chdir('../../TPG') 
check_exit_status($?.to_i)


# Select directories for which there is a need to do CodeGen
dirs = Dir.entries('.').reject { |d| d == '.' || d == '..' || d == 'README.md'}
  
# check if the object is a dir, if training has been done 
# (required) and if codegen has not already been done
dirs = dirs.reject do |d|
    if File.directory?(d) && training_done?(d) && !codegen_done?(d)
        false
        puts "Valid dir #{d}"
    else
        true #reject
    end
end

Dir.chdir('..') 
check_exit_status($?.to_i)

#Do CodeGen
dirs.each do |d|
    # Be aware that folder name #{d} can cause encoding problems during the copy operation
    puts "\033[1;36mGenerating CodeGen for #{d}\033[0m"

    # required files for codegen
    system("cp TPG/#{d}/src/instructions.cpp Trainer-Generator/src/")
    check_exit_status($?.to_i)
    system("cp TPG/#{d}/src/params.json Trainer-Generator/")
    check_exit_status($?.to_i)
  
    Dir.chdir('Trainer-Generator/bin') do

        trainor_compilation_string = "cmake"
        
        # Specify that we are doing CodeGen on int data type
        # the data needs to be scaled accordingly
        if d.include?('int')   
            trainor_compilation_string += " -DTYPE_INT=1 .."
        else
            trainor_compilation_string += " -DTYPE_INT=0 .."
        end

        unless (verbose)
            trainor_compilation_string += " > /dev/null 2>&1"
        end
        
        system(trainor_compilation_string)
        check_exit_status($?.to_i)

        system("make Generator")
        check_exit_status($?.to_i)

        Dir.chdir('Release') do

            # Launch the CodeGen            
            system("./Generator ../../../TPG/#{d}/training/best_root_training.dot #{seed}")
            check_exit_status($?.to_i)
            puts
            
            # Save the results of the CodeGen into the concerned TPG dir
            system("mv Results ../../../TPG/#{d}/CodeGen")
            check_exit_status($?.to_i)
        
        end
    end
end
