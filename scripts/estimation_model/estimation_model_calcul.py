import os
import json
from sklearn.metrics import mean_squared_error, mean_absolute_percentage_error
from benchmarkUtils import BenchmarkUtils

utils = BenchmarkUtils(base_path=os.path.abspath(os.getcwd()))

# Find the formula that best fits the graph traversal analysis using instruction level analysis and 
# graph traversal informations

# retrieve the graph traversal informations dic{seed, nbEvaluatedPrograms, nbEvaluatedTeams, nbExecutionForEachInstr}
graph_traversal_analysis = utils.import_graph_traversal_analysis("TPG_10v")

# retrieve the graph traversal benchmarks dic{seed, time/energy} 
graph_traversal_informations = utils.import_graph_traversal_informations("TPG_10v")

# for key, value in graph_traversal_informations.items():
#     print(str(key) + ": \n" + str(value))

# check that graph_traversal_analysis anad graph_traversal_informations have the same keys
# for key in graph_traversal_analysis.keys():
#     if graph_traversal_informations.get(key) is None:
#         raise ValueError("graph_traversal_analysis, graph_traversal_informations: the keys differ: " + str(key))

print(len(graph_traversal_analysis.keys()))
print(len(graph_traversal_informations.keys()))


# retrieve the intruction level benchmarks dic{seed, time/energy} 
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



# compute graph traversal estimations
graph_traversal_estimations = utils.compute_graph_traversal_estimations(graph_traversal_informations, 
    instruction_level_analysis, instructions)
# rescaled data from graph traversal analysis
for key in graph_traversal_analysis:
    graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'] = round(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'] * 1000, 4) 
    graph_traversal_analysis[key]['singleTraversalexecutionTimeUnit'] = "ns"


# compute sklearn MSE


# int 

y_pred, y_true = [], []
display = 1

for key, value in graph_traversal_analysis.items():
    if key[0] == "int_base" and graph_traversal_estimations.get(key) is not None:
        y_true.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
        y_pred.append(graph_traversal_estimations[key])
        if display == 1:
            print(str(key) + ": " + "observed: " + \
                str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
                ", estimated: " + str(graph_traversal_estimations[key]))
            print(str(graph_traversal_informations[key]) + "\n")
print("int")
print(round(mean_squared_error(y_true, y_pred),4))
print(round(mean_absolute_percentage_error(y_true, y_pred),4))


# double

y_pred, y_true = [], []
display = 0
for key, value in graph_traversal_analysis.items():
    if key[0] == "double_base" and graph_traversal_estimations.get(key) is not None:
        y_true.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
        y_pred.append(graph_traversal_estimations[key])
        if display == 1:
            print(str(key) + ": " + "observed: " + \
                    str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
                    ", estimated: " + str(graph_traversal_estimations[key]))
            print(str(graph_traversal_informations[key]) + "\n")
print("double")
print(round(mean_squared_error(y_true, y_pred),4))
print(round(mean_absolute_percentage_error(y_true, y_pred),4))


# int add
y_pred, y_true = [], []
display = 0
# for key, value in graph_traversal_analysis.items():
#     if key[0] == "int_add" and graph_traversal_estimations.get(key) is not None:
#         y_true.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
#         y_pred.append(graph_traversal_estimations[key])
#         if display == 1:
#             print(str(key) + ": " + "observed: " + \
#                 str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
#                 ", estimated: " + str(graph_traversal_estimations[key]))
# print("int_add")
# print(round(mean_squared_error(y_true, y_pred),4))
# print(round(mean_absolute_percentage_error(y_true, y_pred),4))

# optimize O0

y_pred, y_true = [], []
display = 1
# for key, value in graph_traversal_analysis.items():
#     if key[0] == "int_base_optimize_O0" and graph_traversal_estimations.get(key) is not None:
#         y_true.append(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'])
#         y_pred.append(graph_traversal_estimations[key])
#         if display == 1:
#             print(str(key) + ": " + "observed: " + \
#                     str(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime']) + " " + \
#                     ", estimated: " + str(graph_traversal_estimations[key]))
#             print(str(graph_traversal_informations[key]) + "\n")
# print("int_base_optimize_O0")
# print(round(mean_squared_error(y_true, y_pred),4))
# print(round(mean_absolute_percentage_error(y_true, y_pred),4))

# optimize O3, optimizeO0
y_pred_O3, y_pred_O0 = [], []
display = 1
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

y_true =        [4633.9  , 15020.7  , 4657.7  , 15032.7 , 15020.7  , 4657.7  , 739.7471 , 15032.7]
y_pred_actual = [739.7471, 1432.3124, 739.7471, 739.7471, 1992.9626, 739.7471, 1992.9626, 739.7471]
y_pred_target = [4500    , 15800.0  , 4500    , 14000.0 , 14500.0  , 4600.0  , 700      , 14800.0]
print("actual int sample")
print(round(mean_absolute_percentage_error(y_true, y_pred_actual),4))
print("target int sample")
print(round(mean_absolute_percentage_error(y_true, y_pred_target),4))

print("my functions operating on dict")

# compute MSE
print(utils.MSE(graph_traversal_analysis, graph_traversal_estimations, "int_base"))

#compute MAPE
print(utils.MAPE(graph_traversal_analysis, graph_traversal_estimations, "int_base"))

# utils.display_estimations_observed(graph_traversal_analysis, graph_traversal_estimations)