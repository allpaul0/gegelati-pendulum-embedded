require 'json'
require 'descriptive_statistics'
require 'pp'

# Instruction-level log to JSON
def graphLevelLogToJson(logPath, jsonPath, input_seed = nil)
  logStartBench = "##### Log Start Bench #####"
  logEndBench = "##### Log End Bench #####"
  floatRegex = /-?\d+\.?\d*/
  integerRegex = /-?\d+/
  textRegex = /[a-zA-Z]+/
  dataLine = /(#{integerRegex})\t(#{floatRegex})\t(#{floatRegex})/
  paramLine = /dataTimeUnit : (#{textRegex})\tdataTimerMultiplier : (#{floatRegex})\tStartAngle : (#{floatRegex})\tStartVelocity : (#{floatRegex})/
  headerLine = /Step\tCurrent\tPower/
  executionTimingLine = /\=\=\= T_(#{textRegex}) :\s+(#{floatRegex})\s+(#{textRegex})/
  cyclesLine = /\=\=\= C_(#{textRegex}) :\s+(#{floatRegex})\s*((#{textRegex})|%)/
  seedLine = /SEED : (#{integerRegex})/

  jsonHash = { "samples" => [], "summary" => {} }
  current_sample = nil
  nbSamples = nil
  nbActions = nil

  File.open(logPath).each_line do |line|
    if line.include?(logStartBench)
      current_sample = { "step" => [], "current" => [], "power" => [] }
    elsif line.include?(logEndBench)
      jsonHash["samples"] << current_sample
    else
      case line
      when paramLine
        if current_sample
          current_sample["dataTimeUnit"] = $1
          current_sample["dataTimeMultiplier"] = $2.to_f
          current_sample["startAngle"] = $3.to_f
          current_sample["startVelocity"] = $4.to_f
        end
      when dataLine
        if current_sample
          current_sample["step"] << $1.to_i
          current_sample["current"] << $2.to_f
          current_sample["power"] << $3.to_f
        end
      when cyclesLine
        if current_sample
          variable_name = $1
          value = $2
          unit = $3
          current_sample["#{variable_name}"] = "#{value}"
        end
      when executionTimingLine
        if current_sample
          timing_name = $1
          value = $2
          unit = $3
          current_sample["executionT#{timing_name}"] = "#{value.sub(/.?0*$/, '')} #{unit}"
        end
      when seedLine
        if current_sample
          current_sample["seed"] = $1
        end
      else
        if line.include?("NB_SAMPLES")
          nbSamples = line.split(":")[1].strip.to_i
        elsif line.include?("NB_ACTIONS")
          nbActions = line.split(":")[1].strip.to_i
        end
      end
    end
  end

  puts "jsonHash[\"samples\"].size: #{jsonHash["samples"].size}"
  calculate_averages_and_summary(jsonHash, nbSamples, nbActions)

  # for debug purpose
  # Path to save the raw JSON hash for debugging
  debug_path = "debug_json_hash.txt"

  # Write the raw hash to a file
  File.open(debug_path, 'w') do |f|
    PP.pp(jsonHash, f)
  end

  # puts JSON.pretty_generate(jsonHash["summary"])

  File.write(jsonPath, JSON.pretty_generate(jsonHash["summary"]))

  jsonHash
end

def calculate_averages_and_summary(jsonHash, nbSamples, nbActions)
  jsonHash["samples"].each do |section|
    unless section.is_a?(Hash) && !section["current"].nil?
      puts "Error: Section is not a valid Hash or 'current' key is missing. Section: #{section.inspect}"
      next
    end
    
    # init is -1, it should be deleted when present
    section["step"].each.with_index.reverse_each do |s, idx|
      if s < 0
        section["step"].delete_at(idx)
        section["current"].delete_at(idx)
        section["power"].delete_at(idx)
      end
    end

    # section["averageCurrent"] = section["current"].mean # not used
    section["averagePower"] = section["power"].mean
    section["stdDevCurrent"] = standard_deviation_sample(section["current"])
    section["stdDevPower"] = standard_deviation_sample(section["power"])
    section["sumPower"] = section["power"].sum

    # retrieve timeUnit
    timeUnit = section["dataTimeUnit"]
    timeMultiplier = section["dataTimeMultiplier"]

    # measureStepTime is a func to convert the frequency of power sampling to seconds
    # e.g: TIM7 samples every 3 ms -> 0.003
    measureStepTime = adjust_measurement_time(timeUnit, timeMultiplier)

    # Total Energy consumption = sum(0.66 * 0.003, 0.72 * 0.003, ...)
    #                          = sum(0.66, 0.72, ...) * 0.003
    # Watts * seconds = Joules -> rescaled to mJ. (1 J * 1e3 = 1000 mJ)
    section["energyConsumption"] = section["power"].sum * measureStepTime * 1e3 
    section["stdDevEnergyConsumption"] = standard_deviation_sample(section["power"]) * measureStepTime * 1e3
    section["energyConsumptionUnit"] = "mJ" # Joules rescaled to milliJoules 

    # retrieve size for pooled_standard_deviation calculation

    section["size"] = section["step"].size

    # no longer needed, heavy and will pollute uselessly

    section.delete("step")
    section.delete("current")
    section.delete("power")
  end


  group_samples_by_seed(jsonHash, nbSamples, nbActions)
end

# TIM 7 = 3 ms -> 0.003
def adjust_measurement_time(timeUnit, timeMultiplier)
  case timeUnit
  when "ms"
    timeMultiplier / 1000.0
  when "us"
    timeMultiplier / 1_000_000.0
  when "s"
    # Do nothing, already in seconds
    timeMultiplier
  else
    puts "Unknown time unit '#{timeUnit}', defaulting to seconds."
    timeMultiplier
  end
end

# finds stdDev for a sample, I have measured a subset of possible occurrences
# on the board
def standard_deviation_sample(numbers) 
  # Convert strings to floats
  numbers = numbers.map(&:to_f)

  # Return 0 if there's only one value
  return 0 if numbers.size <= 1

  # Step 1: Calculate the mean
  mean = numbers.sum.to_f / numbers.size
  
  # Step 2: Calculate the variance
  variance = numbers.map { |n| (n - mean) ** 2 }.sum / (numbers.size - 1)
  
  # Step 3: Calculate the standard deviation
  Math.sqrt(variance)
end


def group_samples_by_seed(jsonHash, nbSamples, nbActions)

  executionTimeUnit = get_executionTimeUnit(jsonHash)

  grouped_by_seed = jsonHash["samples"].group_by { |sample| sample["seed"] }


  grouped_by_seed.each do |seed, samples|
    # Gather data for calculations
    sizes = samples.map { |s| s["size"] }
    ratioInterruptComputes = samples.map { |s| s["ratioInterruptCompute"] }
    executionTimes = samples.map { |s| s["executionTavg"] }
    energyConsumptions = samples.map { |s| s["energyConsumption"] }
    std_devs_energy = samples.map { |s| s["stdDevEnergyConsumption"] }
    energy_consumption_unit = samples.first["energyConsumptionUnit"] # Assuming all samples have the same unit

    # Calculate combined averages
    combined_mean_ratio = ratioInterruptComputes.mean
    combined_mean_execution = executionTimes.mean
    combined_mean_energy = energyConsumptions.mean

    # Calculate pooled standard deviations
    # pooled_std_dev_energy = pooled_standard_deviation(sizes, energyConsumptions, std_devs_energy)

    jsonHash["summary"][seed] = {}

    # Can be decommented for insight on the calculus

    # Update summary with grouped data
    # jsonHash["summary"][seed]["overall"] = {
    #   "averageRatioInterruptCompute" => combined_mean_ratio.round(4),
    #   "stdDevRatioInterruptCompute" => standard_deviation_sample(ratioInterruptComputes).round(4),

    #   "averageExecutionTime" => combined_mean_execution.round(4),
    #   "stdDevExecutionTime" => standard_deviation_sample(executionTimes).round(4),
    #   "executionTimeUnit" => executionTimeUnit,

    #   "averageEnergyConsumption" => combined_mean_energy.round(4),
    #   "stdDevEnergyConsumption" => (standard_deviation_sample(energyConsumptions)).round(4),
    #   # "PooledstdDevEnergyConsumption" => pooled_std_dev_energy.round(4),
    #   "energyConsumptionUnit" => energy_consumption_unit, # mJ because we rescaled it once
    # }

    jsonHash["summary"][seed]["singleTraversal"]= {
      "singleTraversalAverageExecutionTime" => (combined_mean_execution/nbActions).round(4),
      "singleTraversalStdDevExecutionTime" => (standard_deviation_sample(executionTimes)/nbActions).round(4),
      "singleTraversalexecutionTimeUnit" => executionTimeUnit,

      "singleTraversalAverageEnergyConsumption" => ((combined_mean_energy/nbActions)*1e3).round(4), 
      "singleTraversalStdDevEnergyConsumption" => ((standard_deviation_sample(energyConsumptions)/nbActions)*1e3).round(4),
      # PooledStdDev yields a similar result to stdDev
      # "singleTraversalPooledstdDevEnergyConsumption" => ((pooled_std_dev_energy/nbActions)*1e3).round(4), # rescaling the unit
      "singleTraversalEnergyConsumptionUnit" => "uJ" # unit rescaled twice J -> uJ. 1J * 1e6 = 1000000uJ
    }

    # Can be commented for insight on the calculus

    # Remove the processed samples from jsonHash["samples"]
    #jsonHash["samples"].delete_if { |sample| sample["seed"] == seed }
  end
end

def pooled_standard_deviation(sizes, means, std_devs)
  # Check for nil values in input arrays
  if sizes.any?(&:nil?) || means.any?(&:nil?) || std_devs.any?(&:nil?)
    raise ArgumentError, "Input arrays contain nil values. Please check the input data."
  end
  
  # Calculate the total size of all data points
  total_size = sizes.sum
  
  # Calculate the combined mean
  weighted_sum = 0.0
  sizes.each_with_index do |size, index|
    weighted_sum += size * means[index]
  end
  combined_mean = weighted_sum / total_size
  
  # Calculate the pooled variance
  sum_of_variances = 0.0
  sizes.each_with_index do |size, index|
    mean = means[index]
    std_dev = std_devs[index]
    
    # Check if size is zero to prevent division errors
    next if size.zero?
    
    # Within-group variability
    within_group_variance = (size - 1) * std_dev**2
    
    # Between-group variability
    between_group_variance = size * (mean - combined_mean)**2
    
    # Add to the total sum of variances
    sum_of_variances += within_group_variance + between_group_variance
  end
  
  # Prevent division by zero in variance calculation
  degrees_of_freedom = total_size - sizes.size
  if degrees_of_freedom <= 0
    raise ArgumentError, "Invalid degrees of freedom for pooled variance calculation."
  end
  
  # Calculate the pooled variance using the total degrees of freedom
  pooled_variance = sum_of_variances / degrees_of_freedom
  
  # Calculate the pooled standard deviation
  pooled_std_dev = Math.sqrt(pooled_variance)
  
  # Return the pooled standard deviation
  pooled_std_dev
end

def get_executionTimeUnit(jsonHash)

    # Get the unit from executionTavg if available

    executionTimeUnit = nil
    if jsonHash["samples"].first && jsonHash["samples"].first["executionTavg"]
        executionTimeUnit = jsonHash["samples"].first["executionTavg"].split.last
    end

    executionTimeUnit
end