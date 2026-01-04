#include <stdio.h>
#define MAX_SIZE 100

void heapifyDown(int arr[], int n, int index);
void buildHeap(int arr[], int n);
void heapSort(int arr[], int n);
void insert(int arr[], int* size, int value);
int deleteRoot(int arr[], int* size);

int main() {
    int arr[MAX_SIZE] = {7, 3, 10, 1, 5, 2, 8};
    int heapSize = 7;

    printf("Original array: ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    buildHeap(arr, heapSize);
    printf("Heap after buildHeap(): ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    insert(arr, &heapSize, 0);
    printf("Heap after insert(0): ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    int rootVal = deleteRoot(arr, &heapSize);
    printf("Deleted root value: %d\n", rootVal);
    printf("Heap after deleteRoot(): ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, heapSize);
    printf("Heap sorted (descending, because min-heap): ");
    for (int i = 0; i < heapSize; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


void heapifyDown(int arr[], int size, int i){
    int min = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;

    if (lc < size && arr[lc] < arr[min])
        min = lc;

    if (rc < size && arr[rc] < arr[min])
        min = rc;
    
    if (min != i){
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;

        heapifyDown(arr, size, min);
    }
}

void heapifyUp(int arr[], int i){
    int parent = (i - 1) / 2;

    if (i != 0 && arr[i] < arr[parent]){
        int temp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = temp;

        heapifyUp(arr, parent);
    }
}

void buildHeap(int arr[], int size){
    for (int i = (size / 2) - 1; i >= 0; i--){
        heapifyDown(arr, size, i);
    }
}

void heapSort(int arr[], int size){
    buildHeap(arr, size);

    for (int i = size - 1; i > 0; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapifyDown(arr, i, 0);
    }
}

void insert(int arr[], int* size, int value){
    arr[*size] = value;
    heapifyUp(arr, *size);
    (*size)++;
}

int deleteRoot(int arr[], int* size){
    if (*size == 0) return 0;

    int root = arr[0];
    arr[0] = arr[*size - 1];
    (*size)--;
    heapifyDown(arr, *size, 0);

    return root;
}

