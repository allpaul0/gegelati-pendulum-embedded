require 'json'
require 'descriptive_statistics'

def logToJson(logPath, jsonPath, input_seed=nil)
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
    executionTimingLine = /\=\=\= T_(#{textRegex}) : (#{floatRegex}) (#{textRegex})/
    cyclesLine = /\=\=\= C_(#{textRegex}) : (#{floatRegex})(( #{textRegex})|%)/

    jsonHash = {"samples" => [], "summary" => {}}
    current_sample = nil
    nbSamples = nil
    nbIterationsFunc = nil
    seed = nil

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
                # Parse NB_SAMPLES and NB_ITERATIONS_FUNC
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

    jsonHash["samples"] << current_sample if current_sample

    dataTimeUnit = nil
    dataTimeMultiplier = nil
    nbCyclesInterrupts = []
    nbCyclesComputes = []
    ratioInterruptComputes = []
    executionTavgs = []
    totalEnergies = []

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

        timeUnit = section["dataTimeUnit"]
        timeMultiplier = section["dataTimeMultiplier"]
        measureStepTime = timeMultiplier

        case timeUnit
        when "ms"
            measureStepTime = timeMultiplier / 1000.0
        when "us"
            measureStepTime = timeMultiplier / 1000000.0
        when "s"
            # Do nothing, already in seconds
        else
            puts "Unknown time unit '#{timeUnit}', defaulting to seconds."
        end

        section["energyConsumption"] = section["power"].sum * measureStepTime

        dataTimeUnit ||= section["dataTimeUnit"]
        dataTimeMultiplier ||= section["dataTimeMultiplier"]
        nbCyclesInterrupts << section["nbcyclesInterrupt"]
        nbCyclesComputes << section["nbcyclesCompute"]
        ratioInterruptComputes << section["ratioInterruptCompute"].to_f
        executionTavgs << section["executionTavg"].to_f if section["executionTavg"]
        totalEnergies << section["energyConsumption"]

        section.delete("step")
        section.delete("current")
        section.delete("power")
    end

     # Get the unit from executionTavg if available
     executionUnit = nil
     if jsonHash["samples"].first && jsonHash["samples"].first["executionTavg"]
         executionUnit = jsonHash["samples"].first["executionTavg"].split.last
     end
 

    # summary represents the average of each sample
    jsonHash["summary"] = {
        "Seed" => seed,
        "nbSamples" => nbSamples,
        #"nbIterationsFunc" => nbIterationsFunc,
        "dataTimeUnit" => dataTimeUnit,
        "dataTimeMultiplier" => dataTimeMultiplier,
        #"NbCyclesInterrupt" => nbCyclesInterrupts.mean,
        #"stdDevNbCyclesInterrupt" => nbCyclesInterrupts.standard_deviation,
        #"NbCyclesCompute" => nbCyclesComputes.mean,
        #"stdDevNbCyclesCompute" => nbCyclesComputes.standard_deviation,
        "ratioInterruptCompute" => ratioInterruptComputes.mean,
        "stdDevRatioInterruptCompute" => ratioInterruptComputes.standard_deviation,
        "singleInstructionExecutionTime" => "#{(executionTavgs.mean/nbIterationsFunc).round(4)} #{executionUnit}",
        "sIstdDevExecutionTime" => executionTavgs.standard_deviation/nbIterationsFunc,
        "singleInstructionEnergyConsumption" => totalEnergies.mean/nbIterationsFunc,
        "sIstdDevEnergyConsumption" => totalEnergies.standard_deviation/nbIterationsFunc,
        "ExecutionTime" => "#{executionTavgs.mean} #{executionUnit}",
        "stdDevExecutionTime" => executionTavgs.standard_deviation,
        "EnergyConsumption" => totalEnergies.mean,
        "stdDevEnergyConsumption" => totalEnergies.standard_deviation
    }

    # Clear the samples from jsonHash
    # jsonHash.delete("samples")

    File.write(jsonPath, JSON.pretty_generate(jsonHash))

    jsonHash
end
