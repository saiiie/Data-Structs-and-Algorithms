#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node, *BST;

void insert(BST* root, int value);
void deleteNode(BST* root, int value);
Node* search(Node* root, int value);
Node* findMin(Node* root);
Node* findMax(Node* root);

void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);

int main() {
    BST root = NULL;

    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 60);
    insert(&root, 80);

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
    deleteNode(&root, 70);

    printf("Inorder after deletion: ");
    inorder(root);

    printf("\n");
    return 0;
}

void insert(BST* root, int value) {
    // CASE: Empty tree
    if (*root == NULL){
        BST node = (BST)malloc(sizeof(Node));
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return;
    }

    // CASE: Not empty, locating correct position
    if (value < (*root)->data){
        insert(&(*root)->left, value);
    }
    else if (value > (*root)->data){
        insert(&(*root)->right, value);
    }
}

void deleteNode(BST* root, int value) {
    // CASE: Empty tree
    if (*root == NULL) return;

    // CASE: Locating node
    if (value < (*root)->data){
        deleteNode(&(*root)->left, value);
        return;
    }
    else if (value > (*root)->data){
        deleteNode(&(*root)->right, value);
        return;
    }
    else {
        // CASE: Node has one child
        if ((*root)->left == NULL){
            Node* temp = (*root)->right;
            free((*root));
            (*root) = temp;
            return;
        }
        else if ((*root)->right == NULL){
            Node* temp = (*root)->left;
            free((*root));
            (*root) = temp;
            return;
        }

        // CASE: Node has two children.
        Node* successor = (*root)->right;
        while (successor->left != NULL){
            successor = successor->left;
        }

        (*root)->data = successor->data;
        deleteNode(&(*root)->right, successor->data);
    }
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
