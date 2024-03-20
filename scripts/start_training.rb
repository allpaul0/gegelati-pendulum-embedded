#!/usr/bin/ruby

require 'fileutils'

# Start trainings for subdirectory of TPG if it hasn't been trained yet (Doesn't contain a "training" subdir)
# See the corresponding README.md in TPG

def check_exit_status(code)
    if code != 0
        puts "\033[1;91mERROR\033[0m --- Something wrong happened, last exit code is #{code}, exiting script"
        exit 1
    end
end
  
  # move from the current dir to Trainer-Generator
  script_dir = File.expand_path(File.dirname(__FILE__))
  Dir.chdir(File.join(script_dir, '..'))
  check_exit_status($?.to_i)
  
  # CMake configuration
  FileUtils.rm_r('Trainer-Generator/bin')
  check_exit_status($?.to_i)
  FileUtils.mkdir('Trainer-Generator/bin')
  check_exit_status($?.to_i)
  Dir.chdir('Trainer-Generator/bin')
  check_exit_status($?.to_i)
  `cmake ..`
  check_exit_status($?.to_i)
  Dir.chdir('../..')
  check_exit_status($?.to_i)


  # Get a list of directories to train, removing those with a subdirectory named "training"
  dirs = Dir.entries('TPG')
  puts("dirs1" )
  puts(dirs)

  dirs = dirs.reject do |d|
    d == '.' || d == '..' || d == 'README.md'
  end
  puts("dirs2" )
  puts(dirs)

  dirs = dirs.reject do |d|
    if File.directory?(File.join('TPG', d, 'training'))
      puts "Directory #{d} already trained"
      true
    end
  end

  puts("dirs3" )
  puts(dirs)

  dirs.each do |d|
    # ... copy the necessary files and start the training
    # folder name can cause encoding problems during cp 
    puts("TPG/#{d}/src/instructions.cpp")
    system("cp TPG/#{d}/src/instructions.cpp Trainer-Generator/src/")
    check_exit_status($?.to_i)
    system("cp TPG/#{d}/src/params.json Trainer-Generator/")
    check_exit_status($?.to_i)
  
    Dir.chdir('Trainer-Generator/bin') do
      # Train-Generator/bin
      system('cmake --build . --target Trainer')
      check_exit_status($?.to_i)
      puts
  
      Dir.chdir('Release') do
        # Train-Generator/bin/Release
  
        # Launch the Training
        if d.include?('int')
          # Specify that we are training on int data type
          # the data needs to be scaled accordingly
          system('./Trainer TYPE_INT=1')
          puts "int"
        else
          system('./Trainer')
        end
        check_exit_status($?.to_i)
        puts
  
        # Save results
        system("mv Results ../../../TPG/#{d}/training")
        check_exit_status($?.to_i)
      end
    end
  end
  