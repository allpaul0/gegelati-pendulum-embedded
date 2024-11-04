import os
import json
from sklearn.metrics import mean_squared_error, mean_absolute_percentage_error
from benchmarkUtils import BenchmarkUtils

utils = BenchmarkUtils(base_path=os.path.abspath(os.getcwd()))

# Find the formula that best fits the graph traversal analysis using instruction level analysis and 

# Retrieve the a priori informations about the graph traversal under the form of a dictionnary. 
# dic{seed, nbEvaluatedPrograms, nbEvaluatedTeams, nbExecutionForEachInstr}
# These are empiricall observations made after the training of the TPG, on a given testing set. 
# Those statistics are used to estimate the energy consumption and latency of the TPG on a given board. 
graph_traversal_analysis = utils.import_graph_traversal_analysis("TPG_10v")

# retrieve the graph traversal benchmarks dic{seed, time/energy} 
graph_traversal_benchmarks_mc = utils.import_graph_traversal_benchmarks_mc("TPG_10v")

display_key_values = 0
if display_key_values:
    for key, value in graph_traversal_benchmarks_mc.items():
        print(str(key) + ": \n" + str(value))

# check that graph_traversal_analysis anad graph_traversal_benchmarks_mc have the same keys
check_keys = 1
if(check_keys):
    if len(graph_traversal_analysis.keys()) != len(graph_traversal_benchmarks_mc.keys()):
        raise ValueError("length of graph_traversal_analysis : " + \
            str(len(graph_traversal_analysis.keys())) + \
            "differ from length of graph_traversal_benchmarks_mc : " + \
            str(len(graph_traversal_benchmarks_mc.keys())))
    for key in graph_traversal_analysis.keys():
        if graph_traversal_benchmarks_mc.get(key) is None:
            raise ValueError("graph_traversal_analysis, graph_traversal_benchmarks_mc: \
                the keys differ: " + str(key))

# retrieve the intruction level benchmarks on mc dic{seed, time/energy} 
instruction_level_analysis_double = utils.import_instruction_level_analysis("TPG_microbenchmarks_double")

instruction_level_analysis_int = utils.import_instruction_level_analysis("TPG_microbenchmarks_int")

instruction_level_analysis = instruction_level_analysis_int | instruction_level_analysis_double

instructions = {
"double_base": ["sub_double_asm_move", "add_double_asm_move", "mult_double_asm_move", 
                "div_double_asm_move_6reg_input1", "cmp_double_asm_move"],
"int_base": ["sub_int", "add_int", "mult_int", "div_int_input0", "max_int"],
"int_base_optimize_O0": ["sub_int", "add_int", "mult_int", "div_int_input0", "max_int"],
"int_add": ["add_int"]
}

dic_tpg_infos = utils.import_tpg_infos("TPG_10v")
print(dic_tpg_infos)

# compute graph traversal estimations
graph_traversal_estimations = utils.compute_graph_traversal_estimations(graph_traversal_benchmarks_mc, instruction_level_analysis, instructions, dic_tpg_infos)
# rescaled data from graph traversal analysis
for key in graph_traversal_analysis:
    graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'] = \
        round(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'] * 1000, 4) 
    graph_traversal_analysis[key]['singleTraversalexecutionTimeUnit'] = "ns"


# Helper function to print observations and estimaties
def print_observation(key, observed, estimatedP, estimatedT, benchmark=None, display=True):
    if display:
        print(f"{key}: observed: {observed}, estimated for programs: {estimatedP}, estimated for teams: {estimatedT}")
        if benchmark:
            print(f"{benchmark}\n")

# Function to calculate metrics and display results
def calculate_metrics(y_true, y_pred, label):
    mse = round(mean_squared_error(y_true, y_pred), 4)
    mape = round(mean_absolute_percentage_error(y_true, y_pred), 4)
    print(f"{label} - MSE: {mse}, MAPE: {mape}")

# General evaluation function 
def evaluate_case(graph_traversal_analysis, graph_traversal_estimations, graph_traversal_benchmarks_mc, label, display=True):
    y_true, y_pred = [], []
    for key, value in graph_traversal_analysis.items():
        # key[0] is data_type_instr_set, key[1] is the seed for this estimation
        if key[0] == label and (estimation := graph_traversal_estimations.get(key)) is not None:
            observed = value['singleTraversalAverageExecutionTime']
            predictedP = estimation['program_latency']
            predictedT = estimation['team_latency']
            y_true.append(observed)
            y_pred.append(predictedP + predictedT)
            print_observation(key, observed, predictedP, predictedT, graph_traversal_benchmarks_mc.get(key), display)
    calculate_metrics(y_true, y_pred, label)

# Example calls with different configurations
# evaluate_case(graph_traversal_analysis, graph_traversal_estimations, graph_traversal_benchmarks_mc, "int_base",)

evaluate_case(graph_traversal_analysis, graph_traversal_estimations, graph_traversal_benchmarks_mc, "double_base", display=True)

evaluate_case(graph_traversal_analysis, graph_traversal_estimations,  graph_traversal_benchmarks_mc, "int_add", display=True)


# optimize O0

# y_pred, y_true = [], []
# display = 1
# for key, value in graph_traversal_analysis.items():
#     if key[0] == "int_base_optimize_O0" and graph_traversal_estimations.get(key) is not None:
#         y_true.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
#         y_pred.append(graph_traversal_estimations[key])
#         if display == 1:
#             print(str(key) + ": " + "observed: " + \
#                     str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
#                     ", estimated: " + str(graph_traversal_estimations[key]))
#             print(str(graph_traversal_benchmarks_mc[key]) + "\n")
# print("int_base_optimize_O0")
# print(round(mean_squared_error(y_true, y_pred),4))
# print(round(mean_absolute_percentage_error(y_true, y_pred),4))



# optimize O3, optimizeO0

# y_pred_O3, y_pred_O0 = [], []
# display = 1
# for key, value in graph_traversal_analysis.items():
#     if key[0] == "int_base_optimize_O0" and graph_traversal_analysis.get(("int_base", key[1])) is not None:
#         y_pred_O0.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
#         y_pred_O3.append(graph_traversal_analysis[("int_base", key[1])]['singleTraversalAverageExecutionTime'])
#         if display == 1:
#             print(str(key) + ": " + "observed O0: " + \
#                     str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
#                     ", observed O3: " + str(graph_traversal_analysis[("int_base", key[1])]['singleTraversalAverageExecutionTime']) + " " + \
#                     "estimated : " + str(graph_traversal_estimations[("int_base", key[1])]))
# print("int_base_O3, int_base_O0")
# print(round(mean_squared_error(y_true, y_pred),4))
# print(round(mean_absolute_percentage_error(y_true, y_pred),4))

demo_MSE = 0
if demo_MSE:
    y_true =        [4633.9  , 15020.7  , 4657.7  , 15032.7 , 15020.7  , 4657.7  , 739.7471 , 15032.7]
    y_pred_actual = [739.7471, 1432.3124, 739.7471, 739.7471, 1992.9626, 739.7471, 1992.9626, 739.7471]
    y_pred_target = [4500    , 15800.0  , 4500    , 14000.0 , 14500.0  , 4600.0  , 700      , 14800.0]
    print("actual int sample")
    print(round(mean_absolute_percentage_error(y_true, y_pred_actual),4))
    print("target int sample")
    print(round(mean_absolute_percentage_error(y_true, y_pred_target),4))

demo_my_funcs = 0
if demo_my_funcs:
    print("my functions operating on dict")

    # compute MSE
    print(utils.MSE(graph_traversal_analysis, graph_traversal_estimations, "int_base"))

    #compute MAPE
    print(utils.MAPE(graph_traversal_analysis, graph_traversal_estimations, "int_base"))

# utils.display_estimations_observed(graph_traversal_analysis, graph_traversal_estimations)