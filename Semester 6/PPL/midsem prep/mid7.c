#include <mpi.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
    int rank,size,fact=1,no,M,N;
    float avg=0,sum=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    int a[M*size],b[M];
    float c[size];
    if(rank==0)
    {
        N=size;
        printf("Enter value M:\n");
        scanf("%d",&M);
        printf("Enter %d elements\n",M*N);
        for(int i=0;i<M*N;i++)
        {
            scanf("%d",&a[i]);
        }
    }
    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(a,M,MPI_INT,b,M,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<M;i++)
        printf("%d",b[i]);

    printf("\n");
    sum=0;
    avg=0;
    for(int i=0;i<M;i++)
    {
        sum=sum+b[i];
    }
    printf("%fsum\n",sum);
    printf("%dM\n",M);
    avg=sum/M;
    printf("%favg\n",avg);
    MPI_Gather(&avg,1,MPI_FLOAT,c,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    if(rank==0)
    {
        fprintf(stdout,"Gathered:\n");
        fflush(stdout);
        for(int i=0;i<N;i++)
        {
            fprintf(stdout,"%f\t",c[i]);
             fflush(stdout);
        }
       
    }
    MPI_Finalize();
    return 0;
}