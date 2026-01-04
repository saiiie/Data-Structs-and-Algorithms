// SKY GUARD AIR TRAFFIC (PRIORITY QUEUE #3)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAPACITY 10

typedef struct {
    char flightID[10];
    int urgency; // 0 to 100 (100 = Critical)
} Plane;

typedef struct {
    Plane heap[MAX_CAPACITY];
    int count;
} RunwayQueue;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initQueue(RunwayQueue *q) {
    q->count = 0;
}

void swap(Plane *a, Plane *b) {
    Plane temp = *a;
    *a = *b;
    *b = temp;
}

void printQueue(RunwayQueue *q) {
    printf("--- CURRENT AIRSPACE (Count: %d) ---\n", q->count);
    if (q->count == 0) {
        printf("[Airspace Clear]\n");
        return;
    }
    // Prints array order, which effectively shows the Heap structure
    for (int i = 0; i < q->count; i++) {
        printf("[%d] Flight: %s | Urgency: %d\n", i, q->heap[i].flightID, q->heap[i].urgency);
    }
    printf("------------------------------------\n");
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

void siftUp(RunwayQueue *q, int childIndex) {
    // BASE CASE
    if (childIndex == 0) return;

    int parent = (childIndex - 1) / 2;

    if (q->heap[childIndex].urgency > q->heap[parent].urgency) {
        swap(&q->heap[childIndex], &q->heap[parent]);
        siftUp(q, parent);
    }
}


int addPlane(RunwayQueue *q, char *id, int urgency) {
    // CASE: PLANE IS FULL
    if (q->count >= MAX_CAPACITY) return 0;

    strcpy(q->heap[q->count].flightID, id);
    q->heap[q->count].urgency = urgency;
    siftUp(q, q->count);

    q->count++;
    return 1; // Success
}

void siftDown(RunwayQueue* q, int parent){
    int max = parent;
    int lc = 2 * parent + 1;
    int rc = 2 * parent + 2;

    // CHECKING ORDER
    if (lc < q->count && q->heap[lc].urgency > q->heap[max].urgency)
        max = lc;
    if (rc < q->count && q->heap[rc].urgency > q->heap[max].urgency)
        max = rc;

    // CHECK IF NEED SWAP
    if (max != parent){
        swap(&q->heap[max], &q->heap[parent]);
        siftDown(q, max);
    }
}

Plane landPlane(RunwayQueue *q) {
    Plane landedPlane;

    // CASE: QUEUE IS EMPTY
    if (q->count == 0) {
        landedPlane.urgency = -1;
        return landedPlane;
    }

    // DEQUEUE PLANE
    landedPlane = q->heap[0];
    q->heap[0] = q->heap[q->count - 1];
    q->count--;

    // RESTORE HEAP
    siftDown(q, 0);
    return landedPlane;
}

int main() {
    RunwayQueue skyGuard;
    initQueue(&skyGuard);

    printf("--- STORM WARNING: ATC SYSTEMS ONLINE ---\n");

    // TEST 1: Add Planes (Normal and Urgent)
    // We expect the heap to automatically float the highest number to index 0.
    printf("\n[1] Incoming Traffic...\n");
    
    addPlane(&skyGuard, "UA-505", 20); // Low urgency
    addPlane(&skyGuard, "DL-101", 50); // Medium urgency
    addPlane(&skyGuard, "AF-999", 90); // High urgency!
    addPlane(&skyGuard, "SW-300", 10); // Very low urgency

    printQueue(&skyGuard);
    // Expected Root: AF-999 (90)

    // TEST 2: High Priority Insertion
    // A plane declares MAYDAY. It should sift to the top immediately.
    printf("\n[2] MAYDAY CALL RECEIVED!\n");
    addPlane(&skyGuard, "EMG-001", 100);
    
    printQueue(&skyGuard);
    // Expected Root: EMG-001 (100)

    // TEST 3: Processing the Queue (Dequeue)
    printf("\n[3] Clearing Runway for Landing...\n");
    
    Plane p1 = landPlane(&skyGuard);
    printf(">> LANDED: %s (Urgency: %d)\n", p1.flightID, p1.urgency);
    // Should be EMG-001
    
    Plane p2 = landPlane(&skyGuard);
    printf(">> LANDED: %s (Urgency: %d)\n", p2.flightID, p2.urgency);
    // Should be AF-999
    
    printQueue(&skyGuard);
    // Remaining root should be DL-101 (50)

    // TEST 4: Empty Queue Check
    printf("\n[4] Landing remaining planes...\n");
    landPlane(&skyGuard); // Lands DL-101
    landPlane(&skyGuard); // Lands UA-505
    landPlane(&skyGuard); // Lands SW-300
    
    Plane pEmpty = landPlane(&skyGuard); // Queue empty now
    if (pEmpty.urgency == -1) {
        printf(">> No planes in airspace. Radar clear.\n");
    }

    return 0;
}