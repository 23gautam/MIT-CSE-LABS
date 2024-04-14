#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__device__ int position(char *str,int *col,int id)
{
    int pos=0;
    for(int i=0;i<id;i++)
    {
        if(str[i]=='+')
            pos+=col[i]+1;
        
        else
            pos+=col[i]+2;
    }
    return pos;
}


__global__ void sparse(char* str, char* res, int *row, int *col, int len)
{
    int id=threadIdx.x;
    if(id<len)
    {
        int pos=position(str,col,id);
        int nextpos=position(str,col,id+1);

        for(int i=pos;i<nextpos;i++)
        {
          res[i]=str[id];
        }

        
    }
}


int main()
{
    char str[100],res[100];

    printf("Enter string: ");
    scanf("%s",str);
    int len=strlen(str);

    int row[len],col[len];

    printf("Enter row mat: ");
    for(int i=0;i<len;i++)
    {
        scanf("%d",&row[i]);
    }
    printf("Enter col mat: ");
    for(int i=0;i<len;i++)
    {
        scanf("%d",&col[i]);
    }

    int *d_row,*d_col;
    char *d_str,*d_res;

    cudaMalloc((void**)&d_str,len*sizeof(char));
    cudaMalloc((void**)&d_res,len*len*sizeof(char));
    cudaMalloc((void**)&d_row,len*sizeof(int));
    cudaMalloc((void**)&d_col,len*sizeof(int));

    cudaMemcpy(d_str,str,len*sizeof(char),cudaMemcpyHostToDevice);
    cudaMemcpy(d_res,res,len*len*sizeof(char),cudaMemcpyHostToDevice);
    cudaMemcpy(d_col,col,len*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_row,row,len*sizeof(int),cudaMemcpyHostToDevice);

    sparse<<<1,16>>>(d_str,d_res,d_row,d_col,len);

    cudaMemcpy(res,d_res,len*len*sizeof(char),cudaMemcpyDeviceToHost);

    printf("result:%s",res);

    cudaFree(d_str);
    cudaFree(d_res);
    cudaFree(d_row);
    cudaFree(d_col);

}