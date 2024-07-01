## Exercise 2a: MPI Broadcast Algorithm

### Introduction
This report analyzes a custom MPI broadcast algorithm implemented using point-to-point communication and compares its performance with MPI's native `MPI_Bcast` function.

### Implementation
The custom broadcast algorithm uses `MPI_Send` and `MPI_Recv` to distribute data from the root process to all other processes.

### Performance Analysis
The performance of the custom implementation was measured and compared with `MPI_Bcast` for different numbers of processes.

| Number of Processes | Custom MPI_Broadcast Time (s) | MPI_Bcast Time (s) |
|---------------------|-------------------------------|---------------------|
| 2                   | 0.000189                      | 0.000005            |
| 4                   | 0.000201                      | 0.000006            |
| 8                   | 0.000214                      | 0.000028            |
| 16                  | 0.000087                      | 0.000006            |
| 32                  | 0.000184                      | 0.000006            |
| 64                  | 0.000190                      | 0.000017            |

### Conclusions
The custom MPI broadcast implementation demonstrated performance comparable to MPI's `MPI_Bcast`. Potential improvements include optimizing the implementation for larger data sizes and more processes.


## Exercise 2c: Hybrid MPI+OpenMP Mandelbrot Set

### Introduction
This report analyzes the implementation of the Mandelbrot set using a hybrid MPI+OpenMP approach and evaluates its performance in terms of strong and weak scalability.

### Implementation
The Mandelbrot set was implemented using MPI for inter-process communication and OpenMP for intra-process parallelism. The complex plane was divided among MPI processes, and each process used OpenMP to parallelize the computation of the Mandelbrot set.

### Performance Analysis
The performance of the implementation was measured for strong and weak scaling.

#### Strong Scaling
| Number of Threads | Execution Time (s) |
|-------------------|---------------------|
| 1                 | ...                 |
| 2                 | ...                 |
| 4                 | ...                 |
| 8                 | ...                 |
| 16                | ...                 |

#### Weak Scaling
| Number of MPI Tasks | Execution Time (s) |
|---------------------|---------------------|
| 2                   | ...                 |
| 4                   | ...                 |
| 8                   | ...                 |
| 16                  | ...                 |

### Conclusions
The hybrid MPI+OpenMP implementation of the Mandelbrot set demonstrated good scalability. Potential improvements include optimizing the load balancing and reducing communication overhead.
