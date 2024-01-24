#include "mpi.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	int rank,size,N,M,A[10][10],C[10],sum=0,temp=0;
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
		for(int i=0;i<N;i++)
		{		
				for(int j=0;j<M;j++)
					scanf("%d",&A[i][j]);
		}

	}
	for(int i=0;i<N;i++)
	{		
			for(int j=0;j<M;j++)
			{
				temp=A[i][j];
				A[i][j]=A[j][i];
				A[j][i]=temp;
			}
	}
	for(int i=0;i<M;i++)
		{		
				for(int j=0;j<N;j++)
					printf("%d ",A[i][j]);
		}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	for(int i=0;i<M;i++) 
	{
		MPI_Scatter(A[i],N,MPI_INT,C,N,MPI_INT,0,MPI_COMM_WORLD);
	}

	// fprintf(stdout,"I have received in process %d\n",rank);
	// fflush(stdout);
	sum=0;
	avg=0;
	for(int i=0;i<N;i++)
	{
		sum+=C[i];
	}
	avg=sum/N;
	fprintf(stdout,"P%d Avg:%f\n",rank,avg);
	fflush(stdout);
	MPI_Gather(&avg,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		fprintf(stdout,"The result gathered in the root\n");
		fflush(stdout);
		sum=0;
		avg=0;
		for(int i=0;i<M;i++)
		{
			sum+=B[i];
			avg=sum/M;
		}
		fprintf(stdout,"Total Avg: %f\n",avg);
			fflush(stdout);
	}

}