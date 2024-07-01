#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 100
#define REPETITIONS 1000

void mpi_broadcast(int *data, int data_size, int root, MPI_Comm comm) {
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    if (rank == root) {
        for (int i = 0; i < size; i++) {
            if (i != root) {
                MPI_Send(data, data_size, MPI_INT, i, 0, comm);
            }
        }
    } else {
        MPI_Recv(data, data_size, MPI_INT, root, 0, comm, MPI_STATUS_IGNORE);
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[DATA_SIZE];
    double start_time, end_time;

    // Initialize data only on the root process
    if (rank == 0) {
        for (int i = 0; i < DATA_SIZE; i++) {
            data[i] = i;
        }
    }

    // Measure time for custom MPI_Broadcast
    start_time = MPI_Wtime();
    for (int i = 0; i < REPETITIONS; i++) {
        mpi_broadcast(data, DATA_SIZE, 0, MPI_COMM_WORLD);
    }
    end_time = MPI_Wtime();
    if (rank == 0) {
        printf("Custom MPI_Broadcast time: %f seconds\n", (end_time - start_time) / REPETITIONS);
    }

    // Measure time for MPI_Bcast
    start_time = MPI_Wtime();
    for (int i = 0; i < REPETITIONS; i++) {
        MPI_Bcast(data, DATA_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    }
    end_time = MPI_Wtime();
    if (rank == 0) {
        printf("MPI_Bcast time: %f seconds\n", (end_time - start_time) / REPETITIONS);
    }

    MPI_Finalize();
    return 0;
}

