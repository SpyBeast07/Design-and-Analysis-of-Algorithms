#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

void printArray(char message[], int arr[], int n)
{
    printf("%s ", message);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < n && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n)
{
    int lastNonLeafNode = (n / 2) - 1;

    for (int i = lastNonLeafNode; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

void insert(int arr[], int *n, int data)
{
    (*n)++;
    arr[*n - 1] = data;

    int i = *n - 1;
    while (i != 0 && arr[(i - 1) / 2] < arr[i])
    {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteNode(int arr[], int *n)
{
    if (*n <= 0)
    {
        printf("Heap is empty.\n");
        return;
    }

    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;

    heapify(arr, *n, 0);

    printf("Deleted element: %d\n", root);
}

int main()
{
    int arr[] = {4, 18, 17, 10, 19, 20, 14, 8, 3, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArray("Array is: ", arr, n);
    buildHeap(arr, n);
    printArray("Heap is: ", arr, n);

    return 0;
}