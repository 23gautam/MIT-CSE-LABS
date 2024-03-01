#include <mpi.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
    int rank,size,no;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    if(rank==0)
    {
        for(int i=1;i<size-1;i++)
        {
            MPI_Send(&i,1,MPI_INT,i,0,MPI_COMM_WORLD);
            fprintf(stdout,"Sent %d from process 0\n",i);
            fflush(stdout);
        }
    }
    else
    {
        MPI_Recv(&no,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        fprintf(stdout,"Received %d in process %d\n",no,rank);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}