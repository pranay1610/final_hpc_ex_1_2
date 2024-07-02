#!/bin/bash
# OMP Weak Scaling: Increase problem size proportionally to the number of OMP threads

output_dir="results/omp_weak_scaling"
mkdir -p $output_dir

declare -a sizes=("4096 4096" "5792 5792" "8192 8192" "11584 11584")

for idx in ${!sizes[@]}; do
    threads=$((2**idx))
    export OMP_NUM_THREADS=$threads
    problem_size="${sizes[$idx]} -2.0 -2.0 2.0 2.0 255"
    echo "Running with $threads OMP threads"
    ./mandelbrot $problem_size > $output_dir/output_${threads}.txt 2>&1
    mv mandelbrot.pgm $output_dir/mandelbrot_${threads}.pgm
done
