#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    struct node *LC;
    struct node *RC;
} Node, *BST;

void insertIterative(BST *root, const char *key_data);
void deleteIterative(BST *root, const char *key_data);
Node* searchIterative(BST root, const char *key_data);
void inorder(BST root);
void preorder(BST root);
void postorder(BST root);

int main() {
    BST tree = NULL;

    printf("--- Iterative BST Demo ---\n");

    insertIterative(&tree, "Mango");
    insertIterative(&tree, "Apple");
    insertIterative(&tree, "Banana");
    insertIterative(&tree, "Grape");
    insertIterative(&tree, "Pineapple");
    insertIterative(&tree, "Orange");
    insertIterative(&tree, "Kiwi");

    printf("\nInorder Traversal:\n");
    inorder(tree);

    printf("\n\nSearching for 'Grape':\n");
    Node* found = searchIterative(tree, "Grape");
    if (found)
        printf("Found node with key: %s\n", found->key);
    else
        printf("Not found.\n");

    printf("\nDeleting 'Banana' (iteratively)...\n");
    deleteIterative(&tree, "Banana");

    printf("\nInorder After Delete:\n");
    inorder(tree);
    printf("\n");

    // destroyTree(tree);
    // printf("\nTree destroyed. Memory freed.\n");

    return 0;
}

void insertIterative(BST *root, const char *key_data){
    BST node = (BST)malloc(sizeof(Node));
    node->key = (char*)malloc(sizeof(char) * (strlen(key_data) + 1));
    strcpy(node->key, key_data);
    node->LC = NULL;
    node->RC = NULL;

    // CASE: Tree is empty
    if (*root == NULL){
        *root = node;
        return;
    }

    // ELSE: Iterate to find correct position
    Node* curr = *root;
    Node* parent = NULL;
    while (curr != NULL){
        parent = curr;

        // MOVE LEFT
        if (strcmp(key_data, curr->key) < 0){
            curr = curr->LC;
        }
        // MOVE RIGHT
        else if (strcmp(key_data, curr->key) > 0){
            curr = curr->RC;
        }
        // DUPLICATE FOUND
        else if (strcmp(key_data, curr->key) == 0){
            printf("\"%s\" already exists. Ignoring insertion.\n", key_data);
            return;
        }
    }

    // INSERT NODE
    if (strcmp(key_data, parent->key) < 0){
        parent->LC = node;
    }
    else {
        parent->RC = node;
    }
}

void deleteIterative(BST *root, const char *key_data){
    Node* curr = *root;
    Node* parent = NULL;

    // CASE: Tree is empty
    if (curr == NULL) return;

    // ELSE: Locate node
    while (curr != NULL && strcmp(key_data, curr->key) != 0){
        parent = curr;

        if (strcmp(key_data, curr->key) < 0){
            curr = curr->LC;
        }
        else if (strcmp(key_data, curr->key) > 0){
            curr = curr->RC;
        }
    }

    // CASE: Value not found in tree.
    if (curr == NULL){
        printf("\"%s\" does not exist. Ignoring.\n", key_data);
        return;
    }

    // ==== CASE: Node located! ====
    
    // IF: Node  has one child.
    if (curr->LC == NULL){
        Node* temp = curr->RC;

        if (parent == NULL)
            *root = temp;
        else if (parent->LC == curr)
            parent->LC = temp;
        else
            parent->RC = temp;
        
        return;
    }
    else if (curr->RC == NULL){
        Node* temp = curr->LC;

        if (parent == NULL)
            *root = temp;
        else if (parent->LC == curr)
            parent->LC = temp;
        else
            parent->RC = temp;
        
        return;
    }

    // IF: Node has two children.
    Node* successor = curr->RC;
    while (successor->LC != NULL){
        successor = successor->LC;
    }

    // Swap nodes, and delete successor node.
    curr->key = realloc(curr->key, sizeof(char) * (strlen(successor->key) + 1));
    strcpy(curr->key, successor->key);
    deleteIterative(root, successor->key);
}

Node* searchIterative(BST root, const char *key_data){
    BST curr = root;
    while (curr != NULL && strcmp(key_data, curr->key) != 0){
        if (strcmp(key_data, curr->key) < 0){
            curr = curr->LC;
        }
        else if (strcmp(key_data, curr->key) > 0){
            curr = curr->RC;
        }
    }

    // CASE: Node not found.
    if (curr == NULL)
        return NULL;
    else
        return curr;
}

void inorder(BST root){
    if (root == NULL) return;
    inorder(root->LC);
    printf("\"%s\" ", root->key);
    inorder(root->RC);
}

void preorder(BST root){
    if (root == NULL) return;
    printf("\"%s\" ", root->key);
    preorder(root->LC);
    preorder(root->RC);
}

void postorder(BST root){
    if (root == NULL) return;
    postorder(root->LC);
    postorder(root->RC);
    printf("\"%s\" ", root->key);
}


