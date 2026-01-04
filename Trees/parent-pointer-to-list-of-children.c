#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define ROOT_NODE -1
#define INVALID_NODE -2

// ======================================
//           TYPE DEFINITIONS
// ======================================

typedef int Node;

// --- Parent Pointer Tree ---
typedef Node TreeParent[MAX_NODES];

// --- Children List Tree ---
typedef struct ChildNode {
    Node childIndex;
    struct ChildNode *next;
} ChildNode;

typedef struct {
    Node rootIndex;
    ChildNode* children[MAX_NODES];
} TreeChild;


// ======================================
//        FUNCTION PROTOTYPES
// ======================================

// --- Parent-Pointer Functions ---
void initParent(TreeParent T);
void makeRootParent(TreeParent T, Node r);
void setParent(TreeParent T, Node child, Node parent);
void printParentTree(TreeParent T);

// --- Children List Functions ---
void initChild(TreeChild *T);
void addChild(TreeChild *T, Node parent, Node child);
void printChildTree(const TreeChild *T);
void freeChildTree(TreeChild *T);

// --- Conversion Function ---
void convertParentPointerToChildrenList(TreeChild *dst, TreeParent src);

int main() {

    // -----------------------------
    // Build Parent Pointer Tree
    // -----------------------------
    TreeParent P;
    initParent(P);

    // Sample tree:
    //      0
    //     / \
    //    1   2
    //   / \   \
    //  3   4   5

    makeRootParent(P, 0);
    setParent(P, 1, 0);
    setParent(P, 2, 0);
    setParent(P, 3, 1);
    setParent(P, 4, 1);
    setParent(P, 5, 2);

    printf("=== Parent Pointer Tree ===\n");
    printParentTree(P);

    // -----------------------------
    // Convert to Children-List Tree
    // -----------------------------
    TreeChild C;
    initChild(&C);

    convertParentPointerToChildrenList(&C, P);

    printf("\n=== Children List Tree ===\n");
    printChildTree(&C);

    freeChildTree(&C);

    return 0;
}

// ---------- PARENT POINTER ----------
void initParent(TreeParent T) {
    for (int i = 0; i < MAX_NODES; i++){
        T[i] = INVALID_NODE;
    }
}

void makeRootParent(TreeParent T, Node r) {
    T[r] = ROOT_NODE;
}

void setParent(TreeParent T, Node child, Node parent) {
    T[child] = parent;
}

void printParentTree(TreeParent T) {
    printf("Index (Child) | Parent\n");
    printf("--------------|-------\n");
    for (int i = 0; i < MAX_NODES; i++) {
        if (T[i] == ROOT_NODE) {
            printf("%13d | ROOT\n", i);
        } else if (T[i] == INVALID_NODE) {
            printf("%13d | (Uninitialized)\n", i);
        } else {
            printf("%13d | %d\n", i, T[i]);
        }
    }
    printf("---------------------------------\n");
}


// ---------- CHILDREN LIST TREE ----------
void initChild(TreeChild *T) {
    for (int i = 0; i < MAX_NODES; i++){
        T->children[i] = NULL;
    }

    T->rootIndex = INVALID_NODE;
}

void addChild(TreeChild *T, Node parent, Node child) {
    ChildNode* node = malloc(sizeof(ChildNode));
    node->childIndex = child;
    node->next = T->children[parent];
    T->children[parent] = node;
}

void printChildTree(const TreeChild *T) {
    printf("Root Index: %d\n", T->rootIndex);
    printf("Parent Index | Children List\n");
    printf("-------------|---------------\n");

    for (int i = 0; i < MAX_NODES; i++) {
        printf("%12d | ", i);
        ChildNode *current = T->children[i];

        if (current == NULL) {
            printf("(None)\n");
        } else {
            while (current != NULL) {
                printf("%d -> ", current->childIndex);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("-----------------------------------------\n");
}

void freeChildTree(TreeChild *T) {
    for (int i = 0; i < MAX_NODES; i++){
        if (T->children[i] == NULL) continue;

        ChildNode* curr = T->children[i];
        while (curr != NULL){
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    T->rootIndex = INVALID_NODE;
}



// ---------- CONVERSION FUNCTION ----------
void convertParentPointerToChildrenList(TreeChild *dst, TreeParent src) {

    // 1. Determine the root (the one with parent == ROOT_NODE)
    // 2. For every node i:
    //        if src[i] == parent, then i is a child of parent
    //        call addChild(dst, parent, i)

    // LOOK FOR ROOT
    for (int i = 0; i < MAX_NODES; i++){
        if (src[i] == ROOT_NODE){
            
        }
    }
}