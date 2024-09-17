# Scripts 

These post-processing python scripts serve to build the estimation model.

## `benchmarksUtils.py`
Utilitary class to import the data from the inference files into python dictionaries
**TPG_graph_level/double_base/inference/%Y-%m-%d_%H-%M-%S/energy_data.json** represents graph traversals analysis
**TPG_graph_level/double_base/training/executionInfos.json** represents informations about the TPG graph
**TPG_instruction_level/double_base/training/executionInfos.json** represents instruction level analysis

## `consolidate_instruction_level_benchmarks.py`
Allows the user to visualise every instruction level analysis in a single file

## `multipleExecutionsDistributionPlot.py`
script for mutliples seeds energy and latency benchmarks plots, shows distribution of the data
Generate latency distribution (percentage of samples for each fraction of the latency)

## `estimation_model_calcul.py`
Find the formula that best fits the graph traversal analysis using instruction level analysis and 
graph traversal informations

## `poster_ACACES2024\instruction_level_analysis_calcul.py`
script used to do computation on instruction level analysis 

## `poster_ACACES2024\overlay_of_latency_distributions.py`
Create synthetic overlay of latency distributions for the Poster