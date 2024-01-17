#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc,char* argv[])
{
	int rank,size;
	float x=2;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("My rank is %d in total %d processes,result:%f\n",rank,size,pow(x,rank));
	MPI_Finalize();
	return 0;
}