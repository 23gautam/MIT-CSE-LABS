#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 3

__global__ void modify(int *matrix)
{
    int tid=blockIdx.x*blockDim.x+threadIdx.x;
    int stride=blockDim.x*gridDim.x;

    for(int i=tid;i<M*N;i+=stride)
    {
        int row=i/N;
        

        if(row==1)
        {
            matrix[i]=pow(matrix[i],2);
        }
        else if(row==2)
        {
            matrix[i]=pow(matrix[i],3);
        }
    }
}


int main()
{
    int matrix[M][N];
    int *d_matrix;



    printf("Enter matrix:\n");
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }

    cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);

    cudaMalloc((void**)&d_matrix,M*N*sizeof(int));

    cudaMemcpy(d_matrix,matrix,M*N*sizeof(int),cudaMemcpyHostToDevice);

    dim3 blockDim(256);
    dim3 gridDim((M*N+256-1)/256);

    modify<<<gridDim,blockDim>>>(d_matrix);

    cudaMemcpy(matrix,d_matrix,M*N*sizeof(int),cudaMemcpyDeviceToHost);

    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime,start,stop);

    printf("result:\n");
     for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    cudaFree(d_matrix);

}