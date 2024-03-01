#include <mpi.h>
#include <stdio.h>

int main(int argc,char * argv[])
{
    int rank,size,x,size1=256;
    int buf[256];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;

    int arr[size];

    if(rank==0)
    {
        MPI_Buffer_attach(buf,size1);
        for(int i=0;i<size-1;i++)
        {
            printf("Enter the value in master process: \n");
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
        fflush(stdout);
        if(rank%2==0)
        {
            fprintf(stdout,"rank %d: %d\n",rank,x*x);
            fflush(stdout);
        }
        else{
            fprintf(stdout,"rank %d: %d\n",rank,x*x*x);
            fflush(stdout);
        }
    }
    MPI_Finalize();
    return 0;
}