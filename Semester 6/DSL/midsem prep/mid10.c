#include <mpi.h>
#include <stdio.h>

int main(int argc,char*argv[])
{
    int rank,size,n,c,totalc=0;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a[3][3],b[3];
    
    if(rank==0)
    {
        printf("Enter 3x3 matrix:\n");
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                scanf("%d",&a[i][j]);
        }
        printf("Enter the element to be searched for: \n");
        scanf("%d",&n);
    }
    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(a,3,MPI_INT,b,3,MPI_INT,0,MPI_COMM_WORLD);
    c=0;
    for(int i=0;i<3;i++)
    {
        if(b[i]==n)
            c++;
    }
    MPI_Gather(&c,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Reduce(&c,&totalc,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        for(int i=0;i<3;i++)
        {
            printf("%d\t",b[i]);
        }
        printf("\ntotal: %d\n",totalc);
    }

    MPI_Finalize();
    return 0;
}