import os
import json
from datetime import datetime

def find_most_recent_folder(folder_list):
    # Parse the folder names into datetime objects
    date_format = "%Y-%m-%d_%H-%M-%S"
    date_folders = [(datetime.strptime(folder, date_format), folder) for folder in folder_list]
    
    # Find the folder with the most recent datetime
    most_recent_folder = max(date_folders, key=lambda x: x[0])[1]
    
    return most_recent_folder

def fetch_data(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)
        return data

def construct_file_path(folder_name):
    # Find specified folder path
    base_path = os.getcwd()
    suffix_path = "TPG_microbenchmarks/" + folder_name + "/inference/"
    folder_path = os.path.join(base_path, suffix_path)
    folder_listdir = os.listdir(folder_path)
    
    # Retrieve most recent folder
    most_recent_folder = find_most_recent_folder(folder_listdir)
    inference_file_path = os.path.join(folder_path, most_recent_folder, "energy_data.json")
    
    return inference_file_path

def print_folder_data(folder_name, data_dict, print_all=False):
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

# Get a list of all folders in TPG_microbenchmarks
base_folder_path = os.path.join(os.getcwd(), "TPG_microbenchmarks")
folder_names = os.listdir(base_folder_path)

# Create a dictionary to store data for each folder
data_dict = {}

# Loop through each folder and fetch data
for folder_name in folder_names:
    # Construct the file path for the current folder
    inference_file_path = construct_file_path(folder_name)
    
    # Fetch data from the file
    folder_data = fetch_data(inference_file_path)
    
    # Store the data in the dictionary
    data_dict[folder_name] = folder_data

# Print the summary data for each folder by default
for folder_name in data_dict.keys():
    print_folder_data(folder_name, data_dict)

# Example of how to print all data for a specific folder
# print_folder_data('div_int', data_dict, print_all=True)

#div_int_summary_execution_time = 
#div_int_summary_energy_consumption = 


# Ce script est utilisé pour déduire le coût de l'opération mov, indispensable en assembleur pour boucler.
print("ExecutionTime:", data_dict['div_int']['summary']['overall']['executionTime'] - ((1e6 * data_dict['mov_int']['summary']['singleInstruction']['singleInstructionExecutionTime'])/1e3))
print("EnergyConsumption:", data_dict['div_int']['summary']['overall']['energyConsumption'] - ((1e6 * data_dict['mov_int']['summary']['singleInstruction']['singleInstructionEnergyConsumption'])/1e6))