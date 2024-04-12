#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 32

__global__ void vecAdd(int* a,int* b,int* c)
{
    int index=blockIdx.x * blockDim.x + threadIdx.x;
    if(index<N)
    {
        c[index]=a[index]+b[index];
    }
    
}


int main()
{
    int *a, *b, *c;
    int *d_a,*d_b,*d_c;
    int size = N*sizeof(int);

    a=(int*)malloc(size);
    b=(int*)malloc(size);
    c=(int*)malloc(size);

    for(int i=0;i<N;i++)
    {
        a[i]=i;
        b[i]=pow(i,2);
    }

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b,size);
    cudaMalloc((void**)&d_c,size);

    cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

    vecAdd<<<1,N>>>(d_a,d_b,d_c);

    cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);

    printf("Resultant vector(c):\n");
    for(int i=0;i<N;i++)
    {
        printf("%d ",c[i]);
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(a);
    free(b);
    free(c);

    return 0;
}