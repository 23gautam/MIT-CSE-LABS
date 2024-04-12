#include <stdio.h>
#include <stdlib.h>

#define N 10

__global__ void linalgebra(int *x,int *y,int alpha)
{
    int id=blockIdx.x * blockDim.x + threadIdx.x;

    y[id]=alpha*x[id]+y[id];
}

int main()
{
    int *x,*y;
    int alpha;
    int *d_x,*d_y;

    x=(int*)malloc(N*sizeof(int));
    y=(int*)malloc(N*sizeof(int));

    alpha=3;
    for(int i=0;i<N;i++)
    {
        x[i]=i*3;
        y[i]=pow(i,2);
    }

    cudaMalloc((void**)&d_x,N*sizeof(int));
    cudaMalloc((void**)&d_y,N*sizeof(int));
    
    cudaMemcpy(d_x,x,N*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_y,y,N*sizeof(int),cudaMemcpyHostToDevice);

    linalgebra<<<1,N>>>(d_x,d_y,alpha);

    cudaMemcpy(y,d_y,N*sizeof(int),cudaMemcpyDeviceToHost);

    printf("Resultant Matrix:\n");
    for(int i=0;i<N;i++)
    {
        printf("%d ",y[i]);
    }

    cudaFree(d_x);
    cudaFree(d_y);

    free(x);
    free(y);
}