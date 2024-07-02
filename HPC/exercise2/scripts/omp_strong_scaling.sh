#!/bin/bash
# OMP Strong Scaling: Run with a fixed problem size and varying number of OMP threads

problem_size="4096 4096 -2.0 -2.0 2.0 2.0 255"
output_dir="results/omp_strong_scaling"
mkdir -p $output_dir

for threads in 1 2 4 8 16 32; do
    export OMP_NUM_THREADS=$threads
    echo "Running with $threads OMP threads"
    ./mandelbrot $problem_size > $output_dir/output_${threads}.txt 2>&1
    mv mandelbrot.pgm $output_dir/mandelbrot_${threads}.pgm
done
