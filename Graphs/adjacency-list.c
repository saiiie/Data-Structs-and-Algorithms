#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10

// --- Data Structures ---

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    Node* head[MAX_VERTICES];
    int numVertices;
} Graph;

// --- Helper: Create a New Node ---
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// --- Basic Graph Operations ---

void initGraph(Graph* g, int vertices) {
    if (vertices > MAX_VERTICES) {
        printf("[Error] Too many vertices!\n");
        exit(1);
    }
    
    // INITIALIZE ALL AS NULL
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        g->head[i] = NULL;
    }
}

void addEdge(Graph* g, int src, int dest) {
    // CREATE NODE
    Node* newNode = createNode(dest);

    // INSERT AT HEAD
    newNode->next = g->head[src];
    g->head[src] = newNode;

    // ADD EDGE (FOR UNDIRECTED ONLY)
    newNode = createNode(src);
    newNode->next = g->head[dest];
    g->head[dest] = newNode;
}

void printGraph(Graph* g) {
    printf("\n--- Adjacency List ---\n");
    for (int i = 0; i < g->numVertices; i++) {
        Node* temp = g->head[i];
        printf("Vertex %d: Head", i);
        
        while (temp != NULL) {
            printf(" -> %d", temp->dest);
            temp = temp->next;
        }
        printf(" -> NULL\n");
    }
}

void freeGraph(Graph* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Node* temp = g->head[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
        g->head[i] = NULL; // Safety reset
    }
    printf("\n[System] Graph memory cleared.\n");
}

// --- Main Function (Test) ---

int main() {
    Graph myGraph;

    // 1. Initialize Graph with 4 vertices
    // 0 -- 1
    // |    |
    // 3 -- 2
    printf("--- [1] Initializing Graph ---\n");
    initGraph(&myGraph, 4);

    // 2. Add Edges
    addEdge(&myGraph, 0, 1);
    addEdge(&myGraph, 1, 2);
    addEdge(&myGraph, 2, 3);
    addEdge(&myGraph, 3, 0);
    addEdge(&myGraph, 0, 2); // Diagonal

    // 3. Display
    /* Expected Output:
    Vertex 0: Head -> 2 -> 3 -> 1 -> NULL
    (Order depends on insertion, usually strictly LIFO)
    */
    printGraph(&myGraph);

    // 4. Clean up
    freeGraph(&myGraph);

    return 0;
}