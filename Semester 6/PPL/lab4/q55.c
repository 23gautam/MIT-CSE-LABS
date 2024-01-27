#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int size, rank, countsum;
	int A[4][4];
	int colsum[4][4];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank == 0)
	{
		printf("Enter the 4x4 matrix:\n");
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				scanf("%d", &A[i][j]);
			}
		}
	}

	MPI_Bcast(A, 16, MPI_INT, 0, MPI_COMM_WORLD);

	int B[4];
	MPI_Scatter(A, 4, MPI_INT, B, 4, MPI_INT, 0, MPI_COMM_WORLD);

	for(int i = 0; i < 4; i++)
	{
		MPI_Scan(&B[i], &colsum[i], 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	}

	MPI_Gather(colsum, 16, MPI_INT, A, 16, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0)
	{
		printf("\nOutput matrix:\n");
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
}
