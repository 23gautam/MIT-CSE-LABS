#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
	int rank,size,x;
	int buf[256];
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int arr[size];
	MPI_Status status;
	if(rank==0)
	{
		MPI_Buffer_attach(buf,256);
		for(int i=0;i<size-1;i++)
		{
			printf("Enter a value in master process:\n");
			scanf("%d",&arr[i]);
			MPI_Bsend(&arr[i],1,MPI_INT,i+1,0,MPI_COMM_WORLD);
			fprintf(stdout,"Sent %d in process 0\n",arr[i]);
			fflush(stdout);
		}
		
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		fprintf(stdout,"Received %d in process %d\n",x,rank);
		if(rank%2==0)
		{
			fprintf(stdout,"Square= %d in process %d\n",x*x,rank);
			fflush(stdout);
		}
		else
		{
			fprintf(stdout,"Cube= %d in process %d\n",x*x*x,rank);
			fflush(stdout);
		}
	}
	MPI_Finalize();
	return 0;
}