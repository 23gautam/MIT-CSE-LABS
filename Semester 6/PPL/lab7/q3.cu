#include <stdio.h>

#define N 1024 // Size of the vectors

__global__ void vectorScalarAdd(float alpha, float *x, float *y) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < N) {
        y[index] = alpha * x[index] + y[index];
    }
}

int main() {
    float *x, *y;
    float alpha = 2.0f; // Scalar value
    float *d_x, *d_y;
    int size = N * sizeof(float);

    // Allocate host memory
    x = (float*)malloc(size);
    y = (float*)malloc(size);

    // Initialize host vectors
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
    }

    // Allocate device memory
    cudaMalloc((void**)&d_x, size);
    cudaMalloc((void**)&d_y, size);

    // Copy data from host to device
    cudaMemcpy(d_x, x, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y, size, cudaMemcpyHostToDevice);

    // Launch kernel
    vectorScalarAdd<<<1, N>>>(alpha, d_x, d_y);

    // Copy result from device to host
    cudaMemcpy(y, d_y, size, cudaMemcpyDeviceToHost);

    // Print the resultant vector
    printf("Resultant Vector (y):\n");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");

    // Free device memory
    cudaFree(d_x);
    cudaFree(d_y);

    // Free host memory
    free(x);
    free(y);

    return 0;
}
