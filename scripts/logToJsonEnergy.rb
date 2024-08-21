#!/usr/bin/ruby
require 'json'
require 'descriptive_statistics'

def processLogFile(logPath, jsonPath)
    # Define regex patterns for the new log format
    logStartEnergy = "##### Log Start #####"
    logEndEnergy = "##### Log End #####"
    logStartTiming = "Starting inference execution time bench"
    logEndTiming = "Exiting inference execution time bench"

    # Regular expressions for parsing
    dataLine = /(-?\d+)\t([\d\.]+)\t([\d\.]+)/
    executionTimingLine = /\=\=\= T_avg : ([\d\.]+) (\w+)/
    
    jsonHash = {
        "meanPower" => [],
        "meanTiming" => [],
        "units" => {
            "power" => "Watts",
            "timing" => nil
        }
    }
    current_sample_power = []
    timing_bench = false

    File.open(logPath).each_line do |line|
        if line.include?(logStartEnergy)
            current_sample_power = []
        elsif line.include?(logEndEnergy)
            unless current_sample_power.empty?
                # Exclude the first measure (warming up effect)
                if current_sample_power.size > 1
                    # Calculate mean power and round to 4 decimal places
                    mean_power = current_sample_power[1..-1].map { |p| p[2].to_f }.mean.round(4)
                    jsonHash["meanPower"] << mean_power
                end
            end
        elsif line.include?(logStartTiming)
            timing_bench = true
        elsif line.include?(logEndTiming)
            timing_bench = false
        elsif dataLine.match(line)
            current_sample_power << $~
        elsif executionTimingLine.match(line) && timing_bench
            avg_timing = $1.to_f.round(4)
            timing_unit = $2
            jsonHash["meanTiming"] << avg_timing
            jsonHash["units"]["timing"] ||= timing_unit
        end
    end

    # Write the output to JSON file
    File.write(jsonPath, JSON.pretty_generate(jsonHash))

    jsonHash
end

# Command-line argument handling
if ARGV.length != 2
    puts "Usage: ruby logToJsonEnergy.rb <log_file> <output_file>"
    exit 1
end

logPath = ARGV[0]
jsonPath = ARGV[1]

# Ensure the logPath and jsonPath are valid
unless File.exist?(logPath)
    puts "Error: Log file '#{logPath}' does not exist."
    exit 1
end

# Process the log file
processLogFile(logPath, jsonPath)
