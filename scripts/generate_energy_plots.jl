#!/usr/bin/julia

using PlotlyJS
using JSON3

include("create_plots.jl")

# =====[ Script parameters ]=====

showPlot = false

# =====[ Functions ]=====

"""
    getOptionArgument(i::Integer)

Return the argument of an option, with i the index of the option in ARGS. Exit program if there is no argument.
"""
function getOptionArgument(i::Integer)
    if i+1 <= length(ARGS) && ARGS[i+1][1] != '-'
        return ARGS[i+1]
    else
        println("Missing argument for option $a")
        exit(1)
    end
end

"""
    filterByFiles!(dirPath::String, requiredFiles::Vector{String}, excludedFiles::Vector{String})

Return if a directory has all required files and doesn't have all exlcuded files.
"""
function checkFiles(dirPath::String, requiredFiles::Vector{String}, excludedFiles::Vector{String}=[])

    missingFile = findfirst(requiredFiles) do file
        !isfile(dirPath * "/" * file)
    end

    if !isnothing(missingFile)
        return false
    end

    unexpectedFile = findfirst(excludedFiles) do file
        isfile(dirPath * "/" * file)
    end

    return isnothing(unexpectedFile)

end


# =====[ ARGS parsing ]=====

i = 1
while i <= length(ARGS)

    a = ARGS[i]

    if a == "--show"
        global showPlot = true
    else
        println("Unknown option $a")
        exit(1)
    end

    global i += 1
end


# =====[ Searching results path ]=====

# Searching results paths with the energy_data.json file

all_result_paths = []

isInferenceResultDir(fullPath::String) = occursin(r"^.*\d{4}-\d{2}-\d{2}_\d{2}-\d{2}-\d{2}$", fullPath)

cd((@__DIR__) * "/../TPG") do 

    tpgDirs = filter(isdir, readdir(join=true))  # Get all TPG subdirectories

    for tpgDir in tpgDirs  # Get all results directories for all TPGs

        inferenceDir = joinpath(tpgDir, "inference")  # Create path to inference directory within TPG directory

        if isdir(inferenceDir)  # check if 'inference' directory exists
            inferenceDirs = filter(isdir, readdir(inferenceDir, join=true))  # Get all directories within 'inference' directory
            resultDirs = filter(isInferenceResultDir, inferenceDirs)  # Filter directories that match the inferenece result pattern (timestamp)
            append!(all_result_paths, resultDirs)
        end
    end

end


# =====[ Plotting ]=====


# === Measurments plot ===

requiredFiles = [
    "energy_data.json"
]

excludedFiles = [
    "graph.html",
    "graph.png"
]

valid_result_paths = filter(
    path -> checkFiles(path, requiredFiles, excludedFiles),
    all_result_paths
)

println("Creating measurement plots for :")
for p in valid_result_paths
    println("- ", p)
end

for resultDirPath in valid_result_paths

    graph = plotEnergyData("$resultDirPath/energy_data.json")
    savefig(graph, "$resultDirPath/graph.png", width=1920, height=1080)
    
    # Saving html files
    open("$resultDirPath/graph.html", "w") do io
        PlotlyBase.to_html(io, graph)
    end

    if showPlot
        displayInBrowser("$resultDirPath/graph.html")
        println("Press enter to continue")
        readline()
    end
end


# === Execution plots ===

requiredFiles = [
    "executionStats.json"
]

excludedFiles = [
    "execution_stats.html",
    "instructions_stats.html"
]

valid_result_paths = filter(
    path -> checkFiles(path, requiredFiles, excludedFiles),
    all_result_paths
)

println("Creating execution stats plots for :")
for p in valid_result_paths
    println("- ", p)
end

for resultDirPath in valid_result_paths

    executionPlot, instructionPlot = plotExecutionData("$resultDirPath/executionStats.json")

    # Saving html files
    open("$resultDirPath/execution_stats.html", "w") do io
        PlotlyBase.to_html(io, executionPlot.plot)
    end
    open("$resultDirPath/instructions_stats.html", "w") do io
        PlotlyBase.to_html(io, instructionPlot.plot)
    end

    if showPlot
        displayInBrowser("$resultDirPath/execution_stats.html")
        displayInBrowser("$resultDirPath/instructions_stats.html")
        println("Press enter to continue")
        readline()
    end

end