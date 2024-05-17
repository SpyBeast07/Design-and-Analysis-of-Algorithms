#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 5

typedef struct Node {
    int count;
    int data[MAX_KEYS - 1];
    struct Node* child[MAX_KEYS];
} Node;

Node* createNode() {
    Node* newNode = malloc(sizeof(Node));
    newNode->count = 0;
    for (int i = 0; i < MAX_KEYS; i++) {
        newNode->data[i] = 0;
        newNode->child[i] = NULL;
    }
    return newNode;
}

int findMinValueIndex(Node* root) {
    while (root->child[0] != NULL) {
        root = root->child[0];
    }
    return root->data[0];
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    int i = 0;
    while (i < root->count && key > root->data[i]) {
        i++;
    }

    if (root->data[i] == key) {
        if (root->child[i] == NULL && root->child[i + 1] == NULL) {
            for (int j = i; j < root->count - 1; j++) {
                root->data[j] = root->data[j + 1];
            }
            root->count--;
            return root;
        }
        if (root->child[i] != NULL && root->child[i + 1] != NULL) {
            int minValue = findMinValueIndex(root->child[i + 1]);
            root->data[i] = minValue;
            root->child[i + 1] = deleteNode(root->child[i + 1], minValue);
            return root;
        }
    }
    if (root->child[i] == NULL) {
        return root;
    }
    root->child[i] = deleteNode(root->child[i], key);
    
    return root;
}

Node* insert(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = createNode();
        newNode->data[0] = key;
        newNode->count = 1;
        return newNode;
    }
    if (root->count < MAX_KEYS - 1) {
        int i = root->count - 1;
        while (i >= 0 && root->data[i] > key) {
            root->data[i + 1] = root->data[i];
            i--;
        }
        root->data[i + 1] = key;
        root->count++;
        return root;
    }
    int i = MAX_KEYS - 1;
    while (i >= 0 && root->data[i - 1] > key) {
        i--;
    }
    root->child[i] = insert(root->child[i], key);
    return root;
}

int display(Node* root) {
    if (root == NULL) {
        return 0;
    }

    Node* queue[100];
    int front = 0, rear = -1;

    queue[++rear] = root;

    int level = 0;
    while (front <= rear) {
        int currentLevelSize = rear - front + 1;

        printf("Level %d: ", level);
        for (int i = 0; i < currentLevelSize; i++) {
        Node* current = queue[front++];

        for (int j = 0; j < current->count; j++) {
            printf("%d ", current->data[j]);
        }

        for (int j = 0; j < current->count + 1; j++) {
            if (current->child[j] != NULL) {
            queue[++rear] = current->child[j];
            }
        }
        }
        level++;
        printf("\n");
    }

    return 1;
}

int main() {
    Node* root = NULL;
    int x, key;

	ask:
        printf("\nM-Way Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print M-Way Tree\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &x);

    switch(x) {
        case 1:
			printf("Enter the key to insert: ");
			scanf("%d", &key);
			root = insert(root, key);  // 10 20 5 30 15 25
            printf("%d inserted.\n", key);
			break;
		case 2:
			printf("Enter the key to delete: ");
			scanf("%d", &key);
			root = deleteNode(root, key);  // 20 30
            printf("%d deleted.\n", key);
			break;
		case 3:
            if (display(root) != 0) {
                printf("M-Way Tree:\n");
            }
            else {
                printf("M-Way Tree is Empty\n");
            }
			display(root);
			break;
		case 4:
			printf("Exit\n");
			break;
		default:
            printf("Wrong input\n");
            break;
    }
	if (x != 4) {
		goto ask;
	}

    return 0;
}