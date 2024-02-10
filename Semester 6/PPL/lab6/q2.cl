__kernel void selectionSort(__global int *A, __global int *C) {

    int globalID = get_global_id(0);


    int minIndex = globalID;


    for (int i = globalID + 1; i < get_global_size(0); i++) {
        if (A[i] < A[minIndex]) {
            minIndex = i;
        }
    }

    int temp = A[globalID];
    A[globalID] = A[minIndex];
    A[minIndex] = temp;

    C[globalID] = A[globalID];
}
