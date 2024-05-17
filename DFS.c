#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
};

struct Graph {
    int vertices;
    struct List* array;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->array = (struct List*)malloc(vertices * sizeof(struct List));

    for (int i = 0; i < vertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void DFS(struct Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* currentNode = graph->array[vertex].head;
    while (currentNode) {
        int adjacentVertex = currentNode->data;
        if (!visited[adjacentVertex]) {
            DFS(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}

void DFSTraversal(struct Graph* graph, int* order, int orderSize) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < orderSize; i++) {
        if (!visited[order[i]]) {
            DFS(graph, order[i], visited);
        }
    }

    free(visited);
}

int main() {
    int vertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    struct Graph* graph = createGraph(vertices);

    int choice;
    do {
        printf("\nMenu:\n");
        printf("Add an edge- 1\n");
        printf("Perform DFS traversal- 2\n");
        printf("Exit- 3\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {  // 1 2 0 1 0 2 1 1 2 1 0 1 1 3 3 1 1 3
                int src, dest;
                printf("Enter source and destination vertices (0 to %d): ", vertices - 1);
                scanf("%d %d", &src, &dest);
                if (src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
                    printf("Invalid vertices.\n");
                } else {
                    addEdge(graph, src, dest);
                    printf("Edge added successfully.\n");
                }
                break;
            }
            case 2: {
                int startVertex;
                printf("Enter the starting vertex for DFS traversal (0 to %d): ", vertices - 1);
                scanf("%d", &startVertex);
                if (startVertex < 0 || startVertex >= vertices) {
                    printf("Invalid vertex.\n");
                } else {
                    DFSTraversal(graph, &startVertex, 1);
                }
                break;
            }
            case 3:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}