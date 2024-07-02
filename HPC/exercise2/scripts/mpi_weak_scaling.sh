#!/bin/bash
# MPI Weak Scaling: Increase problem size proportionally to the number of MPI processes

output_dir="results/mpi_weak_scaling"
mkdir -p $output_dir

declare -a sizes=("4096 4096" "5792 5792" "8192 8192" "11584 11584")

for idx in ${!sizes[@]}; do
    np=$((2**idx))
    problem_size="${sizes[$idx]} -2.0 -2.0 2.0 2.0 255"
    echo "Running with $np MPI processes"
    mpirun -np $np ./mandelbrot $problem_size > $output_dir/output_${np}.txt 2>&1
    mv mandelbrot.pgm $output_dir/mandelbrot_${np}.pgm
done
