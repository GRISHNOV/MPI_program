#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
//// START ON 5. 16 decimal places
#define mymessage 619
typedef long double LONG_TYPE;

LONG_TYPE fact_range(LONG_TYPE data_init, LONG_TYPE data_fin)
{
    LONG_TYPE result = 1;
    if (data_init == data_fin)
    {
        for (LONG_TYPE i = 1; i <= data_init; i++)
        {
            result = result * i;
        }
        return result;
    }

    for (LONG_TYPE i = data_init; i <= data_fin; i++)
    {
        result = result * i;
    }
    return result;
}

int main(int argc, char **argv)
{

    int i, j, size, rank;
    LONG_TYPE /*sum_add = 0,*/ sum_fin = 1;

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0)
    {
        if (rank == 1)
        {

            LONG_TYPE sum_res = 0;
            for (i = 1; i <= 250; i++)
            {
                //fact_array[i] = fact_range(i, i);
                sum_res = sum_res + 1.0 / fact_range(i, i);
            }

            MPI_Send(&sum_res, 1, MPI_LONG_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
        }
        if (rank == 2)
        {
            LONG_TYPE sum_res = 0;
            for (i = 250; i <= 500; i++)
            {
                //fact_array[i] = fact_range(i, i);
                sum_res = sum_res + 1.0 / fact_range(i, i);
            }
            MPI_Send(&sum_res, 1, MPI_LONG_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
        }
        if (rank == 3)
        {
            LONG_TYPE sum_res = 0;
            for (i = 500; i <= 750; i++)
            {
                //fact_array[i] = fact_range(i, i);
                sum_res = sum_res + 1.0 / fact_range(i, i);
            }
            MPI_Send(&sum_res, 1, MPI_LONG_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
        }
        if (rank == 4)
        {
            LONG_TYPE sum_res = 0;
            for (i = 750; i <= 1000; i++)
            {
                //fact_array[i] = fact_range(i, i);
                sum_res = sum_res + 1.0 / fact_range(i, i);
            }
            MPI_Send(&sum_res, 1, MPI_LONG_DOUBLE, 0, mymessage, MPI_COMM_WORLD);
        }
    }

    if (rank == 0)
    {
        //sleep(1);
        LONG_TYPE sum_buf[4];
        for (j = 1; j <= 4; j++)
        {
            MPI_Recv(sum_buf + j, 1, MPI_LONG_DOUBLE, j, mymessage, MPI_COMM_WORLD, &status);
        }

        for (j = 1; j <= 4; j++)
        {
            printf("Sum from process = %i => %.4000Lf\n", j, sum_buf[j]);
            sum_fin = sum_fin + sum_buf[j];
        }
        printf("EXP =  %.4000Lf\n", sum_fin);
    }

    MPI_Finalize();
    return 0;
}