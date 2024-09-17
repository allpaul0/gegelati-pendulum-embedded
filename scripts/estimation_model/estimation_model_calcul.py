import os
import json
from benchmarkUtils import BenchmarkUtils

utils = BenchmarkUtils(base_path=os.path.abspath(os.getcwd()))

# Find the formula that best fits the graph traversal analysis using instruction level analysis and 
# graph traversal informations

# retrieve the graph traversal informations dic{seed, nbEvaluatedPrograms, nbEvaluatedTeams, nbExecutionForEachInstr}
graph_traversal_analysis = utils.import_graph_traversal_analysis("TPG_10v")
# print(graph_traversal_analysis)

# retrieve the graph traversal benchmarks dic{seed, time/energy} 
graph_traversal_informations = utils.import_graph_traversal_informations("TPG_10v")
# for key in graph_traversal_informations:
#     print(str(key) + "\n" + str(graph_traversal_informations[key]["nbExecutionForEachInstr"])) 

# retrieve the intruction level benchmarks dic{seed, time/energy} 
import_instruction_level_analysis = utils.import_instruction_level_analysis("TPG_microbenchmarks")
# print(import_instruction_level_analysis)


