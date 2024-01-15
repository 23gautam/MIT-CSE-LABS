#include "mpi.h"
#include <stdio.h>
#include <string.h>

void toggleCase(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		if(str[i]>='a' && str[i]<='z')
			str[i] = str[i]-32;
		else if(str[i]>='A' && str[i]<='Z')
			str[i] = str[i]+32;
		i++;
	}
}


int main(int argc,char *argv[])
{
	int rank,size,length;
	char word[256], word1[256];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a word to send\n");
		scanf("%s",word);
		length=strlen(word)+1;
		MPI_Ssend(&length,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Ssend(&word,length,MPI_CHAR,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"1.Sent %s in process 0\n",word);
		fflush(stdout);
		MPI_Recv(&word,length,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
		fprintf(stdout,"2.Received %s in process 0\n",word);
		fflush(stdout);
	}
	else
	{
		MPI_Recv(&length,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		MPI_Recv(&word1,length,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		fprintf(stdout,"3.Received %s in process 1\n",word1);
		fflush(stdout);
		
		toggleCase(word1);
		
		fprintf(stdout,"4.toggled %s in process 1\n",word1);
		fflush(stdout);
		MPI_Ssend(&word1,length,MPI_CHAR,0,2,MPI_COMM_WORLD);
		fprintf(stdout,"5.Sent %s in process 1\n",word1);
		fflush(stdout);


	}
	MPI_Finalize();
	return 0;
}