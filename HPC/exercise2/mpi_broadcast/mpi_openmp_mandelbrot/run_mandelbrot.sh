#!/bin/bash
#SBATCH --job-name=strong_scaling_mandelbrot
#SBATCH --output=strong_scaling_output.txt
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16  # Update this for each run (1, 2, 4, 8, 16)
#SBATCH --time=00:10:00
#SBATCH --partition=EPYC

module load openMPI/4.1.5/gnu/12.2.1

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

mpirun ./mpi_openmp_mandelbrot 1000 1000 -2.0 -2.0 2.0 2.0 1000

