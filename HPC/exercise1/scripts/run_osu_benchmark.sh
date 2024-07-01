#!/bin/bash

#SBATCH --job-name=osu_benchmark
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=128
#SBATCH --time=02:00:00
#SBATCH --output=/orfeo/cephfs/home/dssc/pnarsipuram/final_hpc_ex_1_2/HPC/exercise1/results/osu_benchmark_results.out
#SBATCH -A dssc
#SBATCH -p EPYC

module load openMPI/4.1.5/gnu/12.2.1

OSU_PATH=/orfeo/cephfs/home/dssc/pnarsipuram/final_hpc_ex_1_2/HPC/osu-micro-benchmarks-7.4/c/mpi/collective

for benchmark in osu_bcast osu_scatter; do
    for size in 1000 10000 100000; do
        for map in core socket; do
            mpirun -np 256 --map-by $map $OSU_PATH/blocking/$benchmark -m $size >> /orfeo/cephfs/home/dssc/pnarsipuram/final_hpc_ex_1_2/HPC/exercise1/results/osu_${benchmark}_${size}_${map}.out
        done
    done
done

