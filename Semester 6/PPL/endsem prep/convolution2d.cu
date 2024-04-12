#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"
#include "cuda_runtime.h"

__global__ void convolution2d(int *mat, int *mask, int *out, int n, int m, int outSize)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < outSize && col < outSize)
    {
        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int input_row = row + i;
                int input_col = col + j;
                sum += mat[input_row * n + input_col] * mask[i * m + j];
            }
        }
        out[row * outSize + col] = sum;
    }
}

int main()
{
    int m, n;
    printf("Enter dim of matrix: ");
    scanf("%d", &n);

    printf("Enter dim of mask: ");
    scanf("%d", &m);

    int matrix[n][n], mask[m][m];

    int *d_mat, *d_mask, *d_out;

    printf("Enter matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Enter mask:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &mask[i][j]);
        }
    }

    int outSize = n - m + 1;
    int output[outSize][outSize];

    cudaMalloc((void **)&d_mat, n * n * sizeof(int));
    cudaMalloc((void **)&d_out, outSize * outSize * sizeof(int));
    cudaMalloc((void **)&d_mask, m * m * sizeof(int));

    cudaMemcpy(d_mat, matrix, n * n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask, mask, m * m * sizeof(int), cudaMemcpyHostToDevice);

    dim3 blockDim(16, 16);
    dim3 gridDim((outSize + blockDim.x - 1) / blockDim.x, (outSize + blockDim.y - 1) / blockDim.y);

    convolution2d<<<gridDim, blockDim>>>(d_mat, d_mask, d_out, n, m, outSize);

    cudaMemcpy(output, d_out, outSize * outSize * sizeof(int), cudaMemcpyDeviceToHost);

    printf("result:\n");
    for (int i = 0; i < outSize; i++)
    {
        for (int j = 0; j < outSize; j++)
        {
            printf("%d ", output[i][j]);
        }
        printf("\n");
    }

    cudaFree(d_mat);
    cudaFree(d_mask);
    cudaFree(d_out);

    return 0;
}
