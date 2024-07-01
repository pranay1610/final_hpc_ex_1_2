#!/bin/bash

#SBATCH --job-name=mpi_broadcast
#SBATCH --output=mpi_broadcast_output.txt
#SBATCH --ntasks=64  # Update this line for different numbers of tasks
#SBATCH --time=00:05:00
#SBATCH --partition=EPYC

module load openMPI/4.1.5/gnu/12.2.1

mpirun ./mpi_broadcast
