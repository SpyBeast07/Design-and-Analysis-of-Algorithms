#include <stdio.h>
#include <stdlib.h>

struct Process {
    int proc_id;
    int priority;
};

struct Node {
    struct Process data;
    struct Node* next;
};

struct PriorityQueue {
    struct Node* front;
};

void initializeQueue(struct PriorityQueue* queue) {
    queue->front = NULL;
}

void insertElement(struct PriorityQueue* queue, struct Process process) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = process;
    newNode->next = queue->front;
    queue->front = newNode;

    printf("Process %d with priority %d inserted.\n", process.proc_id, process.priority);
}

void deleteElement(struct PriorityQueue* queue) {
    if (queue->front == NULL) {
        printf("Priority queue is empty.\n");
        return;
    }
    
    struct Node* curr = queue->front;
    struct Node* prev = NULL;
    struct Node* maxNode = queue->front;
    struct Node* maxPrev = NULL;

    while (curr != NULL) {
        if (curr->data.priority > maxNode->data.priority) {
            maxNode = curr;
            maxPrev = prev;
        }
        prev = curr;
        curr = curr->next;
    }

    if (maxPrev == NULL) {
        queue->front = maxNode->next;
    }
    else {
        maxPrev->next = maxNode->next;
    }

    printf("Process %d with priority %d deleted.\n", maxNode->data.proc_id, maxNode->data.priority);
    free(maxNode);
}

void displayQueue(struct PriorityQueue* queue) {
    if (queue->front == NULL) {
        printf("Priority queue is empty.\n");
    }
    else {
        printf("Priority Queue:\n");
        struct Node* curr = queue->front;
        while (curr != NULL) {
            printf("Process %d: Priority %d\n", curr->data.proc_id, curr->data.priority);
            curr = curr->next;
        }
    }
}

int main() {
    struct PriorityQueue priorityQueue;
    initializeQueue(&priorityQueue);

    int choice;
    struct Process process;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Display the priority queue\n");
        printf("4. Quit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter process ID: ");
                scanf("%d", &process.proc_id);
                printf("Enter priority: ");
                scanf("%d", &process.priority);
                insertElement(&priorityQueue, process);
                break;

            case 2:
                deleteElement(&priorityQueue);
                break;

            case 3:
                displayQueue(&priorityQueue);
                break;

            case 4:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}