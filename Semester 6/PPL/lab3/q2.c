#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank,size,N,M,A[100],C[100],sum=0,temp=0;
	float B[100];
	float avg=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		N=size;
		fprintf(stdout,"Enter value M:\n");
		fflush(stdout);
		scanf("%d",&M);
		fprintf(stdout,"Enter %d values:\n",N*M);
		fflush(stdout);
		for(int i=0;i<N*M;i++)
		{		
				scanf("%d",&A[i]);
		}

	}
	
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,M,MPI_INT,C,M,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stdout,"I have received in process %d\n",rank);
	fflush(stdout);
	sum=0;
	avg=0;
	for(int i=0;i<M;i++)
	{
		sum+=C[i];
	}
	avg=sum/M;
	fprintf(stdout,"P%d Avg:%f\n",rank,avg);
	fflush(stdout);
	MPI_Gather(&avg,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		fprintf(stdout,"The result gathered in the root\n");
		fflush(stdout);
		sum=0;
		avg=0;
		for(int i=0;i<N;i++)
		{
			sum+=B[i];
			avg=sum/N;
		}
		fprintf(stdout,"Total Avg: %f\n",avg);
			fflush(stdout);
	}

}