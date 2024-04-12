#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDAcount(char *A, unsigned int *d_count)
{
    int i = threadIdx.x;
    if (A[i] == 'a')
        atomicAdd(d_count, 1);
}

int main()
{
    char A[N];
    char *d_A;
    unsigned int count = 0, *d_count, *result;
    printf("Enter a string: ");
    scanf("%s", A);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    cudaMalloc((void **)&d_A, (strlen(A) + 1) * sizeof(char));
    cudaMalloc((void **)&d_count, sizeof(unsigned int));

    cudaMemcpy(d_A, A, (strlen(A) + 1) * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(unsigned int), cudaMemcpyHostToDevice);

    CUDAcount<<<1, strlen(A) + 1>>>(d_A, d_count);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);

    result = (unsigned int *)malloc(sizeof(unsigned int));
    cudaMemcpy(result, d_count, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    printf("Total occurrences of 'a': %u\n", *result);

    printf("Time Taken = %f\n", elapsedTime);

    cudaFree(d_A);
    cudaFree(d_count);
    free(result);

    return 0;
}
