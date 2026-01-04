#include <stdio.h>
#include <stdlib.h>

#define MAX 15
#define ROOT -1
#define EMPTY -2

typedef struct Node {
    int index;
    struct Node *next;
} Node;

typedef struct {
    int root;
    Node* children[MAX];
} Tree;

void init(Tree*);
void makeRoot(Tree*, int);
void addChild(Tree*, int, int);
int getParent(Tree*, int);
int leftMost(Tree*);
int rightMost(Tree*);
void freeTree(Tree*);

int main() {
    Tree T;
    init(&T);

    // --- Build Tree ---
    // Structure:
    //      0 (Root)
    //   /  |  \
    //  1   2   3
    //      |  / \
    //      6  4  5
    // Node indices 1,5,4,6 are leaves.

    makeRoot(&T, 0);

    // Add children to root (head insertion: newest at head)
    addChild(&T, 0, 1);
    addChild(&T, 0, 2);
    addChild(&T, 0, 3);

    // Add children to node 3
    addChild(&T, 3, 4);
    addChild(&T, 3, 5);

    // Add child to node 2
    addChild(&T, 2, 6);

    printf("Root index: %d\n", T.root);

    // Print immediate children of root
    printf("Children of root: ");
    Node* curr = T.children[T.root];
    while (curr != NULL) {
        printf("%d ", curr->index);
        curr = curr->next;
    }
    printf("\n");

    // Leftmost leaf (follow last child recursively)
    int leftLeaf = leftMost(&T);
    printf("Leftmost leaf: %d\n", leftLeaf);  // Expected: 5

    // Rightmost leaf (follow first child recursively)
    int rightLeaf = rightMost(&T);
    printf("Rightmost leaf: %d\n", rightLeaf);  // Expected: 6

    // Test getParent
    printf("Parent of 5: %d\n", getParent(&T, 5)); // Expected: 3
    printf("Parent of 6: %d\n", getParent(&T, 6)); // Expected: 2
    printf("Parent of root: %d\n", getParent(&T, T.root)); // Expected: -1 (ROOT)

    // Clean up memory
    freeTree(&T);

    return 0;
}


void init(Tree* T){
    for (int i = 0; i < MAX; i++)
        T->children[i] = NULL;
    
    T->root = EMPTY;
}

void makeRoot(Tree* T, int index){
    T->root = index;
}

void addChild(Tree* T, int parent, int index){
    Node* child = (Node*)malloc(sizeof(Node));
    child->index = index;
    
    child->next = T->children[parent];
    T->children[parent] = child;
}

int getParent(Tree* T, int child){
    if (T->root == child) return ROOT;

    for (int i = 0; i < MAX; i++){
        Node* curr = T->children[i];

        while (curr != NULL){
            if (curr->index == child)
                return i;
            
            curr = curr->next;
        }
    }

    return EMPTY;
}

int leftMost(Tree* T){
    int idx = T->root;
    if (idx == EMPTY) return EMPTY;

    Node* curr = T->children[idx];
    while (curr != NULL){
        Node* trav = curr;
        while (trav->next != NULL)
            trav = trav->next;
        
        idx = trav->index;
        curr = T->children[idx];
    }

    return idx;
}

int rightMost(Tree* T){
    int idx = T->root;
    if (idx == EMPTY) return EMPTY;

    Node* curr = T->children[idx];
    while (curr != NULL){
        idx = curr->index;
        curr = T->children[idx];
    }

    return idx;
}

void freeTree(Tree* T){
    for (int i = 0; i < MAX; i++){
        Node* curr = T->children[i];
        while (curr != NULL){
            Node* toDelete = curr;
            curr = curr->next;
            free(toDelete);
        }

        T->children[i] = NULL;
    }

    T->root = EMPTY;
}