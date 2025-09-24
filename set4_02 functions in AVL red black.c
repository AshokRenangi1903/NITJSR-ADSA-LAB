#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

int height(Node *n) { return n ? n->height : 0; }
int max(int a, int b) { return a > b ? a : b; }

Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key; node->left = node->right = NULL; node->height = 1;
    return node;
}

// Rotations
Node* rightRotate(Node* y) {
    Node* x = y->left; Node* T2 = x->right;
    x->right = y; y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right; Node* T2 = y->left;
    y->left = x; x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
int getBalance(Node* n) { return n ? height(n->left) - height(n->right) : 0; }

// Traversal (for printing tree)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}
void printTree(Node* root) {
    printf("Inorder: ");
    inorder(root);
    printf("\n");
}

// Insert
Node* insertItem(Node* root, int key) {
    if (!root) return createNode(key);
    if (key < root->key) root->left = insertItem(root->left, key);
    else if (key > root->key) root->right = insertItem(root->right, key);
    else return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key) return rightRotate(root);
    if (balance < -1 && key > root->right->key) return leftRotate(root);
    if (balance > 1 && key > root->left->key) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (balance < -1 && key < root->right->key) { root->right = rightRotate(root->right); return leftRotate(root); }

    return root;
}

Node* minValue(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

// Delete
Node* deleteItem(Node* root, int key) {
    if (!root) return root;
    if (key < root->key) root->left = deleteItem(root->left, key);
    else if (key > root->key) root->right = deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) { temp = root; root = NULL; }
            else *root = *temp;
            free(temp);
        } else {
            Node* temp = minValue(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }
    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }

    return root;
}

// Search
Node* searchItem(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return searchItem(root->left, key);
    return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Main
int main() {
    Node* root = NULL;

    // Insert demo
    int values[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++) {
        printf("\nInserting %d...\n", values[i]);
        root = insertItem(root, values[i]);
        printTree(root);
    }

    // Delete demo
    int delVals[] = {40, 50};
    for (int i = 0; i < 2; i++) {
        printf("\nDeleting %d...\n", delVals[i]);
        root = deleteItem(root, delVals[i]);
        printTree(root);
    }

    // Search demo
    int key = 25;
    Node* found = searchItem(root, key);
    if (found) printf("\nKey %d found in tree!\n", key);
    else printf("\nKey %d not found!\n", key);

    deleteTree(root);
    return 0;
}
