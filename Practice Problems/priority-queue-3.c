// XENO-CONTAINMENT FAACILITY (RPIORITY QUEUE #4)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 20

typedef struct {
    char speciesName[30];    // Static size
    char *containmentNote;   // DYNAMIC size (Requires malloc)
    int dangerRating;        // Priority Key (Higher = More Dangerous)
} Alien;

typedef struct {
    Alien *heap;             // Dynamic array of Aliens (or static if you prefer, but let's use a pointer to array)
    int count;
    int capacity;
} PriorityQueue;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initQueue(PriorityQueue *pq) {
    pq->count = 0;
    pq->capacity = MAX_CAPACITY;
    pq->heap = (Alien *)malloc(sizeof(Alien) * MAX_CAPACITY);
}

void printQueue(PriorityQueue *pq) {
    printf("--- SECTOR 4 STATUS (Count: %d) ---\n", pq->count);
    if (pq->count == 0) {
        printf("[Facility Empty]\n");
        return;
    }
    // Prints in array order (Level Order Traversal)
    for (int i = 0; i < pq->count; i++) {
        printf("[%d] %s (Danger: %d) | Note: %s\n", 
            i, pq->heap[i].speciesName, pq->heap[i].dangerRating, pq->heap[i].containmentNote);
    }
    printf("-----------------------------------\n");
}

void swap(Alien *a, Alien *b) {
    Alien temp = *a;
    *a = *b;
    *b = temp;
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

void siftDown(PriorityQueue *pq, int index) {
    int max = index;
    int lc = 2 * index + 1;
    int rc = 2 * index + 2;

    if (lc < pq->count && pq->heap[lc].dangerRating > pq->heap[max].dangerRating)
        max = lc;
    if (rc < pq->count && pq->heap[rc].dangerRating > pq->heap[max].dangerRating)
        max = rc;

    if (max != index){
        swap(&pq->heap[max], &pq->heap[index]);
        siftDown(pq, max);
    }
}

int admitAlien(PriorityQueue *pq, char *name, int danger, char *note) {
    if (pq->count >= pq->capacity) return 0;

    // CREATE ALIEN NODE
    Alien alien;
    alien.containmentNote = malloc(sizeof(char) * strlen(note) + 1);
    strcpy(alien.speciesName, name);
    strcpy(alien.containmentNote, note);
    alien.dangerRating = danger;

    // INSERT AND HEAP
    pq->heap[pq->count] = alien;
    pq->count++;

    // SIFT UP
    int child = pq->count - 1;
    while (child != 0){
        int parent = (child - 1) / 2;

        if (pq->heap[child].dangerRating > pq->heap[parent].dangerRating){
            swap(&pq->heap[child], &pq->heap[parent]);
            child = parent;
        }

        // HEAP NOW CORRECT
        else {
            break;
        }
    }
    
    return 1;
}

Alien processAlien(PriorityQueue *pq) {
    Alien topAlien;
    if (pq->count == 0) {
        topAlien.dangerRating = -1;
        return topAlien;
    }

    topAlien = pq->heap[0];
    pq->heap[0] = pq->heap[pq->count - 1];
    pq->count--;
    
    siftDown(pq, 0);
    return topAlien;
}

int main() {
    PriorityQueue sector4;
    initQueue(&sector4);

    printf("--- ALIEN CONTAINMENT PROTOCOL INITIATED ---\n");

    // TEST 1: Admitting Aliens (with Memory Allocation)
    printf("\n[1] Incoming Transfers...\n");
    
    // Normal Danger
    admitAlien(&sector4, "Gloop", 20, "Keep away from water");
    
    // High Danger - Should float up
    admitAlien(&sector4, "Xenomorph", 95, "Acid blood - Handle with care");
    
    // Medium Danger
    admitAlien(&sector4, "Martian", 50, "Allergic to country music");
    
    // Extreme Danger - Should become new Root
    admitAlien(&sector4, "Predator", 99, "Invisibility cloak active");

    printQueue(&sector4);
    // EXPECTED ORDER (roughly):
    // Root: Predator (99)
    // Children: Xenomorph (95), Martian (50) ...

    // TEST 2: Processing (Extract Max)
    printf("\n[2] Processing Highest Threat...\n");
    Alien processed = processAlien(&sector4);
    
    if (processed.dangerRating != -1) {
        printf(">> PROCESSED: %s (Danger: %d)\n", processed.speciesName, processed.dangerRating);
        printf(">> NOTE: %s\n", processed.containmentNote);
        
        // CRITICAL: Free the memory we malloc'd in admitAlien!
        free(processed.containmentNote);
        printf(">> MEMORY CLEARED for %s.\n", processed.speciesName);
    }
    
    printQueue(&sector4);
    // EXPECTED ROOT: Xenomorph (95) - (Next highest)

    // TEST 3: Heap Logic Check
    printf("\n[3] Processing Next Threat...\n");
    processed = processAlien(&sector4); // Should be Xenomorph
    printf(">> PROCESSED: %s (Danger: %d)\n", processed.speciesName, processed.dangerRating);
    free(processed.containmentNote);

    printQueue(&sector4);
    // EXPECTED ROOT: Martian (50)

    // Cleanup rest of heap (Optional, but good practice in C)
    // In a real exam, you'd write a cleanup function loop.
    
    return 0;
}
