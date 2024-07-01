#!/bin/bash
#SBATCH --job-name=mpi_gather
#SBATCH --output=mpi_gather_output.txt
#SBATCH --ntasks=64
#SBATCH --time=00:10:00
#SBATCH --partition=EPYC

module load openMPI/4.1.5/gnu/12.2.1

mpirun ./mpi_gather
