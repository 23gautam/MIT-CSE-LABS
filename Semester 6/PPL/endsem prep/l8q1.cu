#include<stdio.h>
#include<string.h>
#include<stdlib.h>

__global__ void print3(char *str,char *out,int ip_len,int n)
{
    int id=threadIdx.x;

    int op_len=n*ip_len;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<ip_len;j++)
        {
             out[id*op_len+i*ip_len+j]=str[j];
        }
    }
}
   

int main()
{
    char str[]="Hello";
    int N=3;
    int len=strlen(str);

    char *out;
    char *d_str,*d_out;
    out=(char*)malloc(N*strlen(str)*sizeof(char));

    cudaMalloc((void**)&d_str,strlen(str)*sizeof(char));
    cudaMalloc((void**)&d_out,N*strlen(str)*sizeof(char));

    cudaMemcpy(d_str,str,strlen(str)*sizeof(char),cudaMemcpyHostToDevice);
    
    print3<<<1,N>>>(d_str,d_out,len,N);

   cudaMemcpy(out,d_out,N*strlen(str)*sizeof(char),cudaMemcpyDeviceToHost);

    printf("Resultant:%s",out);

    cudaFree(d_str);
    cudaFree(d_out);

    free(out);

}