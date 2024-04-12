#include<stdio.h>
#include<string.h>

__global__ void counts(char *str, char *word, int *count, int strlen, int wordlen) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    while (tid < strlen) {
        int i = 0;
        while (i < wordlen && str[tid + i] == word[i]) i++;
        if (i == wordlen) {
            atomicAdd(count, 1);
            tid += wordlen;
        }
        else {
            tid++;
        }
    }
}

int main() {
    const int N = 1024; // Maximum string length
    char input[N];
    char word[N];
    int *count = 0, *d_count;
    int result;

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);

    printf("Enter the word to search for: ");
    scanf("%s", word);

    int strlen = strlen(input);
    int wordlen = strlen(word);

    cudaMalloc((void**)&d_count, sizeof(int));
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    counts<<<1, strlen>>>(input, word, d_count, strlen, wordlen);

    cudaMemcpy(&result, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Total occurrences of '%s' = %d\n", word, result);

    cudaFree(d_count);

    return 0;
}