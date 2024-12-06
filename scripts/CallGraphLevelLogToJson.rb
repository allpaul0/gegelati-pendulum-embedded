#!/usr/bin/ruby
require 'fileutils'

require_relative 'graphLevelLogToJson'

# Main script execution
if __FILE__ == $0
  # Check if the required arguments are provided
  if ARGV.size < 2
    puts "Usage: #{$0} logPath dataPath"
    exit 1
  end

  log_path = ARGV[0]  # First argument
  data_path = ARGV[1] # Second argument

  # Validate if the paths exist
  unless File.exist?(log_path)
    puts "Error: Log file not found at #{log_path}"
    exit 1
  end

  unless File.exist?(data_path)
    puts "Error: Data file not found at #{data_path}"
    exit 1
  end

  # Call the method with the provided arguments
  graphLevelLogToJson(log_path, data_path)
end

# usage
# ruby CallGraphLevelLogToJson.rb TPG_10v/double_base/inference/2024-12-05_07-55-00/energy.log TPG_10v/double_base/inference/2024-12-05_07-55-00/energy_data2.json 