#include "mpi.h"
#include <stdio.h>


int main(int argc,char* argv[])
{
	int rank,size,n,n1,temp;
	int arr[9]={18,523,301,1234,2,14,108,150,1928};

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	for(int i=0;i<10;i++)
	{
		if(rank==i)
		{
			n=arr[i];
			temp=0,n1=0;
			while(n>0)
			{
				temp=n%10;
				n1=n1*10+temp;
				n=n/10;
			}
			arr[i]=n1;
		}
		
	}
	MPI_Finalize();
	for(int i=0;i<9;i++)
	{
		if(rank==i)
			printf("%d, ",arr[i]);
	}	
	
	
}