import os
import json
from benchmarkUtils import BenchmarkUtils

# used to aggregate the intruction level benchmarks and display them in a file
# Allows the user to visualise every instruction level analysis in a single file

# Instantiate BenchmarkUtils class with current working directory 
utils = BenchmarkUtils(base_path=os.path.join(os.getcwd()))

# Use the method import_instruction_level_analysis from the utils object
single_instruction_data = utils.import_instruction_level_analysis("TPG_microbenchmarks")

# Path to save the new JSON file with all single_instruction sections
output_path = os.path.join(base_folder, "consolidated_single_instruction_data.json")

# Save the single_instruction_data dictionary to a new JSON file
with open(output_path, "w") as outfile:
    json.dump(single_instruction_data, outfile, indent=4)

print(f"Consolidated single_instruction data saved to {output_path}")
