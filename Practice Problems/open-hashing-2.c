#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5
#define INITIAL_CAPACITY 2

typedef struct {
    char modelName[20];
    int quality; // 0-100
} Component;

typedef struct {
    Component *items;   // POINTER to the Dynamic Array
    int count;          // Number of items currently in bin
    int capacity;       // Current size of the allocated array
} Bin;

// The Hash Table
typedef Bin Inventory[TABLE_SIZE];

// --- HELPER FUNCTIONS (ALREADY DONE) ---

int hash(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) sum += key[i];
    return sum % TABLE_SIZE;
}

void initInventory(Inventory inv) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        inv[i].count = 0;
        inv[i].capacity = INITIAL_CAPACITY;
        // Allocate initial small array
        inv[i].items = (Component*)malloc(sizeof(Component) * INITIAL_CAPACITY);
    }
}

void printInventory(Inventory inv) {
    printf("--- CYBER-INVENTORY ---\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bin [%d] (Size: %d/%d): ", i, inv[i].count, inv[i].capacity);
        for (int j = 0; j < inv[i].count; j++) {
            printf("[%s: %d%%] ", inv[i].items[j].modelName, inv[i].items[j].quality);
        }
        printf("\n");
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Add Component (Insert + Resize):
// Calculate hash. Check if the Bin is full (count == capacity).
// IF FULL: Use 'realloc' to double the array size. Update capacity.
// Then, insert the new component at the end (index 'count') and increment count.
void addComponent(Inventory inv, char *name, int quality) {
    // TODO:
    // 1. Get Bin index.
    // 2. Check Capacity.
    //    If full:
    //      newCap = capacity * 2
    //      inv[idx].items = realloc(inv[idx].items, sizeof(Component) * newCap)
    //      Update capacity.
    // 3. Copy data to inv[idx].items[count].
    // 4. count++.

    int loc = hash(name);

    // CHECK IF BIN IS FULL
    if (inv->count == inv->capacity){
        inv->items = realloc(inv->items, sizeof(Component) * (inv->capacity * 2));
        inv->capacity *= 2;
    }

    // INSERT
    inv->items[inv->count++];
}

// 2. Find Component (Search):
// Search the specific Bin's array for a modelName.
// Return the quality rating if found, or -1 if not found.
int findComponent(Inventory inv, char *name) {
    // TODO: Standard Array Linear Search within the hashed bin.
    return -1;
}

// 3. Logic Check: Purge Defects (Delete & Shift)
// Go to a specific Bin (by index).
// Remove ALL items in that bin where quality < threshold.
// CRITICAL: When you remove an item at index 'j', you must SHIFT items
// from j+1 to count-1 to the LEFT to fill the gap.
// Decrement count for every removal.
// Return the number of items removed.
int purgeDefects(Inventory inv, int binIndex, int threshold) {
    // TODO:
    // Loop through the bin's array.
    // If item quality < threshold:
    //    Shift all subsequent items left (inv[k] = inv[k+1]).
    //    Decrement count.
    //    Decrement loop iterator (so you don't skip the next item after shifting!).
    //    Increment removed counter.
    return 0;
}

int main() {
    Inventory myShop;
    initInventory(myShop);

    printf("--- RIPPERDOC SYSTEM ONLINE ---\n");

    // TEST 1: Basic Insertion
    // Let's assume TABLE_SIZE 5.
    // "Kiroshi" and "Sandevistan" might hash to different spots.
    printf("\n[1] Stocking basic items...\n");
    addComponent(myShop, "KiroshiOptics", 90);
    addComponent(myShop, "MantisBlades", 85);
    
    printInventory(myShop);

    // TEST 2: Triggering Reallocation (The Dynamic Array Check)
    // We intentionally force collisions to fill a bin.
    // Assuming INITIAL_CAPACITY is 2. We add 3 items to the SAME bin.
    // We can simulate this by picking names we know might collide, 
    // or by manually checking the hash logic.
    // For this test, let's just add MANY items to ensure *some* bin resizes.
    
    printf("\n[2] Stress Testing Storage (Triggering Realloc)...\n");
    addComponent(myShop, "GorillaArms", 40); // Low quality
    addComponent(myShop, "Monowire", 30);    // Low quality
    addComponent(myShop, "SubdermalArmor", 95);
    addComponent(myShop, "TitaniumBones", 20); // Low quality
    addComponent(myShop, "SmartLink", 55);
    
    // Check output: One of the bins should show Capacity: 4 (doubled from 2).
    printInventory(myShop);

    // TEST 3: Search
    printf("\n[3] Searching for 'MantisBlades'...\n");
    int q = findComponent(myShop, "MantisBlades");
    if (q != -1) printf(">> FOUND: Quality %d%%\n", q);
    else printf(">> Not Found.\n");

    // TEST 4: Purge Logic (Delete & Shift)
    // We pick a bin (let's say bin 0 for example, or iterate them all)
    // and remove anything with Quality < 50.
    printf("\n[4] Purging Defective Ware (Quality < 50)...\n");
    
    int totalRemoved = 0;
    for(int i=0; i<TABLE_SIZE; i++) {
        totalRemoved += purgeDefects(myShop, i, 50);
    }
    printf(">> Recalled %d defective items.\n", totalRemoved);
    
    printInventory(myShop);
    // Logic Verification:
    // 'GorillaArms' (40), 'Monowire' (30), 'TitaniumBones' (20) should be GONE.
    // The array should have no "holes" (NULLs). It should be compact.

    // TEST 5: Cleanup
    printf("\n[5] Cleaning up...\n");
    for(int i=0; i<TABLE_SIZE; i++) {
        free(myShop[i].items); // Free the dynamic arrays
    }
    printf(">> System Shutdown.\n");

    return 0;
}
