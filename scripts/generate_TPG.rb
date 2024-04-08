#!/usr/bin/ruby

require 'fileutils'

def check_exit_status(code)
  if code != 0
    puts "\033[1;91mERROR\033[0m --- Something wrong happened, last exit code is #{code}, exiting script"
    exit 1
  end
end
  
def valid_directory?(d)
  return false unless File.directory?(d)
  
  return false if Dir.glob(File.join(d, 'CodeGen', '*.c')).any?
  return false if Dir.glob(File.join(d, 'CodeGen', '*.h')).any?
  return false unless File.exist?(File.join(d, 'src', 'instructions.cpp'))
  return false unless File.exist?(File.join(d, 'src', 'params.json'))
  return false unless File.exist?(File.join(d, 'training', 'out_best.dot'))

  true
end

def create_CodeGen_dir(d)
  codegen_dir = File.join(d, 'CodeGen')
  Dir.mkdir(codegen_dir) unless Dir.exist?(codegen_dir)
  rescue => e
    puts "Error creating CodeGen directory: #{e.message}"
end

#check if script is called properly
if ARGV.empty?
  puts "Usage: ruby script_name.rb <value of verbose (true/false)>"
  exit 1
end

# Convert the string input to a boolean value
verbose = ARGV[0].casecmp('true').zero?

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

dirs = Dir.entries('.').reject { |d| d == '.' || d == '..' }
  
dirs.each do |d|
  if valid_directory?(d)
    puts "\033[1;36mGenerating CodeGen for #{d}\033[0m"

    # Using Generator target of the Trainer-Genertor C++ project
    create_CodeGen_dir(d)

    # Copying files
    system("cp #{d}/src/instructions.cpp ../Trainer-Generator/src/")
    check_exit_status($?.to_i)

    # Building target
    system('cmake --build ../Trainer-Generator/bin --target Generator')
    check_exit_status($?.to_i)
    puts

    # Do code generation
    system("../Trainer-Generator/bin/Release/Generator #{d}/training/out_best.dot")
    check_exit_status($?.to_i)
    puts

    puts "\033[1;36mSuccessful code generation for #{d}\033[0m\n"
  elsif File.directory?(d)
    puts "\033[1;36mSkip #{d} \033[0m(not all required files or TPG already generated)\n"
  end
end
  