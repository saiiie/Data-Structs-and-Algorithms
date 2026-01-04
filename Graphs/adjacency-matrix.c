#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 10

// --- Data Structure ---
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// --- Basic Graph Operations ---

void initGraph(Graph *g, int vertices) {
    // CASE: GRAPH IS FULL
    if (vertices > MAX_VERTICES) {
        printf("[Error] Too many vertices! Max is %d.\n", MAX_VERTICES);
        exit(1);
    }
    
    // INITIALIZE ALL TO 0
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *g, int src, int dest) {
    // CASE: INVALID VERTICES
    if (src >= g->numVertices || dest >= g->numVertices || src < 0 || dest < 0) {
        printf("[Error] Invalid Edge: %d -> %d\n", src, dest);
        return;
    }

    // ADD EDGE
    g->matrix[src][dest] = 1;
    g->matrix[dest][src] = 1;
}

void removeEdge(Graph *g, int src, int dest) {
    if (src >= g->numVertices || dest >= g->numVertices || src < 0 || dest < 0) return;

    // REMOVES EDGE
    g->matrix[src][dest] = 0;
    g->matrix[dest][src] = 0;
}


int hasEdge(Graph *g, int src, int dest) {
    if (src >= g->numVertices || dest >= g->numVertices) return 0;
    return g->matrix[src][dest];
}

void printMatrix(Graph *g) {
    printf("\n   ");
    // COLUMN HEADERS
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // PRINTING ROWS
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d: ", i); // ROW HEADER
        for (int j = 0; j < g->numVertices; j++) {
            // PRINTS VALUES
            printf("%d ", g->matrix[i][j]);
        }
        printf("\n");
    }
}

// --- Main Function (Test) ---

int main() {
    Graph myGraph;

    // 1. Create a Graph with 4 Nodes (0, 1, 2, 3)
    // Visualizing: Square shape
    // 0 -- 1
    // |    |
    // 3 -- 2
    printf("--- [1] Initializing Graph (4 vertices) ---\n");
    initGraph(&myGraph, 4);

    // 2. Connect Edges
    addEdge(&myGraph, 0, 1);
    addEdge(&myGraph, 1, 2);
    addEdge(&myGraph, 2, 3);
    addEdge(&myGraph, 3, 0);
    addEdge(&myGraph, 0, 2); // Diagonal

    // 3. Display
    printMatrix(&myGraph);
    /* Expected Output Logic:
    Row 0 should have 1s at index 1, 2, 3
    Row 1 should have 1s at index 0, 2
    etc...
    */

    // 4. Test Queries
    printf("\n--- [2] Checking Connections ---\n");
    if (hasEdge(&myGraph, 0, 2)) 
        printf("Node 0 is connected to Node 2 (Correct)\n");
    else 
        printf("Node 0 is NOT connected to Node 2 (Error)\n");

    if (hasEdge(&myGraph, 0, 3)) 
        printf("Node 0 is connected to Node 3 (Correct)\n");

    // 5. Remove an Edge
    printf("\n--- [3] Removing Diagonal Edge (0-2) ---\n");
    removeEdge(&myGraph, 0, 2);
    printMatrix(&myGraph);

    return 0;
}