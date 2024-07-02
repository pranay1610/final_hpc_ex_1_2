#!/bin/bash
# MPI Strong Scaling: Run with a fixed problem size and varying number of MPI processes

problem_size="4096 4096 -2.0 -2.0 2.0 2.0 255"
output_dir="results/mpi_strong_scaling"
mkdir -p $output_dir

for np in 1 2 4 8 16 32; do
    echo "Running with $np MPI processes"
    mpirun -np $np ./mandelbrot $problem_size > $output_dir/output_${np}.txt 2>&1
    mv mandelbrot.pgm $output_dir/mandelbrot_${np}.pgm
done
