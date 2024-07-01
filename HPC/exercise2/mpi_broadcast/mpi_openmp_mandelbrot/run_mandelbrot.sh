#!/bin/bash
#SBATCH --job-name=mpi_openmp_mandelbrot
#SBATCH --output=mandelbrot_output.txt
#SBATCH --ntasks=4           # Number of MPI tasks
#SBATCH --cpus-per-task=4    # Number of OpenMP threads per MPI task
#SBATCH --time=00:10:00
#SBATCH --partition=EPYC

module load openMPI/4.1.5/gnu/12.2.1

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

mpirun ./mpi_openmp_mandelbrot 1000 1000 -2.0 -2.0 2.0 2.0 1000
