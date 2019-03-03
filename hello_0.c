#include <mpi.h>
#include <stdio.h>

int main (int argc, char **argv){

	int i, size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Hello! I’m a process #%d of %d processes\n", rank, size);
	MPI_Finalize();
	return 0;
}

/// mpirun -np 5 hello.bin

