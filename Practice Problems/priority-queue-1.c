// functions.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int id;
    char description[50];
    int severity;
} RepairTask;

typedef struct {
    RepairTask tasks[MAX_SIZE];
    int count;
} DroneQueue;

// Heap helpers
void sift_up(DroneQueue *q, int child_idx);
void sift_down(DroneQueue *q, int parent_idx);

// Core operations
void schedule_repair(DroneQueue *q, int id, char *desc, int sev);
RepairTask perform_repair(DroneQueue *q);
void escalate_sector_priority(DroneQueue *q, char *sector_name, int boost_amount);

// Queue utilities
void init_queue(DroneQueue *q);
int is_empty(DroneQueue *q);
int is_full(DroneQueue *q);
void swap(RepairTask *a, RepairTask *b);
void print_queue(DroneQueue *q);

int main(){
    DroneQueue stationQueue;
    init_queue(&stationQueue);

    printf("--- SYSTEM STATUS: NORMAL ---\n");

    // 1. Test Enqueue (sift_up logic)
    // Format: schedule_repair(&queue, ID, Description, Severity)
    schedule_repair(&stationQueue, 101, "Cafeteria Microwave Broken", 10);
    schedule_repair(&stationQueue, 102, "Oxygen Recycler Leak", 85);
    schedule_repair(&stationQueue, 103, "Solar Panel Misalignment", 60);
    schedule_repair(&stationQueue, 104, "Hull Vibration Sector 4", 40);
    schedule_repair(&stationQueue, 105, "Main Thruster Overheat", 95);

    printf("Queue after initial alerts (Should see Thruster or Oxygen at top):\n");
    print_queue(&stationQueue);

    // 2. Test The Logic Function (Escalate)
    printf("\n--- WARNING: SECTOR 4 CRITICAL FAILURE ---\n");
    printf("Escalating all 'Sector 4' tasks by +50 priority...\n");

    // This finds "Hull Vibration Sector 4" (severity 40) and boosts it to 90.
    // It must then fix the heap because 90 > 60 (Solar Panel) and 85 (Oxygen).
    escalate_sector_priority(&stationQueue, "Sector 4", 50);

    print_queue(&stationQueue);

    // 3. Test Dequeue (sift_down logic)
    printf("\n--- DEPLOYING DRONES (Processing Tasks) ---\n");

    while (!is_empty(&stationQueue))
    {
        RepairTask current = perform_repair(&stationQueue);
        printf("Releasing Drone for Task %d: [%s] (Severity: %d)\n",
        current.id, current.description, current.severity);
    }

    return 0;
}

// typedef struct {
//     int id;
//     char description[50];
//     int severity;
// } RepairTask;

// typedef struct {
//     RepairTask tasks[MAX_SIZE];
//     int count;
// } DroneQueue;

// Used by: schedule_repair AND escalate_sector_priority
void sift_up(DroneQueue *q, int child_idx){
    int parent = (child_idx - 1) / 2;

    while (child_idx != 0 && q->tasks[child_idx].severity > q->tasks[parent].severity){
        swap(&q->tasks[child_idx], &q->tasks[parent]);

        // MOVE TO NEXT NODE
        sift_up(q, parent);
    }
}

// Moves a node DOWN if it is smaller than its children
// Used by: perform_repair
void sift_down(DroneQueue *q, int parent_idx){
    // CALCULATE INDICES
    int max = parent_idx;
    int left = 2 * max + 1;
    int right = 2 * max + 2;

    // UPDATE MAX
    if (left < q->count && q->tasks[left].severity > q->tasks[max].severity)
        max = left;
    
    if (right < q->count && q->tasks[right].severity > q->tasks[max].severity)
        max = right;

    // SWAP AND HEAPIFY
    if (max != parent_idx){
        // CREATE TEMP VAR
        swap(&q->tasks[max], &q->tasks[parent_idx]);

        // HEAPIFY
        sift_down(q, max);
    }
}

void schedule_repair(DroneQueue *q, int id, char *desc, int sev){
    // CHECK IF FULL
    if (q->count == MAX_SIZE) return;

    // CREATE NEW TASK
    RepairTask task;
    task.id = id;
    task.severity = sev;
    strcpy(task.description, desc);

    // INSERT AT END
    q->tasks[q->count] = task;
    sift_up(q, q->count);
    q->count++;
}

RepairTask perform_repair(DroneQueue *q){
    // STORE ROOT
    RepairTask finishedTask = q->tasks[0];

    // OVERWRITE ROOT AND HEAPIFY
    q->tasks[0] = q->tasks[q->count - 1];
    q->count--;
    sift_down(q, 0);

    return finishedTask;
}

void escalate_sector_priority(DroneQueue *q, char *sector_name, int boost_amount){
    for (int i = 0; i < q->count; i++){
        if (strstr(q->tasks[i].description, sector_name) != NULL){
            // ADD BOOST TO SEVERITY
            q->tasks[i].severity += boost_amount;
            sift_up(q, i);
        }
    }
}

void init_queue(DroneQueue *q){
    q->count = 0;
}

int is_empty(DroneQueue *q){
    return q->count == 0;
}

int is_full(DroneQueue *q){
    return q->count == MAX_SIZE;
}

void swap(RepairTask *a, RepairTask *b){
    RepairTask temp = *a;
    *a = *b;
    *b = temp;
}

void print_queue(DroneQueue *q){
    printf("Current Queue Status (%d tasks):\n", q->count);
    for (int i = 0; i < q->count; i++)
    {
        printf("  [%d] %s (Sev: %d)\n", i, q->tasks[i].description, q->tasks[i].severity);
    }
}