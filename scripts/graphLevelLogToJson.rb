require 'json'
require 'descriptive_statistics'

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


  calculate_averages_and_summary(jsonHash, nbSamples, nbActions)

  # puts JSON.pretty_generate(jsonHash["summary"])

  File.write(jsonPath, JSON.pretty_generate(jsonHash["summary"]))

  jsonHash
end

def calculate_averages_and_summary(jsonHash, nbSamples, nbActions)
  jsonHash["samples"].each do |section|
    next unless section.is_a?(Hash) && !section["current"].nil?

    section["step"].each.with_index.reverse_each do |s, idx|
      if s < 0
        section["step"].delete_at(idx)
        section["current"].delete_at(idx)
        section["power"].delete_at(idx)
      end
    end

    # section["averageCurrent"] = section["current"].mean # not used
    section["averagePower"] = section["power"].mean
    section["stdDevCurrent"] = section["current"].standard_deviation
    section["stdDevPower"] = section["power"].standard_deviation
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
    section["stdDevEnergyConsumption"] = section["power"].standard_deviation * measureStepTime * 1e3
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
    pooled_std_dev_energy = pooled_standard_deviation(sizes, energyConsumptions, std_devs_energy)

    jsonHash["summary"][seed] = {}

    # Update summary with grouped data
    jsonHash["summary"][seed]["overall"] = {
      "averageRatioInterruptCompute" => combined_mean_ratio.round(4),
      "stdDevRatioInterruptCompute" => ratioInterruptComputes.standard_deviation.round(4),

      "averageExecutionTime" => combined_mean_execution.round(4),
      "stdDevExecutionTime" => executionTimes.standard_deviation.round(4),
      "executionTimeUnit" => executionTimeUnit,

      "averageEnergyConsumption" => combined_mean_energy.round(4),
      "PooledstdDevEnergyConsumption" => pooled_std_dev_energy.round(4),
      "energyConsumptionUnit" => energy_consumption_unit, # mJ because we rescaled it once
    }

    jsonHash["summary"][seed]["singleTraversal"]= {
      "singleTraversalAverageExecutionTime" => (combined_mean_execution/nbActions).round(4),
      "singleTraversalStdDevExecutionTime" => (executionTimes.standard_deviation/Math.sqrt(nbActions)).round(4),
      "singleTraversalexecutionTimeUnit" => executionTimeUnit,


      "singleTraversalAverageEnergyConsumption" => ((combined_mean_energy/nbActions)*1e3).round(4), 
      "singleTraversalPooledstdDevEnergyConsumption" => ((pooled_std_dev_energy/Math.sqrt(nbActions))*1e3).round(4), # rescaling the unit
      "singleTraversalEnergyConsumptionUnit" => "uJ" # unit rescaled twice J -> uJ. 1J * 1e6 = 1000000uJ
    }
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