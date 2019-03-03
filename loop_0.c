#include <mpi.h>
#include <stdio.h>
                                 //// START ON 4 
#define mymessage 619 

int main (int argc, char **argv){

        int DATA, j, size, rank;       

	MPI_Status status;

	MPI_Init(&argc, &argv);
        
	MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	if (rank != 0){
		if (rank == 1){
				//sleep(5);
				int temp_rec_buf;
				MPI_Recv(&temp_rec_buf, 1, MPI_INT, 0, mymessage, MPI_COMM_WORLD, &status);
				printf("I AM 1! RECV DATA FROM 0 = %i\n", temp_rec_buf);
				printf("I AM 1! SEND DATA FROM 1 TO 2\n");
				//sleep(1);
				MPI_Send(&temp_rec_buf, 1, MPI_INT, 2, mymessage, MPI_COMM_WORLD);
			
		}
		if (rank == 2){
			//sleep(6);
			int temp_rec_buf;
			MPI_Recv(&temp_rec_buf, 1, MPI_INT, 1, mymessage, MPI_COMM_WORLD, &status);
			printf("I AM 2! RECV DATA FROM 1 = %i\n", temp_rec_buf);
			printf("I AM 2! SEND DATA FROM 2 TO 0\n");
			//sleep(1);
                        MPI_Send(&temp_rec_buf, 1, MPI_INT, 0, mymessage, MPI_COMM_WORLD);
		}
	}
	
	if (rank == 0){
		int temp_rec_buf;
		scanf("%i",&DATA);
		printf("I AM 0! SEND DATA FROM 0 TO 1\n");
		MPI_Send(&DATA, 1, MPI_INT, 1, mymessage, MPI_COMM_WORLD);
		sleep(1);
		MPI_Recv(&temp_rec_buf, 1, MPI_INT, 2, mymessage, MPI_COMM_WORLD, &status);
		printf("I AM 0! RECV DATA FROM 2 = %i\n", temp_rec_buf);
	}
        
	MPI_Finalize();
        return 0;
}

