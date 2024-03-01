#include <mpi.h>
#include <string.h>
#include <stdio.h>

void togglecase(char * word,int len)
{
    for(int i=0;i<len;i++)
    {
        if(word[i]>='a' && word[i]<='z')
            word[i]=word[i]-32;

        else if(word[i]>='A' && word[i]<='Z')
            word[i]=word[i]+32;
        
    }
}

int main(int argc,char*argv[])
{
    int rank,size;
    char word[256],word2[256];
    int len;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    if(rank==0)
    {
        printf("Enter the word: \n");
        scanf("%s",word);
        len=strlen(word);
        MPI_Ssend(&len,1,MPI_INT,1,1,MPI_COMM_WORLD);
        MPI_Ssend(&word,len,MPI_CHAR,1,2,MPI_COMM_WORLD);
        fprintf(stdout,"Sent %s from process 0\n",word);
        fflush(stdout);


        MPI_Recv(&word2,len,MPI_CHAR,1,3,MPI_COMM_WORLD,&status);
        fprintf(stdout,"received %s in process 0\n",word2);
        fflush(stdout);
    }
    else{
        MPI_Recv(&len,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        MPI_Recv(&word2,len,MPI_CHAR,0,2,MPI_COMM_WORLD,&status);
        fprintf(stdout,"Received %s in process 1\n",word2);
        fflush(stdout);

        togglecase(word2,len);

        MPI_Ssend(&word2,len,MPI_CHAR,0,3,MPI_COMM_WORLD);
        fprintf(stdout,"sent %s from process 1\n",word2);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;

}