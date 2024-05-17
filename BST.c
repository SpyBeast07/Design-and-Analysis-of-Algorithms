#include <stdio.h> 
#include <stdlib.h>  

struct node { 
    int data; 
    struct node* left; 
    struct node* right;
};

struct node* createNode(int data) { 
    struct node* newN = (struct node *) malloc(sizeof(struct node)); 
    newN->data = data; 
    newN->left = NULL; 
    newN->right = NULL; 
    return newN;
}

struct node* searchNode(struct node* root, int key) { 
    while (root != NULL) { 
        if (key == root->data) { 
            return root; } 
		else if (key < root->data) { 
            root = root->left; } 
		else { 
            root = root->right; } 
    } 
    return NULL;
}

void insert(struct node *root, int data) { 
    struct node *prev = NULL; 
    while (root != NULL) { 
        prev = root; 
        if (data == root->data) { 
            printf("Cannot insert %d, already in BST\n", data); 
            return; } 
		else if (data < root->data) { 
            root = root->left; } 
		else { 
            root = root->right; } 
    } 
    struct node* new_node = createNode(data); 
    if (data < prev->data) { 
        prev->left = new_node;
	} 
	else { 
        prev->right = new_node;
	} 
}

struct node* findMin(struct node* root)
{
    if (root == NULL) {
        return NULL;
    }
    else if (root->left != NULL) {
        return findMin(root->left);
    }
    return root;
}

struct node* deleteNode(struct node *root, int key) {	
	if (root == NULL) {
        return NULL;
	}

    if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else if (key < root->data) {
        root->left = deleteNode (root->left, key);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL || root->right == NULL) {
			struct node* temp;
            if (root->left == NULL) {
                temp = root->right;
            }
            else {
                temp = root->left;
            }
            free(root);
            return temp;
        }
        else {
            struct node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

unsigned int LeafCount(struct node* node)
{
	if(node == NULL)       
		return 0;
	if(node->left == NULL && node->right==NULL)      
		return 1;            
	else
		return (LeafCount(node->left) + LeafCount(node->right));      
}

int height(struct node* root)
{
    if (root == NULL)
        return 0;
    else {
        int lheight = height(root->left);
        int rheight = height(root->right);

        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void inOrder(struct node* root) {
	if (root == NULL) {
		return;
	}

    if (root != NULL) { 
        inOrder(root->left); 
        printf("%d ", root->data); 
        inOrder(root->right);
	} 
}

void preOrder(struct node* root) {
	if (root == NULL) {
		return;
	}

    if (root != NULL) { 
        printf("%d ", root->data); 
        preOrder(root->left); 
        preOrder(root->right);
	} 
}

void postOrder(struct node* root) {
	if (root == NULL) {
		return;
	}

    if (root != NULL) { 
        postOrder(root->left); 
        postOrder(root->right); 
        printf("%d ", root->data);
	} 
}

void printCurrLevel(struct node* root, int level)
{
    if (root == NULL) {
        return;
	}
    if (level == 1) {
        printf("%d ", root->data);
	}
    else if (level > 1) {
        printCurrLevel(root->left, level - 1);
        printCurrLevel(root->right, level - 1);
    }
}

void LevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++) {
		printf("\n");
        printCurrLevel(root, i);
	}
}

int main() {
    struct node* root;
    int x, key, searchKey, first;

	ask:
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Count leaf nodes\n");
        printf("5. Inorder Traversal\n");
        printf("6. Preorder Traversal\n");
        printf("7. Postorder Traversal\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &x);

    switch(x) {
        case 1:
			printf("Enter the key to insert: ");
			scanf("%d", &key);
			if (root == NULL) {
				root = createNode(key);
				first = key;
				break;
			}
			insert(root, key);
			break;
		case 2:
			printf("Enter the key to delete: ");
			scanf("%d", &key);
			if (key == first) {
				printf("Can't delete the root node\n");
				break;
			}
			deleteNode(root, key);
			break;
		case 3:
			printf("Enter the key to search: ");
			scanf("%d", &searchKey);
			if (searchNode(root, searchKey) != NULL)
				printf("%d is found in the tree.\n", searchKey);
			else
				printf("%d is not found in the tree.\n", searchKey);
			break;
		case 4:
			printf("Leaf node count: ");
			printf("%d\n", LeafCount(root));
			break;
		case 5:
			printf("Inorder traversal: ");
			inOrder(root);
			printf("\n");
			break;
		case 6:
			printf("Preorder traversal: ");
			preOrder(root);
			printf("\n");
			break;
		case 7:
			printf("Postorder traversal: ");
			postOrder(root);
			printf("\n");
			break;
		case 8:
			printf("Levelorder traversal: ");
			LevelOrder(root);
			printf("\n");
			break;
		case 9:
			printf("Exit\n");
			break;
		default:
            printf("Wrong input\n");
            break;
    }
	if (x != 9) {
		goto ask;
	}

    return 0; 
}