import matplotlib.pyplot as plt
import os

def parse_output(directory):
    times = []
    for filename in sorted(os.listdir(directory)):
        if filename.startswith("output_"):
            with open(os.path.join(directory, filename)) as f:
                for line in f:
                    if "Execution time" in line:
                        time = float(line.split()[-1])
                        times.append(time)
    return times

# Strong scaling
strong_scaling_dir = "results/mpi_strong_scaling"
strong_scaling_times = parse_output(strong_scaling_dir)
processes_strong = [1, 2, 4, 8, 16, 32]

# Weak scaling
weak_scaling_dir = "results/mpi_weak_scaling"
weak_scaling_times = parse_output(weak_scaling_dir)
processes_weak = [1, 2, 4, 8]

# Plotting Strong Scaling
plt.figure()
plt.plot(processes_strong, strong_scaling_times, marker='o')
plt.xlabel('Number of Processes')
plt.ylabel('Execution Time (s)')
plt.title('Strong Scaling')
plt.grid(True)
plt.savefig('results/strong_scaling.png')

# Plotting Weak Scaling
plt.figure()
plt.plot(processes_weak, weak_scaling_times, marker='o')
plt.xlabel('Number of Processes')
plt.ylabel('Execution Time (s)')
plt.title('Weak Scaling')
plt.grid(True)
plt.savefig('results/weak_scaling.png')

plt.show()
