#include<mpi.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
    int rank,size,no,f,max;
    int a[3][3],a1[3][3],b[3],c[3],d[3];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        printf("Enter 3x3 matrix\n");
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                scanf("%d",&a[i][j]);
            }
        }
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                a1[i][j]=a[j][i];
            }
        }
        
       printf("Enter array\n");
       for(int i=0;i<3;i++)
        scanf("%d",&b[i]);
        
    }
    MPI_Scatter(b,1,MPI_INT,&no,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(a1,3,MPI_INT,c,3,MPI_INT,0,MPI_COMM_WORLD);

    max=c[0];
    for(int i=0;i<3;i++)
    {
        if(max<c[i])
            max=c[i];
    }
    f=no+max;

    MPI_Gather(&f,1,MPI_INT,d,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        for(int i=0;i<3;i++)
            printf("%d  ",d[i]);
        
        printf("\n");
    }


    MPI_Finalize();

}