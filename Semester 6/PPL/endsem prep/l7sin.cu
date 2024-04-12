#include <stdio.h>
#define N 10

__global__ void sinefun(float*radians, float *sine)
{
    int id=blockIdx.x*blockDim.x+threadIdx.x;

    sine[id]=sin(radians[id]);
}

int main()
{
    float *radians,*sine;
    float *d_radians,*d_sine;

    radians=(float*)malloc(N*sizeof(float));
    sine=(float*)malloc(N*sizeof(float));

    for(int i=0;i<N;i++)
    {
        radians[i]=float(i*5/2+0.3)*10;
    }

    cudaMalloc((void**)&d_radians,N*sizeof(float));
    cudaMalloc((void**)&d_sine,N*sizeof(float));

    cudaMemcpy(d_radians,radians,N*sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(d_sine,sine,N*sizeof(float),cudaMemcpyHostToDevice);

    sinefun<<<1,N>>>(d_radians,d_sine);

    cudaMemcpy(sine,d_sine,N*sizeof(float),cudaMemcpyDeviceToHost);

    printf("Resultant:\n");
    for(int i=0;i<N;i++)
    {
        printf("%f ",sine[i]);
    }

    cudaFree(d_sine);
    cudaFree(d_radians);

    free(radians);
    free(sine);
}