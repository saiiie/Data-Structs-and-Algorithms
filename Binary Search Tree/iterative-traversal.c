#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK 100

// --- Data Structure ---
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// --- STACK HELPER (REQUIRED FOR ITERATIVE) ---
typedef struct {
    Node* items[MAX_STACK];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

bool isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Node* node) {
    if (s->top < MAX_STACK - 1) {
        s->items[++(s->top)] = node;
    }
}

Node* pop(Stack* s) {
    if (isEmpty(s)) return NULL;
    return s->items[(s->top)--];
}

// --- BST Helper Functions (Already Implemented) ---

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data) root->left = insert(root->left, value);
    else if (value > root->data) root->right = insert(root->right, value);
    return root;
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---
// NOTE: You must declare "Stack s;" and "initStack(&s);" inside these functions.

// 1. Iterative Preorder
void iterPreorder(Node* root) {
    if (root == NULL) return;

    // ROOT -> LEFT -> RIGHT
    Stack s;
    initStack(&s);
    push(&s, root);

    // LOOP WHILE STACK NOT EMPTY
    while (isEmpty(&s) == false){
        Node* curr = pop(&s);
        printf("%d ", curr->data);

        // PUSH CHILDREN TO STACK
        if (curr->right != NULL) push(&s, curr->right);
        if (curr->left != NULL) push(&s, curr->left);
    }
}

// 2. Iterative Inorder
void iterInorder(Node* root) {
    // LEFT -> ROOT -> RIGHT
    Stack s;
    initStack(&s);
    
    Node* curr = root;
    while (curr != NULL || isEmpty(&s) == false){
        // MOVE TO LEFTMOST
        while (curr != NULL){
            push(&s, curr);
            curr = curr->left;
        }

        // PRINT DATA
        curr = pop(&s);
        printf("%d ", curr->data);

        // MOVE TO THE RIGHT SUBTREE
        curr = curr->right;
    }
}

// 3. Iterative Postorder (Two Stack Method recommended)
void iterPostorder(Node* root) {
    // LEFT -> RIGHT -> ROOT
    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    push(&s1, root);
    while (isEmpty(&s1) == false){
        Node* curr = pop(&s1);
        push(&s2, curr);

        if (curr->left != NULL) push(&s1, curr->left);
        if (curr->right != NULL) push(&s1, curr->left);
    }

    while (isEmpty(&s2) == false){
        Node* curr = pop(&s2);
        printf("%d ", curr->data);
    }
}

// --- Main Function ---

int main() {
    Node* root = NULL;

    // Building the Tree
    //       50
    //      /  \
    //    30    70
    //   /  \  /  \
    //  20  40 60  80
    
    printf("[System] Building Tree...\n");
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Test 1: Preorder
    // Expected: 50 30 20 40 70 60 80
    printf("\n--- Iterative Preorder ---\n");
    iterPreorder(root);
    printf("\n");

    // Test 2: Inorder
    // Expected: 20 30 40 50 60 70 80
    printf("\n--- Iterative Inorder ---\n");
    iterInorder(root);
    printf("\n");

    // Test 3: Postorder
    // Expected: 20 40 30 60 80 70 50
    printf("\n--- Iterative Postorder ---\n");
    iterPostorder(root);
    printf("\n");

    return 0;
}