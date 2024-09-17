import os
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# description : script for mutliples seeds energy and latency benchmarks plots, shows distribution of the data
# Generate latency distribution (percentage of samples for each fraction of the latency)

# Import BenchmarkUtils class
from benchmarkUtils import BenchmarkUtils

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

        print(data_dict)
    else:
        print(f"inference file path not found for {folder_name}")

# Colors from the original script
bright_color1 = '#FFB3E5'  # Pink color
background_color = '#5585BF'  # Background color

# Define the total number of samples
total_samples = 1500

# Create plots for each folder
for folder_name, folder_data in data_dict.items():
    # Extract the timing data
    timings = folder_data.get('meanTiming', [])
    
    if not timings:
        print(f"No timing data available for folder: {folder_name}")
        continue
    
    # Convert to a NumPy array
    timings_array = np.array(timings)

    # Find the unique values
    unique_values = np.unique(timings_array)

    print(timings_array)

    # Count the number of unique values
    num_unique_values = len(unique_values)

    print(f'There are {num_unique_values} different unique values in the latency array.')
        
    # Define the histogram bins
    num_bins = 100
    min_timing, max_timing = np.min(timings_array), np.max(timings_array)
    bins = np.linspace(min_timing, max_timing, num_bins + 1)
    
    # Plotting
    fig, ax = plt.subplots(figsize=(10, 7))
    
    # Set the figure and axis background colors
    fig.patch.set_facecolor(background_color)
    ax.set_facecolor(background_color)
    
    # Create the histogram with normalization to show percentages
    sns.histplot(timings_array, kde=False, bins=bins, color=bright_color1, edgecolor=bright_color1, stat='percent', label="on board measurements", alpha=0.5, ax=ax)
    
    # Set title, labels, and colors
    ax.set_title(f'Latency Distribution for {folder_name}', color='white', fontsize=24)
    ax.set_xlabel('Latency (us)', color='white', fontsize=10)
    ax.set_ylabel('Percentage of Samples (%)', color='white', fontsize=10)
    
    # Customize tick parameters for white color and larger font size
    ax.tick_params(colors='white', labelsize=5)
    
    # Set the x-tick positions and their labels with rotation
    ax.set_xticks(bins)
    ax.set_xticklabels([f'{int(b)}' for b in bins], rotation=45, color='white')
    
    # Customize the spines for white color
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['bottom'].set_color('white')
    ax.spines['left'].set_color('white')
    
    # Add a legend with white background and black text
    legend = plt.legend(facecolor='white', edgecolor='white', fontsize=16)
    plt.setp(legend.get_texts(), color='black')
    
    # Save the plot
    plt.tight_layout()
    #plt.savefig(f'{folder_name}_latency_histogram.png')
    #plt.close()
    
    print(f'Plot saved for folder: {folder_name}')
    plt.show()
