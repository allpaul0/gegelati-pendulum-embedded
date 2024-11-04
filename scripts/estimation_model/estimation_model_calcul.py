import os
import json
from benchmarkUtils import BenchmarkUtils

utils = BenchmarkUtils(base_path=os.path.abspath(os.getcwd()))

#    Find the formula that best fits the graph traversal analysis using instruction level analysis and 
# Retrieve the a priori informations about the graph traversal under the form of a dictionnary. 
# dic{seed, nbEvaluatedPrograms, nbEvaluatedTeams, nbExecutionForEachInstr}
# These are empiricall observations made after the training of the TPG, on a given testing set. 
# Those statistics are used to estimate the energy consumption and latency of the TPG on a given board. 


# retrieve graph traversal analysis dic{instr_set_data_type, seed: nbEvaluatedPrograms, nbEvaluatedTeams, nbExecutionForEachInstr, traceTeamIds}
graph_traversal_analysis = utils.import_graph_traversal_analysis("TPG_10v")

# retrieve the graph informations dic{seed, time/energy} 
graph_informations = utils.import_graph_informations("TPG_10v")

# check that graph_traversal_analysis anad graph_informations have the same keys
utils.check_keys(graph_traversal_analysis, graph_informations)

# retrieve the intruction level benchmarks on mc dic{seed, time/energy} 
instruction_level_analysis_double = utils.import_instruction_level_analysis("TPG_microbenchmarks_double")
instruction_level_analysis_int = utils.import_instruction_level_analysis("TPG_microbenchmarks_int")
instruction_level_analysis = instruction_level_analysis_int | instruction_level_analysis_double

instructions = {
"double_base": ["sub_double_asm_move", "add_double_asm_move", "mult_double_asm_move", "div_double_asm_move_6reg_input1", "cmp_double_asm_move"],
"int_base": ["sub_int", "add_int", "mult_int", "div_int_input0", "max_int"],
"int_base_optimize_O0": ["sub_int", "add_int", "mult_int", "div_int_input0", "max_int"],
"int_add": ["add_int"]
}

# retrieve TPG infos
dic_tpg_infos = utils.import_tpg_infos("TPG_10v")

# compute graph traversal estimations
graph_traversal_estimations = utils.compute_graph_traversal_estimations(graph_informations, instruction_level_analysis, instructions, dic_tpg_infos)

# Example calls with different configurations
utils.evaluate_case(graph_traversal_analysis, graph_traversal_estimations, graph_informations, "int_base", display=True)
utils.evaluate_case(graph_traversal_analysis, graph_traversal_estimations, graph_informations, "double_base", display=False)
# utils.evaluate_case(graph_traversal_analysis, graph_traversal_estimations,  graph_informations, "int_add", display=False)