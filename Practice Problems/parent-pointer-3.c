// THE HIVE MIND (PARENT POINTER)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HIVE_SIZE 20

typedef enum { QUEEN, WARRIOR, DRONE } Caste;

typedef struct {
    char *name;         // DYNAMIC string (malloc required)
    int psiLevel;       // Mental strength
    Caste caste;        // Type of alien
    int masterIndex;    // PARENT POINTER: Index of the superior (-1 if Root)
} AlienNode;

typedef struct {
    AlienNode pool[MAX_HIVE_SIZE];
    int count;
} HiveMind;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initHive(HiveMind *hive) {
    hive->count = 0;
}

const char* getCasteName(Caste c) {
    switch(c) {
        case QUEEN: return "QUEEN";
        case WARRIOR: return "WARRIOR";
        case DRONE: return "DRONE";
        default: return "UNKNOWN";
    }
}

void printHiveSummary(HiveMind *hive) {
    printf("--- HIVE STATUS ---\n");
    for (int i = 0; i < hive->count; i++) {
        AlienNode *a = &hive->pool[i];
        printf("[%d] %s (%s) | Master Index: %d\n", 
            i, a->name, getCasteName(a->caste), a->masterIndex);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

int spawnAlien(HiveMind *hive, char *name, int psi, Caste caste, int masterIdx) {
    // CASE: HIVE IS FULL
    if (hive->count >= MAX_HIVE_SIZE) return -1;

    hive->pool[hive->count].name = malloc(sizeof(char) * strlen(name) + 1);
    strcpy(hive->pool[hive->count].name, name);
    hive->pool[hive->count].masterIndex = masterIdx;
    hive->pool[hive->count].psiLevel = psi;
    hive->pool[hive->count].caste = caste;
    
    hive->count++;
    return hive->count - 1;
}

int findQueen(HiveMind *hive, int startIndex) {
    
    while (startIndex != -1){
        // IF: REACHED QUEEN
        if (hive->pool[startIndex].masterIndex == -1)
            return startIndex;
        
        // ELSE: MOVE TO MASTER
        startIndex = hive->pool[startIndex].masterIndex;
    }

    return -1;
}

int calculateSynapticDelay(HiveMind *hive, int targetIndex) {
    int count = 0;

    // STOP WHEN AT ROOT
    while (hive->pool[targetIndex].masterIndex != -1){
        count++;
        targetIndex = hive->pool[targetIndex].masterIndex;
    }

    return count;
}

int main() {
    HiveMind zergonHive;
    initHive(&zergonHive);

    printf("--- HIVE MIND AWAKENING ---\n");

    // TEST 1: Spawning the Queen (Root)
    // Master is -1 because she answers to no one.
    int queenIdx = spawnAlien(&zergonHive, "Overmind", 9000, QUEEN, -1);
    printf("Queen spawned at index: %d\n", queenIdx);

    // TEST 2: Spawning Subordinates
    // Warriors serve the Queen (Index 0).
    int w1 = spawnAlien(&zergonHive, "Hunter", 500, WARRIOR, queenIdx);
    int w2 = spawnAlien(&zergonHive, "Crusher", 600, WARRIOR, queenIdx);
    
    // Drones serve the Warriors.
    // 'WorkerA' serves 'Hunter' (Index 1)
    int d1 = spawnAlien(&zergonHive, "WorkerA", 50, DRONE, w1);
    // 'WorkerB' serves 'Crusher' (Index 2)
    int d2 = spawnAlien(&zergonHive, "WorkerB", 50, DRONE, w2);
    // 'Larva' serves 'WorkerA' (Index 3) - A deep hierarchy!
    int l1 = spawnAlien(&zergonHive, "Larva", 10, DRONE, d1);

    printHiveSummary(&zergonHive);

    // TEST 3: Finding the Root
    printf("\n[3] Tracing Lineage for 'Larva' (Index %d)...\n", l1);
    int root = findQueen(&zergonHive, l1);
    if (root == queenIdx) printf(">> SUCCESS: Trace leads to Queen 'Overmind'.\n");
    else printf(">> FAILURE: Trace ended at index %d.\n", root);

    // TEST 4: Calculating Depth (Logic)
    // Larva (5) -> WorkerA (3) -> Hunter (1) -> Queen (0).
    // This is 3 hops.
    printf("\n[4] Calculating Synaptic Delay for 'Larva'...\n");
    int delay = calculateSynapticDelay(&zergonHive, l1);
    printf(">> Delay: %d hops (Expected: 3)\n", delay);
    
    if (delay == 3) printf(">> LOGIC VERIFIED.\n");
    else printf(">> LOGIC ERROR.\n");

    // TEST 5: Cleanup (Memory)
    // In a real exam, demonstrate you know how to free the dynamic names.
    printf("\n[5] Hive Destroyed (Memory Cleanup)...\n");
    for(int i=0; i<zergonHive.count; i++) {
        free(zergonHive.pool[i].name);
    }
    printf(">> Memory Freed.\n");

    return 0;
}