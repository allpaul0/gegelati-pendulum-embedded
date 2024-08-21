import os
import json
import re
from datetime import datetime

class BenchmarkUtils:
    def __init__(self, base_path):
        self.base_path = base_path

    def find_most_recent_folder(self, folder_list):
        date_format = "%Y-%m-%d_%H-%M-%S"
        date_folders = []
        
        for folder in folder_list:
            try:
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
        
        inference_file_path = os.path.join(folder_path, most_recent_folder, "energy_data2.json")
        return inference_file_path

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

    def parse_logs(self, log_data):
        power_pattern = re.compile(r"Step\s+Current\s+Power\n(?:[^\n]+\n)+?(?:[\d-]+\s+[^\s]+\s+([^\s]+))")
        t_avg_pattern = re.compile(r"=== T_avg : ([\d.]+) us")
        
        power_matches = power_pattern.findall(log_data)
        t_avg_matches = t_avg_pattern.findall(log_data)
        
        if not power_matches or not t_avg_matches:
            print("No power or T_avg data found in logs.")
            return []
        
        energy_consumptions = []
        
        for i in range(len(t_avg_matches)):
            t_avg = float(t_avg_matches[i]) * 1e-6
            power_values = [float(p) for p in power_matches[i * len(power_matches) // len(t_avg_matches): (i + 1) * len(power_matches) // len(t_avg_matches)]]
            
            if len(power_values) <= 1:
                print("Insufficient power values for computation.")
                continue
            
            power_values = power_values[1:]
            avg_power = sum(power_values) / len(power_values)
            energy = avg_power * t_avg
            energy_consumptions.append(energy)
        
        return energy_consumptions

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
