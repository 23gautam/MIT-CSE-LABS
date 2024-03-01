#include <mpi.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
    int rank,size;

    int c;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int a[size],b[size];

    if(rank==0)
    {
        printf("enter %d values: \n",size);
        for(int i=0;i<size;i++)
            scanf("%d",&a[i]);
    }
    MPI_Scatter(a,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
    fprintf(stdout,"I have received %d in %d process\n",c,rank);
    fflush(stdout);

    c=c*c;
    MPI_Gather(&c,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        fprintf(stdout,"Result gathered in root: \n");
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