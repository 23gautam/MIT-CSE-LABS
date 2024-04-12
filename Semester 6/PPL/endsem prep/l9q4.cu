#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

__global__ void comp1(int *a,int *res, int m,int n)
{
    int row=blockIdx.y*blockDim.y+threadIdx.y;
    int col=blockIdx.x*blockDim.x+threadIdx.x;
    int no,rem,newno;

    if(row>=0 && row<m && col>=0 && col<n)
    {
        if(row==0 || row==m-1 || col==0 || col==n-1)
        {
            res[row*n+col]= a[row*n+col];
        }
        else
        {
            no=a[row*n+col]+1;
            rem=0;
            newno=0;
            while(no>0)
            {
              rem=no%2;
              newno=newno*10+rem;
              no=no/2;
            }
            res[row*n+col]=newno;
        }
    }
}

int main()
{
    int m,n;
    printf("Enter the dim: ");
    scanf("%d%d",&m,&n);

    int a[m][n];
    int res[m][n];
    int *d_a,*d_res;

    printf("enter the matrix:\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);


    cudaMalloc((void**)&d_a,m*n*sizeof(int));
    cudaMalloc((void**)&d_res,m*n*sizeof(int));

    cudaMemcpy(d_a,a,m*n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 blockDim(32,32);
    dim3 gridDim((n+blockDim.x-1)/blockDim.x,(m+blockDim.y-1)/blockDim.y);

    comp1<<<gridDim,blockDim>>>(d_a,d_res,m,n);

    cudaMemcpy(res,d_res,m*n*sizeof(int),cudaMemcpyDeviceToHost);

    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime,start,stop);

    printf("Result:\n");
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    printf("Time Taken:%f",elapsedTime);

    cudaFree(d_a);
    cudaFree(d_res);

}