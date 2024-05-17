#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int process_id;
    int priority;
} Process;

typedef struct {
    Process processes[MAX_SIZE];
    int size;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue *pq) {
    pq->size = 0;
}

void insertProcess(PriorityQueue *pq, Process process) {
    if (pq->size >= MAX_SIZE) {
        printf("Priority queue is full.\n");
        return;
    }
    pq->processes[pq->size] = process;
    pq->size++;

    printf("Elements after insertion:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("Process ID: %d, Priority: %d\n", pq->processes[i].process_id, pq->processes[i].priority);
    }
}

void deleteMaxPriorityProcess(PriorityQueue *pq) {
    if (pq->size <= 0) {
        printf("Priority queue is empty.\n");
        return;
    }
    int max_priority_index = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->processes[i].priority > pq->processes[max_priority_index].priority) {
            max_priority_index = i;
        }
    }
    printf("Process with highest priority (ID: %d, Priority: %d) has been deleted.\n",
    pq->processes[max_priority_index].process_id,
    pq->processes[max_priority_index].priority);

    pq->processes[max_priority_index] = pq->processes[pq->size - 1];
    pq->size--;

    printf("Elements after deletion:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("Process ID: %d, Priority: %d\n", pq->processes[i].process_id, pq->processes[i].priority);
    }
}

int main() {
    PriorityQueue pq;
    initializePriorityQueue(&pq);

    int choice;
    Process process;

    while (1) {
        printf("\n1. Insert a process\n2. Delete process with highest priority\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID: ");
                scanf("%d", &process.process_id);
                printf("Enter priority: ");
                scanf("%d", &process.priority);
                insertProcess(&pq, process);
                break;
            case 2:
                deleteMaxPriorityProcess(&pq);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}