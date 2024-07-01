#!/bin/bash
#SBATCH --job-name=weak_scaling_mandelbrot
#SBATCH --output=weak_scaling_output.txt
#SBATCH --ntasks=16           # Update this for each run (2, 4, 8, 16)
#SBATCH --cpus-per-task=1
#SBATCH --nodes=2            # Ensure using at least 2 nodes
#SBATCH --time=00:10:00
#SBATCH --partition=EPYC

module load openMPI/4.1.5/gnu/12.2.1

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

mpirun ./mpi_openmp_mandelbrot 2000 2000 -2.0 -2.0 2.0 2.0 1000  # Increase problem size proportionally

