#include <mpi.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
    int rank,size,fact=1,no;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int a[size],b[size];
    if(rank==0)
    {
        printf("Enter %d elements\n",size);
        for(int i=0;i<size;i++)
        {
            scanf("%d",&a[i]);
        }
    }
    MPI_Scatter(a,1,MPI_INT,&no,1,MPI_INT,0,MPI_COMM_WORLD);
    fprintf(stdout,"Received %d in process %d",no,rank);
    fflush(stdout);

    while(no>0)
    {
        fact=fact*no;
        no=no-1;
    }
    MPI_Gather(&fact,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        fprintf(stdout,"Gathered:\n");
        fflush(stdout);
        for(int i=0;i<size;i++)
        {
            fprintf(stdout,"%d\t",b[i]);
        }
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}