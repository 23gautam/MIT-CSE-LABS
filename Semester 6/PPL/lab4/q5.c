#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int size,rank,key,count=0,countsum;
	int A[4][4];


	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		printf("Enter the 4x4 matrix:\n");
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				scanf("%d",&A[i][j]);
			}
		}

	}
	int B[4];
	MPI_Scatter(A,4,MPI_INT,B,4,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<4;i++)
		printf("%d ",B[i]);

	printf("rank: %d\n", rank);

	// count=0;
	// for(int i=0;i<3;i++)
	// {
	// 	if(B[i]==key)
	// 		count++;
	// }
	// MPI_Reduce(&count,&countsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	// if(rank==0)
	// 	printf("Total number of occurences is: %d\n",countsum);
	MPI_Finalize();
}