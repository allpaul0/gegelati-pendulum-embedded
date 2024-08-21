import os

# Import BenchmarkUtils class
from benchmarkUtils import BenchmarkUtils

import numpy as np
import matplotlib.pyplot as plt

# Initialize the class with the base folder path
utils = BenchmarkUtils(base_path=os.getcwd())

base_TPG_folder = "TPG_10v"

# Get a list of all folders in TPG_10v
folder_names = [item for item in os.listdir(os.path.join(os.getcwd(), base_TPG_folder)) if os.path.isdir(os.path.join(os.getcwd(), "TPG_10v", item))]

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

# Iterate over the data dictionary to print power and timing lists
for folder_name, folder_data in data_dict.items():
    print(f"Folder: {folder_name}")
    
    # Extract power and timing lists from the data
    power_list = folder_data.get('meanPower', [])
    timing_list = folder_data.get('meanTiming', [])
    
    print("Power List (Watts):")
    print(power_list)
    
    print("Timing List (us):")
    print(timing_list)

# Create plots for each folder
for folder_name, folder_data in data_dict.items():
    # Extract the timing data
    timings = folder_data.get('meanTiming', [])
    
    if not timings:
        print(f"No timing data available for folder: {folder_name}")
        continue
    
    # Convert to a NumPy array
    timings_array = np.array(timings)
    
    # Determine the min and max values for timing
    min_timing = np.min(timings_array)
    max_timing = np.max(timings_array)
    
    # Define the number of bins (sections)
    num_bins = 10
    
    # Create the bins and compute the histogram
    bins = np.linspace(min_timing, max_timing, num_bins + 1)
    histogram, _ = np.histogram(timings_array, bins=bins)
    
    # Plotting
    plt.figure(figsize=(10, 6))
    plt.bar(bins[:-1], histogram, width=np.diff(bins), edgecolor='black', align='edge')
    plt.xlabel('Latency (us)')
    plt.ylabel('Number of Samples')
    plt.title(f'Histogram of Latency for {folder_name}')
    plt.xticks(bins, rotation=45)
    plt.grid(axis='y')
    
    # Save the plot
    plt.tight_layout()
    plt.savefig(f'{folder_name}_latency_histogram.png')
    plt.close()
    
    print(f'Plot saved for folder: {folder_name}')
