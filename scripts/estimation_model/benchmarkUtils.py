import os
import json
import re
from datetime import datetime

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
        folder_path = os.path.join(self.base_path, base_folder, folder_name, sub_dir)
        
        if not os.path.exists(folder_path):
            print(f"Path does not exist: {folder_path}")
            return None
        
        folder_listdir = os.listdir(folder_path)
        if not folder_listdir:
            print(f"No subfolders found in: {folder_path}")
            return None
        
        most_recent_folder = self.find_most_recent_folder(folder_listdir)
        if not most_recent_folder:
            return None
        
        inference_file_path = os.path.join(folder_path, most_recent_folder, "energy_data.json")
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

    def import_instruction_level_analysis(self, instruction_level_analysis_folder):
   
        # Check if the instruction_level_analysis_folder directory exists
        if not os.path.exists(instruction_level_analysis_folder):
            print(f"Error: The instruction_level_analysis_folder does not exist: {instruction_level_analysis_folder}")
            exit(1)

        # Get the list of subfolders (X, Y, Z, etc.) in the instruction_level_analysis_folder folder
        subfolders = [item for item in os.listdir(instruction_level_analysis_folder) if os.path.isdir(os.path.join(instruction_level_analysis_folder, item))]

        # Create a dictionary to store the single_instruction sections from energy_data.json
        dic_instruction_level_analysis = {}

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:
            # Construct the path to the inference folder (e.g., instruction_level_analysis_folder/X/inference)
            inference_path = os.path.join(instruction_level_analysis_folder, subfolder, "inference")

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
                            print(f"No 'singleInstruction' section found in {energy_data_path}")
                    else:
                        print(f"energy_data.json not found in {inference_path}")
                else:
                    print(f"No recent folder found in {inference_path}")
            else:
                print(f"Inference path does not exist or is not a directory for {subfolder}")

        return dic_instruction_level_analysis

    # Graph traversal informations

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

    def import_graph_traversal_informations(self, graph_traversal_informations_folder):

        # Check if the graph_traversal_informations_folder directory exists
        if not os.path.exists(graph_traversal_informations_folder):
            print(f"Error: The graph_traversal_informations_folder does not exist: {graph_traversal_informations_folder}")
            exit(1)

        # Initialize an empty dictionary to store traversal information
        dic_graph_traversal_informations = {}

        # Get the list of subfolders (X, Y, Z, etc.) in the graph_traversal_informations folder
        subfolders = [item for item in os.listdir(graph_traversal_informations_folder) if os.path.isdir(os.path.join(graph_traversal_informations_folder, item))]

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:

            json_file_path = os.path.join(graph_traversal_informations_folder, subfolder, 'CodeGen', 'executionInfos.json')

            # Check if the JSON file exists
            if os.path.exists(json_file_path):
                try:
                    # Open and read the JSON file
                    with open(json_file_path, 'r') as file:
                        data = json.load(file)
                        
                        # Update dic_graph_traversal_informations with data from the current file
                        dic_graph_traversal_informations.update(data)
                except Exception as e:
                    print(f"Error reading {json_file_path}: {e}")
            else:
                print(f"No executionInfos.json found in {json_file_path}.")

        return dic_graph_traversal_informations

    # Graph traversal analysis

    # "singleTraversal": {
    #         "singleTraversalAverageExecutionTime": 71.628,
    #         "singleTraversalStdDevExecutionTime": 0.0,
    #         "singleTraversalexecutionTimeUnit": "us",
    #         "singleTraversalAverageEnergyConsumption": 7.2036,
    #         "singleTraversalPooledstdDevEnergyConsumption": 0.0,
    #         "singleTraversalEnergyConsumptionUnit": "uJ"
    # }

    def import_graph_traversal_analysis(self, graph_traversal_analysis_folder):

        # Initialize an empty dictionary to store traversal analysis
        dic_graph_traversal_analysis = {}

        # Get the list of subfolders (X, Y, Z, etc.) in the graph_traversal_informations folder
        subfolders = [item for item in os.listdir(graph_traversal_analysis_folder) if os.path.isdir(os.path.join(graph_traversal_analysis_folder, item))]

        # Loop through each subfolder (X, Y, Z)
        for subfolder in subfolders:

            # Construct the path to the inference folder (e.g., graph_traversal_analysis_folder/X/inference)
            inference_path = os.path.join(graph_traversal_analysis_folder, subfolder, "inference")

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

                        # Extract the 'singleTraversal' section from the energy_data.json file
                        if 'summary' in energy_data:
                            # print(energy_data['summary'].items())
                            # singleTraversal in the value under the key: seed_number. It is itself a dic
                            for seed_number, seed_data in energy_data['summary'].items():
                                if 'singleTraversal' in seed_data:
                                    # Store data by seed number and subfolder
                                    dic_graph_traversal_analysis[(subfolder, seed_number)] = seed_data['singleTraversal']
                                else:
                                    print(f"No 'singleTraversal' section found for seed {seed_number} in {energy_data_path}")
                        else:
                            print(f"No 'summary' section found in {energy_data_path}")
                    else:
                        print(f"energy_data.json not found in {inference_path}")
                else:
                    print(f"No recent folder found in {inference_path}")
            else:
                print(f"Inference path does not exist or is not a directory for {subfolder}")

        return dic_graph_traversal_analysis
