// DUNGEON LOOT TRACKER (OPEN HASHING #5)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5

typedef struct LootNode {
    char name[20];          // Fixed size key
    char *magicEffect;      // DYNAMIC variable (Requires malloc)
    struct LootNode *next;  // Pointer for chaining
} LootNode;

typedef LootNode* LootTable[TABLE_SIZE]; // Array of Pointers

// --- HELPER FUNCTIONS ---

int hash(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) sum += key[i];
    return sum % TABLE_SIZE;
}

void initTable(LootTable table) {
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;
}

void printTable(LootTable table) {
    printf("--- CHEST CONTENTS ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        LootNode *curr = table[i];
        while (curr != NULL) {
            printf("[%s: %s] -> ", curr->name, curr->magicEffect);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

void addLoot(LootTable table, char *name, char *effect) {
    int loc = hash(name);

    LootNode* loot = malloc(sizeof(LootNode));
    loot->magicEffect = malloc(sizeof(char) * strlen(effect) + 1);
    strcpy(loot->name, name);
    strcpy(loot->magicEffect, effect);

    loot->next = table[loc];
    table[loc] = loot;
}

char* checkLoot(LootTable table, char *name) {
    int loc = hash(name);

    LootNode* curr = table[loc];
    while (curr != NULL){
        if (strcmp(curr->name, name) == 0)
            return curr->magicEffect;
        
        curr = curr->next;
    }

    return "Not Found";
}

int sellLoot(LootTable table, char *name) {
    int loc = hash(name);

    LootNode* curr = table[loc];
    LootNode* prev = NULL;
    while (curr != NULL){
        if (strcmp(curr->name, name) == 0){
            // DELETING AT HEAD
            if (prev == NULL){
                table[loc] = curr->next;
                free(curr->magicEffect);
                free(curr);
                return 1;
            }

            prev->next = curr->next;
            free(curr->magicEffect);
            free(curr);
            return 1;
        }

        prev = curr;
        curr = curr->next;
    }

    return 0;
}

int main() {
    LootTable myChest;
    initTable(myChest);

    printf("--- DUNGEON LOOT TRACKER ---\n");

    // TEST 1: Adding Items (Dynamic Allocation)
    // Note: Assuming TABLE_SIZE 5, some of these might collide.
    printf("\n[1] Storing Loot...\n");
    addLoot(myChest, "Excalibur", "Shines with holy light");
    addLoot(myChest, "RustyDagger", "Might give you tetanus");
    addLoot(myChest, "DragonEgg", "Warm to the touch"); 
    // Let's force a collision (Depends on hash, but conceptually):
    addLoot(myChest, "Bone", "Just a bone");

    printTable(myChest);

    // TEST 2: Retrieval
    printf("\n[2] Identifying 'Excalibur'...\n");
    char *desc = checkLoot(myChest, "Excalibur");
    printf(">> Description: %s\n", desc);

    // TEST 3: Deletion (Memory Management)
    printf("\n[3] Selling 'RustyDagger'...\n");
    if (sellLoot(myChest, "RustyDagger")) {
        printf(">> Sold 'RustyDagger'. Memory freed.\n");
    } else {
        printf(">> Item not found.\n");
    }

    printf("\n[4] Selling 'NonExistentItem'...\n");
    if (!sellLoot(myChest, "GhostOrb")) {
        printf(">> Correctly failed to sell missing item.\n");
    }

    printTable(myChest);
    // 'RustyDagger' should be gone. Others remain.

    return 0;
}
