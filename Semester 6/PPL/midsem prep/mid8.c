#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
    int rank,size,len,nv,tot=0,M,i,v;
    char str[256],substr[10];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int b[size];
    int N=size;

    if(rank==0)
    {
        printf("Enter string: \n");
        scanf("%s",str);
        len=strlen(str);
        M=len/size;
        printf("%dM\n",M);
        printf("%sstr\n",str);
    }
    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(str,M,MPI_CHAR,substr,M,MPI_CHAR,0,MPI_COMM_WORLD);
    printf("received: %s\n",substr);
    nv=0;
    i=0;
    while(substr[i]!='\0')
    {
        if(substr[i]=='a' || substr[i]=='e' || substr[i]=='i' || substr[i]=='o' || substr[i]=='u')
            nv++;
        
        i++;
    }
    v=len-nv;
    MPI_Gather(&nv,1,MPI_INT,b,1,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        for(int i=0;i<size;i++)
        {
            fprintf(stdout,"%d\t",b[i]);
            tot+=b[i];
        }
        fflush(stdout);
        fprintf(stdout,"total: %d\n",tot);
    }
    MPI_Finalize();
    return 0;
}