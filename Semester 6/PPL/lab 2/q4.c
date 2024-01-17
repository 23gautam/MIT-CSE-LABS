#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
	int rank,size,x;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a value in master process:\n");
		scanf("%d",&x);
		MPI_Ssend(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
		fprintf(stdout,"Sent %d in process 0\n",x);
		fflush(stdout);
		
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		fprintf(stdout,"Received %d in process %d\n",x,rank);
		x=x+1;
		fflush(stdout);
		MPI_Ssend(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
		fprintf(stdout,"Sent %d in process %d\n",x,rank);
		fflush(stdout);	
	}
	MPI_Finalize();
	return 0;
}