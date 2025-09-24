#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to perform Preorder Traversal without recursion
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;

    // Create a stack
    struct Node* stack[100];
    int top = -1;

    // Push root
    stack[++top] = root;

    while (top >= 0) {
        // Pop from stack and print
        struct Node* node = stack[top--];
        printf("%d ", node->data);

        // Push right child first so that left is processed first
        if (node->right)
            stack[++top] = node->right;
        if (node->left)
            stack[++top] = node->left;
    }
}

int main() {
    // Example tree
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder Traversal (Non-Recursive): ");
    preorderTraversal(root);

    return 0;
}
