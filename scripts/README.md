# Scripts

Use of these scripts is automated by the `startAllEnergyBenches.rb` script.


## `start_training.rb`
Start TPG trainings with the Trainer-Genrator project (read corresponding README.md for more instructions).

## `start_generation.rb`
Generate CodeGen files for every TPGs in TPG/ directory.

## `start_pre_calcul.rb`
For a given number of initial seeds, computes the nb of steps/actions needed to reach a terminal state.
(Used for Episodic Environment). Solves the environmennt/the challenge in advance on this CPU,  to reuse it latter on the embedded system. 
Practical when the cost of checking if we have reached the end of an episode is high. Ex reverse kinematics arm problem.

## `start_validation.rb`
Check the percentage of environment solved, when starting from a different seed, on a given TPG

## `create_plots.jl`
Provide julia functions to generate plots with PlotlyJS.

## `generate_energy_plots.jl`
For each TPG, generate plots for the energy measurement curves and execution statistics.

## `generate_execution_summary.jl`
Generate a summary of the average execution stats for all TPGs in TPG/ for comparison.

## `logToJson.rb`
Provide a function to parse energy.log files into a json file.

## `install_julia_packages.jl`
Setup the julia project files and install julia packages required by julia scripts.

## `poster_ACACES_2024/overlay_of_latency_distribution.py`
Displays to possible distributions, one real emerging from measurements on the board, the second stemming from the estimation model. Used for the poster on latency and energy estimation ACACES 2024, representative figure as it is ongoing work. 
