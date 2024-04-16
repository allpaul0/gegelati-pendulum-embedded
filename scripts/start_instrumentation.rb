#!/usr/bin/ruby

require 'fileutils'

# Start Instrumenting the TPG if it hasn't been instrumented and cleaned yet (Doesn't contain a "training/instrumented" subdir)
# See the corresponding README.md in TPG

def check_exit_status(code)
    if code != 0
        puts "\033[1;91mERROR\033[0m --- Something wrong happened, last exit code is #{code}, exiting script"
        exit 1
    end
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

  dirs = Dir.entries('TPG')

  # reject theses entries from the list
  dirs = dirs.reject do |d|
    d == '.' || d == '..' || d == 'README.md'
  end

    # Accept directories containing training folder but no training/instrumented subfolder
    dirs = dirs.reject do |d|
    training_dir = File.join('TPG', d, 'training')
    instrumented_dir = File.join(training_dir, 'instrumented')
  
    # directory needs to be trained but not instrumented
    if File.directory?(training_dir)
        if File.directory?(instrumented_dir)
            puts "\033[1;36mSkip #{d} \033[0m(already instrumented)\n"
            true    
        else
            false
        end
    else
        puts "\033[1;36mSkip #{d} \033[1;31m(training dir is missing)\033[0m\n"
        true
    end
  end
  #It either doesn't contain a training folder or already has a 'instrumented' subfolder

#clean the different dirs
dirs.each do |d|
    # ... copy the necessary files and start the instrumentation
    # Be aware that folder name can cause encoding problems during cp !
    puts "\033[0;94mInstrumentation directory #{d}\033[0m"

    system("cp TPG/#{d}/src/instructions.cpp Trainer-Generator/src/")
    check_exit_status($?.to_i)
    system("cp TPG/#{d}/src/params.json Trainer-Generator/")
    check_exit_status($?.to_i)
  
    Dir.chdir('Trainer-Generator/bin') do
        # Train-Generator/bin

        if d.include?('int')
            # Specify that we are training on int data type
            # the data needs to be scaled accordingly
            system("cmake -DTYPE_INT=1 ..")
            check_exit_status($?.to_i)
        else
            system("cmake -DTYPE_INT=0 ..")
            check_exit_status($?.to_i)
        end

        system("make Instrument")
        check_exit_status($?.to_i)

        Dir.chdir('Release') do
            # Train-Generator/bin/Release
            # Launch the Training            
            system("./Instrument ../../../TPG/#{d}/training/out_best.dot")
            check_exit_status($?.to_i)
            puts
    
            # Save results
            system("mv Results ../../../TPG/#{d}/training/instrumented")
            check_exit_status($?.to_i)
        end
    end
end
