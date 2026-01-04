// VECTOR OUTBREAK (LIST OF CHILDREN #2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_IDS 50
#define EMPTY -1

// --- Advanced Structure Definitions ---

typedef struct PatientNode {
    int patientID;          // Unique ID
    char *name;             // DYNAMIC: Must be malloc'd
    char *location;         // DYNAMIC: Must be malloc'd (e.g., "City Hospital", "Market")
    struct PatientNode *next;
} PatientNode;

typedef struct {
    int rootID;
    // Index = The Infector's ID.
    // The List = The people they infected (Children).
    PatientNode* transmissionMap[MAX_IDS];
} VectorTree;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

void initVector(VectorTree *vt) {
    vt->rootID = EMPTY;
    for (int i = 0; i < MAX_IDS; i++) {
        vt->transmissionMap[i] = NULL;
    }
}

void setIndexCase(VectorTree *vt, int id) {
    vt->rootID = id;
    printf("[System] Index Case (Patient Zero) identified as ID: %d\n", id);
}

// Helper to free all memory (nodes AND strings)
void freeVector(VectorTree *vt) {
    for (int i = 0; i < MAX_IDS; i++) {
        PatientNode* curr = vt->transmissionMap[i];
        while (curr != NULL) {
            PatientNode* toDelete = curr;
            curr = curr->next;
            
            // Critical: Free the strings inside the node first
            if(toDelete->name) free(toDelete->name);
            if(toDelete->location) free(toDelete->location);
            
            free(toDelete);
        }
        vt->transmissionMap[i] = NULL;
    }
    printf("[System] Memory cleanup complete.\n");
}

// --- YOUR TASKS START HERE ---

void recordInfection(VectorTree *vt, int infectorID, int childID, char *name, char *loc){
    // CREATING NODE
    PatientNode* patient = malloc(sizeof(PatientNode));
    patient->name = (malloc(sizeof(char) * strlen(name) + 1));
    patient->location = (malloc(sizeof(char) * strlen(loc) + 1));
    patient->patientID = childID;
    strcpy(patient->name, name);
    strcpy(patient->location, loc);
    
    // INSERTING TO LIST
    patient->next = vt->transmissionMap[infectorID];
    vt->transmissionMap[infectorID] = patient;
}

int countCasesInLocation(VectorTree *vt, int currentID, char *targetLoc) {
    int count = 0;

    PatientNode* curr = vt->transmissionMap[currentID];
    while (curr != NULL){
        // IF: LOCATION MATCHED!
        if (strcmp(curr->location, targetLoc) == 0){
            count++;
            count += countCasesInLocation(vt, curr->patientID, targetLoc);
        }

        // ELSE: MOVE TO NEXT PATIENT
        curr = curr->next;
    }

    return count;
}

void tracePatientZero(VectorTree *vt, int targetID) {
    // PRINT ID
    printf("%d ", targetID);

    // BASE CASE
    if (targetID == 0){
        printf("\n");
        return;
    }
    else {
        printf("<- ");
    }

    // FIND PARENT INDEX
    int idx;
    for (idx = 0; idx < MAX_IDS; idx++){
        PatientNode* curr = vt->transmissionMap[idx];

        while (curr != NULL){
            // IF: ID FOUND
            if (curr->patientID == targetID){
                tracePatientZero(vt, idx);
                return;
            }
            
            // ELSE: MOVE TO NEXT NODE
            curr = curr->next;
        }
    }

    printf("<- UNKNOWN\n");
}

int main() {
    VectorTree outbreak;
    initVector(&outbreak);

    // --- Build the Transmission Tree ---
    // Structure:
    // P0 (Root) @ Airport
    //   -> P1 "Alice" @ "Airport"
    //   -> P2 "Bob"   @ "Cafe"
    //
    // P1 (Alice)
    //   -> P3 "Charlie" @ "Home"
    //   -> P4 "Diana"   @ "Airport"
    //
    // P2 (Bob)
    //   -> P5 "Evan"    @ "Cafe"
    
    printf("\n--- [Test 1] Recording Infections (Dynamic Memory) ---\n");
    setIndexCase(&outbreak, 0);

    // P0 infects P1 and P2
    recordInfection(&outbreak, 0, 1, "Alice", "Airport");
    recordInfection(&outbreak, 0, 2, "Bob", "Cafe");

    // P1 infects P3 and P4
    recordInfection(&outbreak, 1, 3, "Charlie", "Home");
    recordInfection(&outbreak, 1, 4, "Diana", "Airport");

    // P2 infects P5
    recordInfection(&outbreak, 2, 5, "Evan", "Cafe");

    // Verify basic structure
    PatientNode *p0_kids = outbreak.transmissionMap[0];
    if (p0_kids != NULL) {
        printf("P0 infected: %s (%s) and %s (%s)\n",
            p0_kids->name, p0_kids->location,
            p0_kids->next->name, p0_kids->next->location);
        // Note: Output order depends on your Head Insertion logic (LIFO)
    } else {
        printf("FAILED: P0 has no children.\n");
    }

    // --- [Test 2] Recursive Location Counting ---
    printf("\n--- [Test 2] Counting Airport Cases ---\n");
    
    // We want to know how many descendants of P0 were infected at the "Airport".
    // P1 (Airport), P4 (Airport). Total = 2.
    // P2 (Cafe), P3 (Home), P5 (Cafe).
    int airportCases = countCasesInLocation(&outbreak, 0, "Airport");
    printf("Cases at 'Airport' downstream of P0: %d (Expected: 2)\n", airportCases);
    
    int cafeCases = countCasesInLocation(&outbreak, 0, "Cafe");
    printf("Cases at 'Cafe' downstream of P0: %d (Expected: 2)\n", cafeCases); // Bob and Evan


    // --- [Test 3] Tracing Patient Zero (Reverse Logic) ---
    printf("\n--- [Test 3] Tracing Transmission Path ---\n");
    
    // Trace P5 (Evan). Expected: 5 <- 2 <- 0
    printf("Tracing P5: ");
    tracePatientZero(&outbreak, 5);
    printf("\n");

    // Trace P4 (Diana). Expected: 4 <- 1 <- 0
    printf("Tracing P4: ");
    tracePatientZero(&outbreak, 4);
    printf("\n");

    // Trace P0. Expected: 0
    printf("Tracing P0: ");
    tracePatientZero(&outbreak, 0);
    printf("\n");

    // Clean up
    printf("\n");
    freeVector(&outbreak); // This tests if your mallocs were done correctly!

    return 0;
}