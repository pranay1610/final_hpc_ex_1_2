#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <mpi.h>
#include <omp.h>

#define MAX_COLOR 65535

void write_pgm_image(const char *filename, int *data, int width, int height, int max_val) {
    FILE *file = fopen(filename, "wb");
    fprintf(file, "P5\n%d %d\n%d\n", width, height, max_val);
    for (int i = 0; i < width * height; i++) {
        short val = (short)data[i];
        fwrite(&val, sizeof(short), 1, file);
    }
    fclose(file);
}

int mandelbrot(double complex c, int max_iter) {
    double complex z = 0;
    int iter;
    for (iter = 0; iter < max_iter; iter++) {
        if (cabs(z) > 2.0) break;
        z = z*z + c;
    }
    return iter;
}

int main(int argc, char *argv[]) {
    if (argc != 8) {
        fprintf(stderr, "Usage: %s n_x n_y x_L y_L x_R y_R I_max\n", argv[0]);
        return 1;
    }

    int n_x = atoi(argv[1]);
    int n_y = atoi(argv[2]);
    double x_L = atof(argv[3]);
    double y_L = atof(argv[4]);
    double x_R = atof(argv[5]);
    double y_R = atof(argv[6]);
    int I_max = atoi(argv[7]);

    int rank, size;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Process %d of %d starting.\n", rank, size);

    int rows_per_process = n_y / size;
    int *local_data = malloc(rows_per_process * n_x * sizeof(int));

    double dx = (x_R - x_L) / n_x;
    double dy = (y_R - y_L) / n_y;

    #pragma omp parallel for schedule(dynamic)
    for (int j = 0; j < rows_per_process; j++) {
        for (int i = 0; i < n_x; i++) {
            double x = x_L + i * dx;
            double y = y_L + (rank * rows_per_process + j) * dy;
            double complex c = x + y * I;
            local_data[j * n_x + i] = mandelbrot(c, I_max);
        }
    }

    printf("Process %d completed computation.\n", rank);

    int *data = NULL;
    if (rank == 0) {
        data = malloc(n_x * n_y * sizeof(int));
    }

    MPI_Gather(local_data, rows_per_process * n_x, MPI_INT, data, rows_per_process * n_x, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (n_y % size != 0) {
            int remaining_rows = n_y % size;
            int offset = size * rows_per_process;
            #pragma omp parallel for
            for (int j = 0; j < remaining_rows; j++) {
                for (int i = 0; i < n_x; i++) {
                    double x = x_L + i * dx;
                    double y = y_L + (offset + j) * dy;
                    double complex c = x + y * I;
                    data[(offset + j) * n_x + i] = mandelbrot(c, I_max);
                }
            }
        }
        write_pgm_image("mandelbrot.pgm", data, n_x, n_y, I_max);
        free(data);
        printf("Output written to mandelbrot.pgm\n");
    }

    free(local_data);
    MPI_Finalize();
    return 0;
}

