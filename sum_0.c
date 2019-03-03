#include <mpi.h>
#include <stdio.h>
                                 //// START ON 4 
#define mymessage 619 

int main (int argc, char **argv){

        int i, j, size, rank;
	double sum_add, sum_fin; 
	sum_add = 0;
	sum_fin = 0;       

	MPI_Status status;

	MPI_Init(&argc, &argv);
        
	MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
	if (rank != 0){
		if (rank == 1){
			for(i = rank; i <= 19; i++){
				sum_add = sum_add + 1/(double)i;
				printf("result %f from rank %i\n", sum_add, rank);
				///MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD); 
			}
			MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
			//printf("SUM FROM 1 TO 19 = %f\n", sum_add);
		}
		if (rank == 2){
			for(i = rank*10; i <= 29; i++){
				sum_add = sum_add + 1/(double)i;
                        	printf("result %f from rank %i\n", sum_add, rank);
				///MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
			}
			MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
			//printf("SUM FROM 2 TO 29 = %f\n", sum_add);
		}
		if (rank == 3){
                        for(i = rank*10; i <= 39; i++){
                                sum_add = sum_add + 1/(double)i;
                                printf("result %f from rank %i\n", sum_add, rank);
				///MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
                        }
			MPI_Send(&sum_add, 1, MPI_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
			//printf("SUM FROM 30 TO 39 = %f\n", sum_add);
                }
	}
	
	if (rank == 0){
		sleep(1);
		double sum_buf[10];
		for(j = 1; j <= 3; j++){
			MPI_Recv(sum_buf+j, 1, MPI_DOUBLE, j, mymessage, MPI_COMM_WORLD, &status);
			///printf("[%i] = %f\n", j, sum_buf[j]);
			sum_fin = sum_fin + sum_buf[j];
		}	
		printf("SUM FROM 1 TO 19 = %f\n", sum_buf[1]);
		printf("SUM FROM 20 TO 29 = %f\n", sum_buf[2]);
		printf("SUM FROM 30 TO 39 = %f\n", sum_buf[3]);
		printf("FINAL SUMM (1/n) WHERE n = 1...39 = %f\n", sum_fin);
	}

	//printf("Hello! I’m a process #%d of %d processes\n", rank, size);
        
	MPI_Finalize();
        return 0;
}

