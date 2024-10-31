import os
import json
import re
from datetime import datetime
import numpy as np
from sklearn.linear_model import LinearRegression

class BenchmarkUtils:
    def __init__(self, base_path):
        self.base_path = base_path

    # inside the inference/ folder, find the most recent folder (ordered by date of creation)
    def find_most_recent_folder(self, folder_list):
        date_format = "%Y-%m-%d_%H-%M-%S"
        date_folders = []
        
        for folder in folder_list:
            try:
                # creates a datetime object from the given string.
                folder_date = datetime.strptime(folder, date_format)
                date_folders.append((folder_date, folder))
            except ValueError:
                print(f"Skipping folder {folder}: Incorrect date format.")
                continue
        
        if not date_folders:
            print("No valid date-formatted folders found.")
            return None
        
        most_recent_folder = max(date_folders, key=lambda x: x[0])[1]
        return most_recent_folder

    # assemble base_folder, folder_name, inference, date, energy_data2.json into a file path (if possible)
    def construct_file_path(self, base_folder, folder_name, sub_dir):
        # Construct the full path dynamically using base_folder
        tpg_folder_path = os.path.join(self.base_path, base_folder, folder_name, sub_dir)
        
        if not os.path.exists(tpg_folder_path):
            print(f"Path does not exist: {tpg_folder_path}")
            return None
        
        folder_listdir = os.listdir(tpg_folder_path)
        if not folder_listdir:
            print(f"No subfolders found in: {tpg_folder_path}")
            return None
        
        most_recent_folder = self.find_most_recent_folder(folder_listdir)
        if not most_recent_folder:
            return None
        
        inference_file_path = os.path.join(tpg_folder_path, most_recent_folder, "energy_data.json")
        return inference_file_path

    # open json, fetch_data, round values to the 4th, return dictionnary
    def fetch_data(self, file_path):
        try:
            with open(file_path, 'r') as file:
                data = json.load(file)

                # Recursive function to round values to 4 decimal places in the dictionary
                def round_values(d):
                    for key, value in d.items():
                        if isinstance(value, dict):
                            # Recursively round nested dictionaries
                            round_values(value)
                        elif isinstance(value, float):
                            # Round floats to 4 decimal places
                            d[key] = round(value, 4)
    
                # Round all the relevant float values in the data dictionary
                round_values(data)

                return data
        except FileNotFoundError:
            print(f"File not found: {file_path}")
            return {}
        except json.JSONDecodeError:
            print(f"Error decoding JSON from file: {file_path}")
            return {}


    def print_folder_data(self, folder_name, data_dict, print_all=False):
        data = data_dict.get(folder_name, {})
        if not data:
            print(f"No data found for folder: {folder_name}")
            return
        
        if print_all:
            print(json.dumps(data, indent=4))
        else:
            summary_data = data.get('summary', {})
            print(f"{folder_name} summary data:")
            print(json.dumps(summary_data, indent=4))


    # function to import the instruction level benchmarks 
    # -> retrieves summary section of last inference to date YYYY/MM/DD_HH/MM/SS folder for each operation folder 

    # "singleInstruction": {
    #   "singleInstructionExecutionTime": 809.96,
    #   "singleInstructionExecutionTimeUnit": "ns",
    #   "singleInstructionstdDevExecutionTime": 0.0,
    #   "singleInstructionEnergyConsumption": 68.52,
    #   "singleInstructionEnergyConsumptionUnit": "nJ",
    #   "singleInstructionstdDevEnergyConsumption": 1.0229
    # }

    def import_instruction_level_analysis(self, instructions_folder_path):
   
        # Check if the instructions_folder_path directory exists
        if not os.path.exists(instructions_folder_path):
            print(f"Error: The instructions_folder_path does not exist: {instructions_folder_path}")
            exit(1)

        # Get the list of subfolders (X, Y, Z, etc.) in the instructions_folder_path folder
        subfolders = [item for item in os.listdir(instructions_folder_path) if os.path.isdir(os.path.join(instructions_folder_path, item))]

        # Create a dictionary to store the single_instruction sections from energy_data.json
        dic_instruction_level_analysis = {}

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:
            # Construct the path to the inference folder (e.g., instructions_folder_path/X/inference)
            inference_path = os.path.join(instructions_folder_path, subfolder, "inference")

            if os.path.exists(inference_path) and os.path.isdir(inference_path):
                # Use BenchmarkUtils to find the most recent folder inside the inference folder
                most_recent_folder = self.find_most_recent_folder(os.listdir(inference_path))

                if most_recent_folder:
                    # Path to the energy_data.json file
                    energy_data_path = os.path.join(inference_path, most_recent_folder, "energy_data.json")

                    if os.path.exists(energy_data_path):
                        # Open and load the energy_data.json file
                        with open(energy_data_path, "r") as file:
                            energy_data = json.load(file)
                        
                        # Extract the 'singleInstruction' section from the energy_data.json file
                        if 'summary' in energy_data and 'singleInstruction' in energy_data['summary']:
                            #print(energy_data['summary'])
                            # singleInstruction is a key, it can be referenced direclty
                            dic_instruction_level_analysis[subfolder] = energy_data['summary']['singleInstruction']
                        else:
                            self.print_colored(f"No 'singleInstruction' section found in {energy_data_path}", "red")
                    else:
                        self.print_colored(f"energy_data.json not found in {inference_path}", "red")
                else:
                    self.print_colored(f"No recent folder found in {inference_path}", "red")
            else:
                self.print_colored(f"Inference path does not exist or is not a directory for {subfolder}", "red")

        return dic_instruction_level_analysis


    # shape of Graph traversal beanchmarks mc 

    # "1059961393" : 
	# {
	# 	"nbEvaluatedPrograms" : 11,
	# 	"nbEvaluatedTeams" : 6,
	# 	"nbExecutionForEachInstr" : 
	# 	{
	# 		"0" : 9,
	# 		"1" : 3,
	# 		"2" : 7,
	# 		"3" : 6,
	# 		"4" : 4
	# 	}
	# }

    # def bind_instrSet_dataType_to_seed(data: dic, instrSet_dataType: str):
    #     binded_data = {}
    #     for key in data:
    #         binded_data[(instrSet_dataType, key)] = data[key]
    #     return binded_data

    def import_graph_traversal_benchmarks_mc(self, tpg_folder_path):

        # Check if the tpg_folder_path directory exists
        if not os.path.exists(tpg_folder_path):
            print(f"Error: The tpg_folder_path does not exist: {tpg_folder_path}")
            exit(1)

        # Initialize an empty dictionary to store traversal information
        dic_graph_traversal_benchmarks_mc = {}

        # Get the list of subfolders (X, Y, Z, etc.) in the tpg folder
        subfolders = [item for item in os.listdir(tpg_folder_path) if os.path.isdir(os.path.join(tpg_folder_path, item))]

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:
            self.print_colored("importing " + str(subfolder), "blue")
            json_file_path = os.path.join(tpg_folder_path, subfolder, 'training', 'executionInfos.json')

            # Check if the JSON file exists
            if os.path.exists(json_file_path):
                try:
                    # Open and read the JSON file
                    with open(json_file_path, 'r') as file:
                        data = json.load(file)

                        # seed: {nbEvalProg, nbEvalTeams, ...} -> (double_base, seed): {nbEvalProg, nbEvalTeams, ...}
                        binded_data = (lambda data, instrSet_dataType: {(instrSet_dataType, key): value for key, value in data.items()})(data, subfolder)

                        # Update dic_graph_traversal_benchmarks_mc with data from the current file
                        dic_graph_traversal_benchmarks_mc.update(binded_data)
                except Exception as e:
                    print(f"Error reading {json_file_path}: {e}")
            else:
                print(f"No executionInfos.json found in {json_file_path}.")

        return dic_graph_traversal_benchmarks_mc


    # Shape of graph traversal analysis

    # "1125898167": {
    #     "singleTraversal": {
    #     "singleTraversalAverageExecutionTime": 71.6283,
    #     "singleTraversalStdDevExecutionTime": 0.0,
    #     "singleTraversalexecutionTimeUnit": "us",
    #     "singleTraversalAverageEnergyConsumption": 7.1353,
    #     "singleTraversalPooledstdDevEnergyConsumption": 2.9851,
    #     "singleTraversalEnergyConsumptionUnit": "uJ"
    #     }
    # }

    def import_graph_traversal_analysis(self, tpg_folder_path):

        # Initialize an empty dictionary to store traversal analysis
        dic_graph_traversal_analysis = {}

        # Get the list of subfolders (X, Y, Z, etc.) in the graph_traversal_informations folder
        subfolders = [item for item in os.listdir(tpg_folder_path) if os.path.isdir(os.path.join(tpg_folder_path, item))]

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:

            # Construct the path to the inference folder (e.g., tpg_folder_path/X/inference)
            inference_path = os.path.join(tpg_folder_path, subfolder, "inference")

            if os.path.exists(inference_path) and os.path.isdir(inference_path):
                # Use BenchmarkUtils to find the most recent folder inside the inference folder
                most_recent_folder = self.find_most_recent_folder(os.listdir(inference_path))

                if most_recent_folder:
                    # Path to the energy_data.json file
                    energy_data_path = os.path.join(inference_path, most_recent_folder, "energy_data.json")

                    if os.path.exists(energy_data_path):
                        # Open and load the energy_data.json file
                        with open(energy_data_path, "r") as file:
                            energy_data = json.load(file)
                            
                        # singleTraversal in the value under the key: seed_number. It is itself a dic
                        for seed_number, seed_data in energy_data.items():
                            if 'singleTraversal' in seed_data:
                                # Store data by seed number and subfolder
                                dic_graph_traversal_analysis[(subfolder, seed_number)] = seed_data['singleTraversal']
                            else:
                                print(f"No 'singleTraversal' section found for seed {seed_number} in {energy_data_path}")
                    else:
                        print(f"energy_data.json not found in {inference_path}")
                else:
                    print(f"No recent folder found in {inference_path}")
            else:
                print(f"Inference path does not exist or is not a directory for {subfolder}")

        return dic_graph_traversal_analysis


    def import_tpg_infos(self, tpg_folder_path):
        # Initialize an empty dictionary to store tpg infos
        dic_tpg_infos = {}

        # Get the list of subfolders (X, Y, Z, etc.) in the tpg_folder_path folder
        subfolders = [item for item in os.listdir(tpg_folder_path) if os.path.isdir(os.path.join(tpg_folder_path, item))]

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:
            # Construct the path to the training folder (e.g., tpg_folder_path/X/training)
            training_path = os.path.join(tpg_folder_path, subfolder, "training")

            if os.path.exists(training_path) and os.path.isdir(training_path):
                # Path to the tpgInfos.json file
                tpg_infos_path = os.path.join(training_path, "tpgInfos.json")

                if os.path.exists(tpg_infos_path):
                    # Open and load the tpgInfos.json file
                    with open(tpg_infos_path, "r") as file:
                        tpg_data = json.load(file)

                    # Ensure subfolder exists in dic_tpg_infos
                    dic_tpg_infos[subfolder] = {}

                    for teamNumber, nbOutgoingEdges in tpg_data.get("tpg", {}).items():
                        # Store data in dic_tpg_infos
                        dic_tpg_infos[subfolder][teamNumber] = nbOutgoingEdges
                else:
                    print(f"tpgInfos.json not found in {training_path}")
            else:
                print(f"Training path does not exist or is not a directory for {subfolder}")

        # Return the dictionary
        return dic_tpg_infos



    def print_colored(self, text, color_name):
        color_dict = {
            "orange": "\033[38;2;255;165;0m",
            "red": "\033[38;2;255;0;0m",
            "green": "\033[38;2;0;255;0m",
            "blue": "\033[38;2;0;0;255m",
            "yellow": "\033[38;2;255;255;0m",
            # Add more colors as needed
        }
        
        color_code = color_dict.get(color_name.lower(), "\033[0m")  # Defaults to reset if color not found
        reset_color = "\033[0m"
        print(f"{color_code}{text}{reset_color}")



    def compute_graph_traversal_estimations(self, graph_traversal_informations: dict, 
        instruction_level_analysis: dict, instructions: dict, dic_tpg_infos: dict):

        x_values = [1, 2, 3, 4, 5]
        y_values = [0.5717, 3.216, 4.7406, 6.2652, 7.7898]

        # Reshape x values to be a 2D array (required by sklearn)
        x = np.array(x_values).reshape(-1, 1)
        y = np.array(y_values)
        
        # Create and fit the linear regression model
        model = LinearRegression()
        model.fit(x, y)

        self.print_colored("div_double_asm_move_6reg_input1", "orange") #40 20
        graph_traversal_estimations = {}
        for key in graph_traversal_informations:
                
            # find cost of programs using instr individual cost and instruction usage
            instrSet_dataType = key[0]
            seed = key[1]
            graph_traversal_estimations[key] = {'program_latency': 0, 'team_latency': 0}
            for index, instruction in enumerate(instructions[instrSet_dataType]):
                if key[0] == "int_add":
                    #pourquoi +1
                    graph_traversal_estimations[key]['program_latency'] += \
                    graph_traversal_informations[key]['nbExecutionForEachInstr'][str(index+1)] *\
                    instruction_level_analysis[instruction]['singleInstructionExecutionTime']
                else:
                    graph_traversal_estimations[key]['program_latency'] += \
                    graph_traversal_informations[key]['nbExecutionForEachInstr'][str(index)] *\
                    instruction_level_analysis[instruction]['singleInstructionExecutionTime']

            graph_traversal_estimations[key]['program_latency'] = round(graph_traversal_estimations[key]['program_latency'], 4)

            # find cost of teams using linear Reg 
            # split traceTeamIds to get a list of values 
            traceTeamIds_char = graph_traversal_informations[key]['traceTeamIds'].split(", ")
            
            # number of outgoing edges for this team 
            traceTeamIds_int = [int(item) for item in traceTeamIds_char]
            #print(traceTeamIds_int)

            traceTIds_nbOutgEdges = list(map(lambda x: dic_tpg_infos[key[0]].get(str(x)), traceTeamIds_int))
            #print(traceTIds_nbOutgEdges)
                        
            # Predict the corresponding y value for the new x (traceTIds_nbOutgEdges)
            graph_traversal_estimations[key]['team_latency'] += round(model.predict(np.array(traceTIds_nbOutgEdges).reshape(-1,1)).sum()*1e3, 4)
    
        return graph_traversal_estimations


    def display_estimations_observed(self, graph_traversal_analysis, graph_traversal_estimations):
        for key in graph_traversal_analysis:
            if graph_traversal_estimations.get(key[1]) is not None:
                print("graph_traversal_analysis: " + str(round(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'],4)))
                print("graph_traversal_estimations:" + str(round(graph_traversal_estimations[key[1]], 4)  ))
                print("ratio:" + str(round(graph_traversal_analysis[key]['singleTraversalAverageExecutionTime'] / (graph_traversal_estimations[key[1]]), 4)) + "\n")


    # Mean Squared Error (MSE): measures the average squared difference 
    # between predicted values and the actual values in the dataset.
    def MSE(self, observed_values :dict, predicted_values: dict, str_TPG_graph: str):
        # if len(observed_values) != len(predicted_values):
        #     raise ValueError("dict a and dict b must have the same length")
        #     return 
        n = 0
        MSE = 0 
        for key in observed_values:
            if key[0] == str_TPG_graph and predicted_values.get(key) is not None:
                # print(str(observed_values[key]['singleTraversalAverageExecutionTime']) + "  " + str(predicted_values[key[1]]))
                MSE += pow((observed_values[key]['singleTraversalAverageExecutionTime'] - predicted_values[key]), 2)
                n+=1
        if n != 0:
            MSE = round(MSE/n,4)
        return MSE

    # Mean Absolute Percentage Error (MAPE): common metric where the absolute error 
    # between the estimated and observed values is expressed as a percentage of the 
    # observed values, and then the average of these percentages is taken.
    def MAPE(self, observed_values :dict, predicted_values: dict, str_TPG_graph: str):
        # if len(observed_values) != len(predicted_values):
        #     raise ValueError("dict a and dict b must have the same length")
        #     return 
        n = 0
        MAPE = 0 
        for key in observed_values:
            if key[0] == str_TPG_graph and predicted_values.get(key) is not None:
                observed = observed_values[key]['singleTraversalAverageExecutionTime'] 
                predicted = predicted_values[key]
                MAPE += abs((observed - predicted)/observed)
                n+=1
        if n != 0:
            MAPE = round(MAPE/n,4)
        return MAPE