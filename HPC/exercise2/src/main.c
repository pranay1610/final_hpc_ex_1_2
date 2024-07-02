#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "image_utils.h"

int main(int argc, char *argv[]) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    if (provided < MPI_THREAD_FUNNELED) {
        printf("Error: MPI does not provide needed threading level\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 8) {
        if (rank == 0) {
            printf("Usage: %s n_x n_y x_L y_L x_R y_R I_max\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    
    int n_x = atoi(argv[1]);
    int n_y = atoi(argv[2]);
    double x_L = atof(argv[3]);
    double y_L = atof(argv[4]);
    double x_R = atof(argv[5]);
    double y_R = atof(argv[6]);
    int I_max = atoi(argv[7]);
    
    int local_n_x = n_x / size;
    int start_x = rank * local_n_x;
    int end_x = (rank + 1) * local_n_x;

    unsigned char *local_matrix = (unsigned char *) malloc(local_n_x * n_y * sizeof(unsigned char));
    if (!local_matrix) {
        printf("Error: Unable to allocate memory for the matrix\n");
        MPI_Finalize();
        return 1;
    }

    compute_mandelbrot(local_matrix, start_x, end_x, n_y, x_L, y_L, x_R, y_R, I_max, n_x);

    unsigned char *global_matrix = NULL;
    if (rank == 0) {
        global_matrix = (unsigned char *) malloc(n_x * n_y * sizeof(unsigned char));
    }

    MPI_Gather(local_matrix, local_n_x * n_y, MPI_UNSIGNED_CHAR, global_matrix, local_n_x * n_y, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        write_pgm_image("mandelbrot.pgm", global_matrix, n_x, n_y, 255);
        free(global_matrix);
    }

    free(local_matrix);
    MPI_Finalize();
    return 0;
}
