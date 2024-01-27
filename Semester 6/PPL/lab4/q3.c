#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int size,rank,key,count=0,countsum;
	int A[3][3];


	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		printf("Enter the 3x3 matrix:\n");
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				scanf("%d",&A[i][j]);
			}
		}
		printf("Enter the element to be searched for\n");
		scanf("%d",&key);

	}
	int B[3];
	MPI_Bcast(&key,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,3,MPI_INT,B,3,MPI_INT,0,MPI_COMM_WORLD);

	for(int i=0;i<3;i++)
		printf("%d ",B[i]);

	printf("rank: %d\n", rank);

	count=0;
	for(int i=0;i<3;i++)
	{
		if(B[i]==key)
			count++;
	}
	MPI_Reduce(&count,&countsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank==0)
		printf("Total number of occurences is: %d\n",countsum);
	MPI_Finalize();
}