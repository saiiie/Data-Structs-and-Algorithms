// SHADOW DATABASE (CLOSED HASHING)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10

typedef enum { EMPTY, OCCUPIED, DELETED } State;

typedef struct {
    char codeName[20];
    int clearanceLevel;
    State state;
} HashEntry;

typedef HashEntry HashTable[TABLE_SIZE];

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void initTable(HashTable table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].state = EMPTY;
    }
}

int hashFunction(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

void printTable(HashTable table) {
    printf("--- Table Dump ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].state == OCCUPIED) 
            printf("[%d]: %s (Lvl %d)\n", i, table[i].codeName, table[i].clearanceLevel);
        else if (table[i].state == DELETED)
            printf("[%d]: X_DELETED_X\n", i);
        else 
            printf("[%d]: ...\n", i);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---
bool addAgent(HashTable table, char *name, int level) {
    int loc = hashFunction(name);

    // ATTEMPTING INSERTION
    for (int idx = 0; idx < TABLE_SIZE; idx++){

        // IF: AVAILABLE SPOT FOUND!
        if (table[loc].state == EMPTY || table[loc].state == DELETED){
            strcpy(table[loc].codeName, name);
            table[loc].clearanceLevel = level;
            table[loc].state = OCCUPIED;
            return true;
        }
        
        // ELSE: MOVE FORWARD
        else{
            loc = (loc + 1) % TABLE_SIZE;
        }
    }
    
    // CASE: TABLE IS FULL
    return false;
}

int findAgent(HashTable table, char *name) {
    int loc = hashFunction(name);
    int start = loc;

    while (table[loc].state != EMPTY){
        // CASE: SKIP DELETED AGENTS
        if (table[loc].state == DELETED) continue;

        // IF: AGENT FOUND
        if (strcmp(table[loc].codeName, name) == 0)
            return loc;
        
        // ELSE: MOVE FORWARD
        else
            loc = (loc + 1) % TABLE_SIZE;
        
        // CASE: LOOPED BACK
        if (loc == start) return -1;
    }
}

bool retireAgent(HashTable table, char *name) {
    int loc = findAgent(table, name);

    // IF: AGENT NOT FOUND
    if (loc == -1) return false;

    // ELSE: RETIRE AGENT
    table[loc].state = DELETED;
    return true;
}

int main() {
    HashTable spyDB;
    initTable(spyDB);

    printf("--- SHADOW DATABASE INITIALIZED ---\n");

    // TEST 1: Insertions with Intentional Collisions
    // Assume TABLE_SIZE is 10.
    // 'Bond' and 'Hunt' might naturally collide or be close depending on ASCII sum.
    
    printf("\n[1] Adding Agents...\n");
    addAgent(spyDB, "Bond", 7);
    addAgent(spyDB, "Hunt", 6);
    addAgent(spyDB, "Bourne", 9); // Should probe if collision occurs
    addAgent(spyDB, "Powers", 4);
    
    printTable(spyDB);

    // TEST 2: Searching
    printf("\n[2] Searching for 'Hunt'...\n");
    int idx = findAgent(spyDB, "Hunt");
    if(idx != -1) printf("Found 'Hunt' at index %d.\n", idx);
    else printf("'Hunt' not found.\n", idx);

    // TEST 3: Lazy Deletion
    printf("\n[3] Retiring 'Bond' (Lazy Deletion)...\n");
    if(retireAgent(spyDB, "Bond")) printf("'Bond' has been retired.\n");
    
    printTable(spyDB); 
    // 'Bond' slot should show X_DELETED_X

    // TEST 4: Search Logic after Deletion
    // This is the critical test. If we search for an agent that was inserted
    // AFTER Bond (and collided), the search must skip over Bond's DELETED spot.
    printf("\n[4] Searching for 'Bourne' (Must skip over Deleted Bond)...\n");
    idx = findAgent(spyDB, "Bourne");
    if(idx != -1) printf("SUCCESS: Found 'Bourne' at index %d (Skipped deletion correctly).\n", idx);
    else printf("FAILURE: Could not find 'Bourne' (Search stopped at Deleted spot).\n");

    return 0;
}