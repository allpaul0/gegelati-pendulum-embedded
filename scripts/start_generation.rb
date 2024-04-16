#!/usr/bin/ruby

require 'fileutils'

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

def needs_codegen?(d)
  codegen_dir = File.join(d, 'CodeGen')
  if File.directory?(codegen_dir)
    puts "\033[1;36mSkip #{d} \033[0m(CodeGen already done)\n"
    false
  else
    true
  end
end

def create_CodeGen_dir(d)
  codegen_dir = File.join(d, 'CodeGen')
  Dir.mkdir(codegen_dir) unless Dir.exist?(codegen_dir)
  rescue => e
    puts "Error creating CodeGen directory: #{e.message}"
end



### Script ###

# Check if script is called properly
if ARGV.empty?
  puts "Usage: ruby script_name.rb <value of verbose (true/false)>"
  exit 1
end

# Convert the string input to a boolean value
verbose = ARGV[0].casecmp('true').zero?


# Move to TPG dir
script_dir = File.expand_path(File.dirname(__FILE__))
Dir.chdir(File.join(script_dir, '..', 'TPG'))


# CMake configuration
FileUtils.rm_r('../Trainer-Generator/bin')
check_exit_status($?.to_i)
Dir.mkdir('../Trainer-Generator/bin')
check_exit_status($?.to_i)

trainor_compilation_string = "cmake -S ../Trainer-Generator -B ../Trainer-Generator/bin"
unless (verbose)
  trainor_compilation_string += " > /dev/null 2>&1"
end
system(trainor_compilation_string)
check_exit_status($?.to_i)


# Select directories for which there is a need to do CodeGen
dirs = Dir.entries('.').reject { |d| d == '.' || d == '..' }
  
# check if the object is a dir, if training has been done 
# (required) and if codegen has not already been done
dirs = dirs.reject do |d|
  if File.directory?(d) && training_done?(d) && needs_codegen?(d)
    false
  else
    true
  end
end


# Do CodeGen
dirs.each do |d|
  puts "\033[1;36mGenerating CodeGen for #{d}\033[0m"

  # Using Generator target of the Trainer-Genertor C++ project
  create_CodeGen_dir(d)

  # Copying instructions.cpp
  system("cp #{d}/src/instructions.cpp ../Trainer-Generator/src/")
  check_exit_status($?.to_i)

  # Copying params.json necessary for nbRegisters nbConstants in the Generator
  system("cp #{d}/src/params.json ../Trainer-Generator/")
  check_exit_status($?.to_i)

  # Building target
  system('cmake --build ../Trainer-Generator/bin --target Generator')
  check_exit_status($?.to_i)

  # Do code generation
  system("../Trainer-Generator/bin/Release/Generator #{d}/training/out_best.dot")
  check_exit_status($?.to_i)

  puts "\033[1;36mSuccessful code generation for #{d}\033[0m\n"
end
  