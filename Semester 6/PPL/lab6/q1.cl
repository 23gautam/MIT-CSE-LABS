__kernel void strprint(__global const char* inputString,__global char* outputString,const int N,const int len) 
{
    int globalID = get_global_id(0);

    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < len; ++j) 
        {
            outputString[globalID * N * len + i * len + j] = inputString[j];
        }
    }
}
