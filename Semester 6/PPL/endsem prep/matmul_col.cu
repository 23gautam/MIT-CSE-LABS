#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

__global__ void matmul_col(int *a,int *b,int *c,int ha,int wa)
{
    int cidB=threadIdx.x;
    int wb=blockDim.x;
    int sum;
    for(int ridA=0;ridA<ha;ridA++)
    {
        sum=0;
        for(int k=0;k<wa;k++)
        {
            sum+=a[ridA*wa+k]*b[k*wb+cidB];
        }
        c[ridA*wb+cidB]=sum;
    }
}


int main()
{
    int ha,hb,wa,wb;
    printf("Enter the dim of 'a': ");
    scanf("%d%d",&ha,&wa);

    printf("Enter the dim of 'b': ");
    scanf("%d%d",&hb,&wb);

    int a[ha][wa],b[hb][wb];
    int res[ha][wb];

    printf("Enter 'a': ");
    for(int i=0;i<ha;i++)
    {
        for(int j=0;j<wa;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }

    printf("Enter 'b': ");
    for(int i=0;i<hb;i++)
    {
        for(int j=0;j<wb;j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    
    int *d_a,*d_b,*d_res;

    cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start,0);

    cudaMalloc((void**)&d_a,ha*wa*sizeof(int));
    cudaMalloc((void**)&d_b,hb*wb*sizeof(int));
    cudaMalloc((void**)&d_res,ha*wb*sizeof(int));

    cudaMemcpy(d_a,a,ha*wa*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,hb*wb*sizeof(int),cudaMemcpyHostToDevice);

    matmul_col<<<1,wb>>>(d_a,d_b,d_res,ha,wa);

    cudaMemcpy(res,d_res,ha*wb*sizeof(int),cudaMemcpyDeviceToHost);

    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime,start,stop);

    printf("Result:\n");
    for(int i=0;i<ha;i++)
    {
        for(int j=0;j<wb;j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
    printf("Time taken:%f",elapsedTime);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_res);

}