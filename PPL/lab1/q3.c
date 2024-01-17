#include "mpi.h"
#include <stdio.h>

int main(int argc,char* argv[])
{
	int rank,size;
	float a=2,b=3;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	switch(rank)
	{
		case 0:printf("rank:%d,a+b=%f\n",rank,a+b);
				break;

		case 1:printf("rank:%d,a-b=%f\n",rank,a-b);
				break;

		case 2: printf("rank:%d,a*b=%f\n",rank,a*b);
				break;

		case 3: printf("rank:%d,a/b=%f\n",rank,a/b);
				break;

	}
	MPI_Finalize();

}