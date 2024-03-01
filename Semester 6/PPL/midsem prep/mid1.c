#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
    int rank,size,no;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;

    if(rank==0)
    {
        printf("Enter a number: ");
        scanf("%d",&no);
        MPI_Ssend(&no,1,MPI_INT,1,1,MPI_COMM_WORLD);
        fprintf(stdout,"I have sent %d from process 0\n",no);
        fflush(stdout);
    }
    else
    {
        MPI_Recv(&no,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        fprintf(stdout,"I have received %d in process 1\n",no);
        fflush(stdout);
    }
    MPI_Finalize();
}