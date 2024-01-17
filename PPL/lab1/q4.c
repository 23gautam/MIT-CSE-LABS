#include "mpi.h"
#include <stdio.h>

int main(int argc,char* argv[])
{
	int size,rank;

	char string[10]="HeLLO";

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	for(int i=0;i<5;i++)
	{
		if(rank==i)
		{
			if(string[rank]>65 && string[rank]<=90)
				string[rank]+=32;
			else 
				string[rank]-=32;

			printf("Rank:%d, string: %s\n",rank,string);
		}
	}
	MPI_Finalize();
}