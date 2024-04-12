#include <stdio.h>
#include <stdlib.h>
#define N 32

__global__ void countword(char *str,char *substr, int *count, int len, int sublen)
{
    int tid=threadIdx.x;
    if(tid<=len-sublen)
    {
        int match=1;
        for(int i=0;i<sublen;i++)
        {
            if(str[tid+i] != substr[i])
            {
                match=0;
                break;
            }
        }
        if(match==1)
        {
            atomicAdd(count,1);
        }
    }
}

int main()
{
    char str[N];
    char substr[N];
    int count;

    char *d_str,*d_substr;
    int *d_count;

    printf("Enter the word: ");
    scanf("%s",str);
    int str_len=strlen(str);

    while (getchar() != '\n');

    printf("Enter the word to search: ");
    scanf("%s",substr);
    int sub_len=strlen(substr);

    cudaMalloc((void**)&d_str,str_len*sizeof(char));
    cudaMalloc((void**)&d_substr,sub_len*sizeof(char));
    cudaMalloc((void**)&d_count,sizeof(int));

    cudaMemcpy(d_str,str,str_len*sizeof(char),cudaMemcpyHostToDevice);
    cudaMemcpy(d_substr,substr,sub_len*sizeof(char),cudaMemcpyHostToDevice);

    countword<<<1,str_len>>>(d_str,d_substr,d_count,str_len,sub_len);

    cudaMemcpy(&count,d_count,sizeof(int),cudaMemcpyDeviceToHost);

    printf("count: %d",count);

    cudaFree(d_str);
    cudaFree(d_substr);
    cudaFree(d_count);
}