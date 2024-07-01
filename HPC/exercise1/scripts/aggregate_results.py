import os
import pandas as pd

def aggregate_results(directory):
    data = []
    for filename in os.listdir(directory):
        if filename.endswith(".out"):
            print(f"Processing file: {filename}")
            parts = filename.split('_')
            if len(parts) < 4:
                print(f"Skipping file: {filename}")
                continue
            benchmark = parts[1]
            size = parts[2]
            map_by = parts[3].split('.')[0]
            with open(os.path.join(directory, filename), 'r') as f:
                for line in f:
                    if "Size" in line or "#" in line or not line.strip():
                        continue  # Skip header lines, comments, and empty lines
                    parts = line.split()
                    if len(parts) == 2:
                        try:
                            size_value = int(parts[0])
                            latency = float(parts[1])
                            data.append({
                                'benchmark': benchmark,
                                'size': int(size),
                                'map_by': map_by,
                                'size_value': size_value,
                                'latency': latency
                            })
                            print(f"Added data: {data[-1]}")
                        except ValueError as e:
                            print(f"Skipping line due to ValueError: {line.strip()}, {e}")
                    else:
                        print(f"Skipping line with unexpected format: {line.strip()}")
    df = pd.DataFrame(data)
    df.to_csv(os.path.join(directory, 'aggregated_osu_results.csv'), index=False)
    print("Aggregation complete. CSV file created.")

if __name__ == "__main__":
    aggregate_results('/orfeo/cephfs/home/dssc/pnarsipuram/final_hpc_ex_1_2/HPC/exercise1/results')

