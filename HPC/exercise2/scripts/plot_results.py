import matplotlib.pyplot as plt

# Read the data
tasks = []
times = []
with open('results.txt', 'r') as file:
    next(file)  # Skip header line
    for line in file:
        parts = line.split()
        tasks.append(int(parts[0]))
        times.append(float(parts[1]))

# Plot the data
plt.plot(tasks, times, marker='o')
plt.xlabel('Number of Tasks')
plt.ylabel('Time (seconds)')
plt.title('MPI Gather Operation Performance')
plt.grid(True)
plt.savefig('performance_plot.png')
plt.show()
