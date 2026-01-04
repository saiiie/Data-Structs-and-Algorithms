#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

Node* insert(Node* root, int value);
Node* search(Node* root, int value);
Node* findMin(Node* root);
Node* findMax(Node* root);
Node* deleteNode(Node* root, int value);

void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

int main() {
    Node* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder (sorted): ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    // ---- SEARCH ----
    printf("\n\nSearching for 40...\n");
    Node* s = search(root, 40);
    if (s != NULL) printf("Found %d!\n", s->data);
    else printf("Not found.\n");

    // ---- MIN & MAX ----
    printf("\nMinimum value: %d\n", findMin(root)->data);
    printf("Maximum value: %d\n", findMax(root)->data);

    // ---- DELETE ----
    printf("\nDeleting 70...\n");
    root = deleteNode(root, 70);

    printf("Inorder after deletion: ");
    inorder(root);

    printf("\n");
    return 0;
}

Node* insert(Node* root, int value) {
    // CASE: Empty Tree
    if (root == NULL){
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    // CASE: Value is LESS than the root
    if (value < root->data){
        root->left = insert(root->left, value);
    }

    // CASE: Value is MORE than the root
    else if (value > root->data){
        root->right = insert(root->right, value);
    }
    
    return root;
}

Node* search(Node* root, int value) {
    // CASE: Empty tree
    if (root == NULL)
        return NULL;

    // CASE: Node is found
    if (root->data == value)
        return root;

    // ELSE: Move one level lower based on value
    if (value < root->data){
        // CASE: Value does not exist.
        if (root->left == NULL){
            return NULL;
        }

        return search(root->left, value);
    }

    else if (value > root->data){
        // CASE: Value does not exist.
        if (root->right == NULL){
            return NULL;
        }

        return search(root->right, value);
    }
}

Node* findMin(Node* root) {
    if (root->left != NULL){
        return findMin(root->left);
    }

    return root;
}

Node* findMax(Node* root) {
    if (root->right != NULL){
        return findMax(root->right);
    }

    return root;
}

Node* deleteNode(Node* root, int value) {
    // CASE: Tree is empty.
    if (root == NULL) return root;

    // CASE: Current node does not match. Move one level lower.
    if (value < root->data){
        root->left = deleteNode(root->left, value);
        return root;
    }
    else if (value > root->data){
        root->right = deleteNode(root->right, value);
        return root;
    }

    // CASE: Node is found!
    else {
        // CASE: Node has no left child.
        if (root->left == NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }

        // CASE: Node has no right child
        else if (root->right == NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        };

        // CASE: Node has TWO children.
        Node* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
        return root;
    }
}

void inorder(Node* root) {
    // left → root -> right
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node* root) {
    // root → left → right
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    // left → right → root
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
