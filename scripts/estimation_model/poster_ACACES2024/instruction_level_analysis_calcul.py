import os

# Import BenchmarkUtils class
from benchmarkUtils import BenchmarkUtils

# script used to do computation on instruction level analysis  

# Initialize the class with the base folder path
utils = BenchmarkUtils(base_path=os.getcwd())

base_TPG_folder = "TPG_microbenchmarks"

# Get a list of all folders in TPG_microbenchmarks
folder_names = os.listdir(os.path.join(os.getcwd(), base_TPG_folder))

# Create a dictionary to store data for each folder
data_dict = {}

# Loop through each TPG folder and fetch data
for folder_name in folder_names:
    # Construct the file path for the current folder
    inference_file_path = utils.construct_file_path(base_TPG_folder, folder_name, "inference")
    
    if inference_file_path:
        # Fetch data from the file
        folder_data = utils.fetch_data(inference_file_path)
        
        # Store the data in the dictionary
        data_dict[folder_name] = folder_data

# Print the summary data for each folder by default
for folder_name in data_dict.keys():
    utils.print_folder_data(folder_name, data_dict)

# Example: Calculate Execution Time and Energy Consumption difference between div_int and mov_int
if 'div_int' in data_dict and 'mov_int' in data_dict:
    div_execution_time = data_dict['div_int']['summary']['overall']['executionTime']
    mov_execution_time = data_dict['mov_int']['summary']['singleInstruction']['singleInstructionExecutionTime']
    
    execution_time_diff = div_execution_time - ((1e6 * mov_execution_time) / 1e3)
    print("ExecutionTime:", execution_time_diff)
    
    div_energy_consumption = data_dict['div_int']['summary']['overall']['energyConsumption']
    mov_energy_consumption = data_dict['mov_int']['summary']['singleInstruction']['singleInstructionEnergyConsumption']
    
    energy_consumption_diff = div_energy_consumption - ((1e6 * mov_energy_consumption) / 1e6)
    print("EnergyConsumption:", energy_consumption_diff)
