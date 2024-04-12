#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"


__global__ void transpose(int *a, int *t)
{
    int n=threadIdx.x;
    int m=blockIdx.x;
    int size=blockDim.x-1;
    int size1=gridDim.x;

    t[n*size1+m]=a[m*size+n];
}


int main()
{
    int *a,*t,m,n,i,j;
    int *d_a,*d_t;

    printf("Enter the value of m: ");
    scanf("%d",&m);

    printf("Enter the value of n: ");
    scanf("%d",&n);

    int size=m*n*sizeof(int);

    a=(int*)malloc(m*n*sizeof(int));
    t=(int*)malloc(m*n*sizeof(int));

    printf("Enter the matrix:\n");
    for(int i=0;i<m*n;i++)
    {
        scanf("%d",&a[i]);
    }

    cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);

    cudaMalloc((void**)&d_a,size);
    cudaMalloc((void**)&d_t,size);

    cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);

    transpose<<<m,n>>(d_a,d_t);

    cudaMemcpy(t,d_t,size,cudaMemcpyDeviceToHost);

    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime,start,stop);

    printf("result:\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",t[i*m+j]);
        }
        printf("\n");
    }
    cudaFree(d_a);
    cudaFree(d_t);

}