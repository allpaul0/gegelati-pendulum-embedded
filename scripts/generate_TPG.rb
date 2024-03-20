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

  script_dir = File.expand_path(File.dirname(__FILE__))
  Dir.chdir(File.join(script_dir, '..', 'TPG'))
  
  # CMake configuration
  FileUtils.rm_r('../Trainer-Generator/bin')
  check_exit_status($?.to_i)
  Dir.mkdir('../Trainer-Generator/bin')
  check_exit_status($?.to_i)
  system('cmake -S ../Trainer-Generator -B ../Trainer-Generator/bin')
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
      puts "\033[1;36mSkip #{d} (not all required files or TPG already generated)\033[0m\n"
    end
  end
  