#include <stdio.h>

#define MAX_CAPACITY 100

struct Process {
    int proc_id;
    int priority;
};

struct MaxHeap {
    struct Process heapArray[MAX_CAPACITY];
    int size;
};

void swap(struct Process* a, struct Process* b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void insertElement(struct MaxHeap* heap, struct Process process) {
    if (heap->size == MAX_CAPACITY) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = heap->size++;
    heap->heapArray[index] = process;

    while (index > 0 && heap->heapArray[index].priority > heap->heapArray[(index - 1) / 2].priority) {
        swap(&heap->heapArray[index], &heap->heapArray[(index - 1) / 2]);
        index = (index - 1) / 2;
    }

    printf("Process %d with priority %d inserted.\n", process.proc_id, process.priority);
}

void deleteElement(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty. Cannot delete elements.\n");
        return;
    }

    struct Process deletedProcess = heap->heapArray[0];
    heap->heapArray[0] = heap->heapArray[--heap->size];

    int index = 0;
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap->size && heap->heapArray[leftChild].priority > heap->heapArray[largest].priority) {
            largest = leftChild;
        }

        if (rightChild < heap->size && heap->heapArray[rightChild].priority > heap->heapArray[largest].priority) {
            largest = rightChild;
        }

        if (largest != index) {
            swap(&heap->heapArray[index], &heap->heapArray[largest]);
            index = largest;
        } else {
            break;
        }
    }

    printf("Process %d with priority %d deleted.\n", deletedProcess.proc_id, deletedProcess.priority);
}

void displayHeap(struct MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
    }
    else {
        printf("Max Heap:\n");
        for (int i = 0; i < heap->size; i++) {
            printf("Process %d: Priority %d\n", heap->heapArray[i].proc_id, heap->heapArray[i].priority);
        }
    }
}

int main() {
    struct MaxHeap maxHeap = { .size = 0 };

    int choice;
    struct Process process;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Display the max heap\n");
        printf("4. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID: ");
                scanf("%d", &process.proc_id);
                printf("Enter priority: ");
                scanf("%d", &process.priority);
                insertElement(&maxHeap, process);
                break;

            case 2:
                deleteElement(&maxHeap);
                break;

            case 3:
                displayHeap(&maxHeap);
                break;

            case 4:
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}