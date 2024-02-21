#include <stdio.h>

#define N 10 // Number of input elements
#define M 3  // Size of the mask array

__global__ void convolution(int *input, int *mask, int *output) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int half_mask = M / 2;

    if (tid < N) {
        int val = 0;
        for (int i = 0; i < M; i++) {
            int idx = tid + i - half_mask;
            if (idx >= 0 && idx < N) {
                val += input[idx] * mask[i];
            }
        }
        output[tid] = val;
    }
}

int main() {
    int input[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int mask[M] = {1, 1, 1}; // Example mask array
    int output[N];

    int *d_input, *d_mask, *d_output;

    cudaMalloc((void**)&d_input, N * sizeof(int));
    cudaMalloc((void**)&d_mask, M * sizeof(int));
    cudaMalloc((void**)&d_output, N * sizeof(int));

    cudaMemcpy(d_input, input, N * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, mask, M * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int gridSize = (N + blockSize - 1) / blockSize;

    convolution<<<gridSize, blockSize>>>(d_input, d_mask, d_output);

    cudaMemcpy(output, d_output, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Resultant Array after Convolution:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    cudaFree(d_input);
    cudaFree(d_mask);
    cudaFree(d_output);

    return 0;
}
