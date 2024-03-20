#include <stdio.h>
#include <stdlib.h>

// Node structure for the Binary Search Tree
struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode* createNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into BST
struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to perform in-order traversal of BST
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Function to perform pre-order traversal of BST
void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform post-order traversal of BST
void postorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->key);
    }
}

// Function to search for a key in BST
void search(struct TreeNode* root, int key) {
    struct TreeNode* current = root;
    struct TreeNode* parent = NULL;
    while (current != NULL && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current != NULL) {
        printf("Node found with key %d\n", current->key);
        if (parent != NULL) {
            printf("Parent key: %d\n", parent->key);
        } else {
            printf("No parent exists for this node.\n");
        }
    } else {
        printf("Node with key %d not found.\n", key);
    }
}

// Function to count nodes in BST
int countNodes(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to find the height of BST
int height(struct TreeNode* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to find node with maximum key value
struct TreeNode* findMax(struct TreeNode* root) {
    if (root == NULL || root->right == NULL) {
        return root;
    }
    return findMax(root->right);
}

// Main function
int main() {
    struct TreeNode* root = NULL;
    int choice, key;

    do {
        printf("\nBinary Search Tree Operations\n");
        printf("1. Insert\n");
        printf("2. In-order Traversal\n");
        printf("3. Pre-order Traversal\n");
        printf("4. Post-order Traversal\n");
        printf("5. Search by Key\n");
        printf("6. Count Nodes\n");
        printf("7. Find Height\n");
        printf("8. Find Node with Maximum Key\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("In-order Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Pre-order Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 4:
                printf("Post-order Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Enter key to search: ");
                scanf("%d", &key);
                search(root, key);
                break;
            case 6:
                printf("Number of nodes in BST: %d\n", countNodes(root));
                break;
            case 7:
                printf("Height of BST: %d\n", height(root));
                break;
            case 8:
                if (root == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    struct TreeNode* maxNode = findMax(root);
                    printf("Node with maximum key: %d\n", maxNode->key);
                    if (maxNode->key != root->key) {
                        printf("Parent key: %d\n", root->key);
                    } else {
                        printf("No parent exists for this node.\n");
                    }
                }
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid choice.\n");
        }
    } while (choice != 9);

    return 0;
}
