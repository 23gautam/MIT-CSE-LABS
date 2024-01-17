#include "mpi.h"
#include <stdio.h>

int main(int argc,char* argv[])
{
	int rank,size;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank%2==0)
		printf("My rank is %d in total %d processes,HELLO\n",rank,size);
	else
		printf("My rank is %d in total %d processes,WORLD\n",rank,size);

	MPI_Finalize();
}