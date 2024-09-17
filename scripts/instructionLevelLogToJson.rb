require 'json'
require 'descriptive_statistics'

# instruction level log to json
# Units by default are Watts for power and Amperes for current

def instructionLevelLogToJson(logPath, jsonPath, input_seed=nil)


    # define regex to match 

    logStartEnergy = "##### Log Start Energy #####"
    logStartTiming = "##### Log Start Timing #####"
    logEndEnergy = "##### Log End Energy #####"
    logEndTiming = "##### Log End Timing #####"

    floatRegex = /-?\d+\.?\d*/
    integerRegex = /-?\d+/
    textRegex = /[a-zA-Z]+/

    dataLine = /(#{integerRegex})\t(#{floatRegex})\t(#{floatRegex})/
    
    paramLine = /dataTimeUnit : (#{textRegex})\tdataTimerMultiplier : (#{floatRegex})\tStartAngle : (#{floatRegex})\tStartVelocity : (#{floatRegex})/
    headerLine = /Step\tCurrent\tPower/
    executionTimingLine = /\=\=\= T_(#{textRegex}) :\s+(#{floatRegex})\s+(#{textRegex})/
    cyclesLine = /\=\=\= C_(#{textRegex}) :\s+(#{floatRegex})\s*((#{textRegex})|%)/


    # variables definition

    jsonHash = {"samples" => [], "summary" => {}}
    current_sample = nil
    nbSamples = nil
    nbIterationsFunc = nil
    seed = nil


    # Parse the log file

    File.open(logPath).each_line do |line|
        if line.include?(logStartEnergy)
            current_sample = {"step" => [], "current" => [], "power" => []}
        elsif line.include?(logEndTiming)
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
            when headerLine
                next
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
            else
                # Parse NB_SAMPLES, NB_ITERATIONS_FUNC, Seed
                if line.include?("NB_SAMPLES")
                    nbSamples = line.split(":")[1].strip.to_i
                elsif line.include?("NB_ITERATIONS_FUNC")
                    nbIterationsFunc = line.split(":")[1].strip.to_i
                elsif line.include?("Seed")
                    seed = line.split(":")[1].strip.to_i
                end
            end
        end
    end


    # variables definition 

    dataTimeUnit = nil
    dataTimeMultiplier = nil
    nbCyclesInterrupts = []
    nbCyclesComputes = []
    ratioInterruptComputes = []
    executionTavgs = []
    singleInstructionExectionTavgs = []
    totalEnergies = []
    energyConsumptionUnit = nil
    singleInstructionEnergies = []
    singleInstructionExecutionTimeUnit = nil


    # for each sample find mean & stdDev for energy and time 

    # jsonHash is a hash (a dictionary-like structure in Ruby).
    # jsonHash["samples"]: retrieves the value associated with the key "samples", which is an array of different objects.

    jsonHash["samples"].each do |section|

        next unless section.is_a?(Hash) && !section["current"].nil?

        toRemove = []
        section["step"].each.with_index { |s, idx| toRemove << idx if s < 0 }
        toRemove.each { |delete_index|
            section["step"].delete_at(delete_index)
            section["current"].delete_at(delete_index)
            section["power"].delete_at(delete_index)
        }

        section["averageCurrent"] = section["current"].mean
        section["averagePower"] = section["power"].mean
        section["stdDevCurrent"] = section["current"].standard_deviation
        section["stdDevPower"] = section["power"].standard_deviation
        section["sumPower"] = section["power"].sum

        timeUnit = section["dataTimeUnit"]
        timeMultiplier = section["dataTimeMultiplier"]
        # measureStepTime is a func to convert the frequency of power sampling to seconds
        # e.g: TIM7 samples every 3 ms -> 0.003
        measureStepTime = adjust_measurement_time(timeUnit, timeMultiplier)

        # E=Sum of power values * Measurement interval
        # Total Energy consumption = sum(0.66 * 0.003, 0.72 * 0.003, ...)
        #                          = sum(0.66, 0.72, ...) * 0.003
        section["energyConsumption"] = section["power"].sum * measureStepTime
        energyConsumptionUnit = "J"


        # retrieve parameters for summary
        unless dataTimeUnit
            dataTimeUnit = timeUnit
            dataTimeMultiplier = timeMultiplier
        end

        # find key informations

        nbCyclesInterrupts << section["nbcyclesInterrupt"]
        nbCyclesComputes << section["nbcyclesCompute"]
        ratioInterruptComputes << section["ratioInterruptCompute"].to_f
        executionTavgs << section["executionTavg"].to_f if section["executionTavg"]
        singleInstructionExectionTavgs << section["executionTavg"].to_f/nbIterationsFunc if section["executionTavg"] && nbIterationsFunc
        totalEnergies << section["energyConsumption"]
        singleInstructionEnergies << section["energyConsumption"] / nbIterationsFunc if nbIterationsFunc
        
        # no longer needed, heavy and will pollute uselessly

        section.delete("step")
        section.delete("current")
        section.delete("power")
    end


    # Get the unit from executionTavg if available

    executionTimeUnit = nil
    if jsonHash["samples"].first && jsonHash["samples"].first["executionTavg"]
        executionTimeUnit = jsonHash["samples"].first["executionTavg"].split.last
    end

    # When going from Overall execTime and Consumption to single Instruction we divide by nbIterationsFunc
    # This causes the data to be fractional, for better readability we rescale it.
    
    # multiply everything by 1e3 and adjust the unit

    singleInstructionExecutionTime = (executionTavgs.mean/nbIterationsFunc * 1e3)
    singleInstructionstdDevExecutionTime = (singleInstructionExectionTavgs.standard_deviation * 1e3)

    case executionTimeUnit
    when "s"
        singleInstructionExecutionTimeUnit = "ms" 
    when "ms"
        singleInstructionExecutionTimeUnit = "us" 
    when "us"
        singleInstructionExecutionTimeUnit = "ns"
    else
        puts "Unknown time unit '#{executionTimeUnit}', defaulting to ms."
        singleInstructionExecutionTimeUnit = "ms" 
    end


    # summary represents the average of each sample

    jsonHash["summary"] = {
        "parameters" => {
            "seed" => seed,
            "nbSamples" => nbSamples,
            "nbIterationsFunc" => nbIterationsFunc,
            "timeUnit" => dataTimeUnit,
            "timeMultiplier" => dataTimeMultiplier,
        },
        "singleInstruction" =>{
            "singleInstructionExecutionTime" => singleInstructionExecutionTime.round(4),
            "singleInstructionExecutionTimeUnit" => singleInstructionExecutionTimeUnit,
            "singleInstructionstdDevExecutionTime" => singleInstructionstdDevExecutionTime.round(8),

            "singleInstructionEnergyConsumption" => (((totalEnergies.mean/nbIterationsFunc) * 1e9).round(4)),
            "singleInstructionEnergyConsumptionUnit" => "nJ",
            "singleInstructionstdDevEnergyConsumption" => (singleInstructionEnergies.standard_deviation * 1e9).round(4),
        },
        "overall" => {
            #"NbCyclesInterrupt" => nbCyclesInterrupts.mean,
            #"stdDevNbCyclesInterrupt" => nbCyclesInterrupts.standard_deviation,
            #"NbCyclesCompute" => nbCyclesComputes.mean,
            #"stdDevNbCyclesCompute" => nbCyclesComputes.standard_deviation,

            "ratioInterruptCompute" => ratioInterruptComputes.mean.round(2),
            "stdDevRatioInterruptCompute" => ratioInterruptComputes.standard_deviation.round(4),

            "executionTime" => executionTavgs.mean,
            "stdDevExecutionTime" => executionTavgs.standard_deviation.round(4),
            "executionTimeUnit" => executionTimeUnit,


            "energyConsumption" => totalEnergies.mean * 1e3,
            "stdDevEnergyConsumption" => (totalEnergies.standard_deviation*1e3).round(4),
            "energyConsumptionUnit" => "mJ"

        }
    }

    puts JSON.pretty_generate(jsonHash["summary"]["singleInstruction"])

    # Clear the samples from jsonHash, currently they aren't too heavy and can be maintained 
    # for quick checking of the data correctness.

    # jsonHash.delete("samples")

    File.write(jsonPath, JSON.pretty_generate(jsonHash))

    jsonHash
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