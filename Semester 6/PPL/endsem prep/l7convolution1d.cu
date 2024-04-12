#include<stdio.h>
#include<stdlib.h>
#define N 10
#define M 3

__global__ void convolution1D(int *input, int *mask, int *out)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int half_mask=M/2;

    if(id<N)
    {
        int val=0;
        for(int i=0;i<M;i++)
        {
            int idx=id+i-half_mask;
            if(idx>=0 && idx<N)
            {
                val+=input[idx]*mask[i];
            }
        }
        out[id]=val;
    }
}
int main()
{
    int *input,*mask,*out;
    int *d_input,*d_mask,*d_out;

    input=(int*)malloc(N*sizeof(int));
    mask=(int*)malloc(M*sizeof(int));
    out=(int*)malloc(N*sizeof(int));

    for(int i=0;i<N;i++)
    {
        input[i]=i+1;
        if(i<M)
            mask[i]=1;
    }


    cudaMalloc((void**)&d_input,N*sizeof(int));
    cudaMalloc((void**)&d_mask,M*sizeof(int));
    cudaMalloc((void**)&d_out,N*sizeof(int));

    cudaMemcpy(d_input,input,N*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_mask,mask,M*sizeof(int),cudaMemcpyHostToDevice);

    convolution1D<<<1,N>>>(d_input,d_mask,d_out);

    cudaMemcpy(out,d_out,N*sizeof(int),cudaMemcpyDeviceToHost);

    printf("Resultant matrix:\n");
    for(int i=0;i<N;i++)
    {
        printf("%d ",out[i]);
    }
        

    cudaFree(d_input);
    cudaFree(d_mask);
    cudaFree(out);

    free(input);
    free(mask);
    free(out);

    return 0;

}