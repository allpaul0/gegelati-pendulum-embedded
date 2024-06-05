#!/usr/bin/ruby

require 'fileutils'

### Script description ###

# Start trainings for subdirectory of TPG if it hasn't been trained yet (Doesn't contain a "training" subdir)
# See the corresponding README.md in TPG
  
### Functions ###

def check_exit_status(code)
  if code != 0
    puts "\033[1;91mERROR\033[0m --- Something wrong happened, last exit code is #{code}, exiting script"
    exit 1
  end
end


### Script ###

# Check if script is called properly, using a verbose param
if ARGV.length < 1
  puts "Usage: ruby script_name.rb <name of TPG dir (default: \"TPG\")>"
  exit 1
end

# Ensure the second argument is a non-empty string
TPG_dir = ARGV[0]
if TPG_dir.nil? || TPG_dir.strip.empty?
  puts "Error: The name of TPG dir must be a non-empty string."
  puts "Usage: ruby script_name.rb <name of TPG dir (default: \"TPG\")>"
  exit 1
end

# move from the current dir to Trainer-Generator 
# Trainer-Generator is used for training the TPGs on a Learning Environment
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

`cmake ..`
check_exit_status($?.to_i)


# Get a list of different directories to train, removing those with a subdirectory named "training"
Dir.chdir('../..')
check_exit_status($?.to_i)

dirs = Dir.entries("#{TPG_dir}")

# reject theses entries from the list
dirs = dirs.reject do |d|
  d == '.' || d == '..' || d == 'README.md'
end

# reject already trained dirs
dirs = dirs.reject do |d|
  if File.directory?(File.join("#{TPG_dir}", d, 'training'))
    puts "\033[0;93mDirectory #{d} already trained.\033[0m"
    true
  end
end


# train the different dirs
dirs.each do |d|
  # ... copy the necessary files and start the training
  # Be aware that folder name can cause encoding problems during cp !
  puts "\033[0;94mTraining directory #{d}\033[0m"

  system("cp #{TPG_dir}/#{d}/src/instructions.cpp Trainer-Generator/src/")
  check_exit_status($?.to_i)
  system("cp #{TPG_dir}/#{d}/src/params.json Trainer-Generator/")
  check_exit_status($?.to_i)

  Dir.chdir('Trainer-Generator/bin') do
    # Train-Generator/bin

    if d.include?('int')
      # Specify that we are training on int data type
      # the data needs to be scaled accordingly
      system("cmake Trainer .. -DTYPE_INT=1")
      check_exit_status($?.to_i)
    else
      system("cmake Trainer .. -DTYPE_INT=0")
      check_exit_status($?.to_i)
    end

    system("make Trainer")
    check_exit_status($?.to_i)

    Dir.chdir('Release') do
      # Train-Generator/bin/Release

      system('./Trainer')
      check_exit_status($?.to_i)

      # Save results
      system("mv Results ../../../#{TPG_dir}/#{d}/training")
      check_exit_status($?.to_i)
    end
  end
end
