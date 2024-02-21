#include <stdio.h>

#define N 32

__global__ void vectorAdd(int *a, int *b, int *c) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < N) {
        c[index] = a[index] + b[index];
    }
}

int main() {
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = N * sizeof(int);

    // Allocate host memory
    a = (int*)malloc(size);
    b = (int*)malloc(size);
    c = (int*)malloc(size);

    // Initialize host vectors
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i*3;
    }

    // Allocate device memory
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    // Copy data from host to device
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // Launch kernel
    vectorAdd<<<N,256>>>(d_a, d_b, d_c);

    // Copy result from device to host
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // Print the resultant vector
    printf("Resultant Vector (c):\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Free host memory
    free(a);
    free(b);
    free(c);

    return 0;
}
