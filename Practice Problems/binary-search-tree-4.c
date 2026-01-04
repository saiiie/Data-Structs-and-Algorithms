// GRIDLOCK POWER SYSTEM DISTRIBUTION (BST #5)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PowerNode {
    int voltage;            // The Key (Unique reading)
    char *sectorName;       // Dynamic String (Requires malloc)
    struct PowerNode *left;
    struct PowerNode *right;
} PowerNode;

// --- HELPER FUNCTIONS (ALREADY DONE) ---

// Helper to visualize the grid (In-Order Traversal)
void printGridStatus(PowerNode *root) {
    if (root != NULL) {
        printGridStatus(root->left);
        printf("[Voltage: %d V] Sector: %s\n", root->voltage, root->sectorName);
        printGridStatus(root->right);
    }
}

// Helper to free memory (Optional for this exercise, but good to have)
void shutdownGrid(PowerNode *root) {
    if (root != NULL) {
        shutdownGrid(root->left);
        shutdownGrid(root->right);
        free(root->sectorName);
        free(root);
    }
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

PowerNode* addSector(PowerNode *root, int voltage, char *name) {
    // BASE CASE
    if (root == NULL){
        PowerNode* reading = malloc(sizeof(PowerNode));
        reading->sectorName = malloc(sizeof(char) * strlen(name) + 1);
        strcpy(reading->sectorName, name);
        reading->voltage = voltage;
        reading->left = NULL;
        reading->right = NULL;

        root = reading;
        return root;
    }

    // LOCATING EMPTY SPOT
    if (voltage < root->voltage){
        root->left = addSector(root->left, voltage, name);
    }
    else if (voltage > root->voltage){
        root->right = addSector(root->right, voltage, name);
    }
}

PowerNode* findSector(PowerNode *root, int targetVoltage) {
    // CASE: READING NOT FOUND
    if (root == NULL) return NULL;

    // IF: READING MATCHED
    if (targetVoltage == root->voltage)
        return root;
    
    // ELSE: MOVE DOWNWARDS
    if (targetVoltage < root->voltage){
        return findSector(root->left, targetVoltage);
    }
    else if (targetVoltage > root->voltage){
        return findSector(root->right, targetVoltage);
    }
}

int countStableSectors(PowerNode *root, int minV, int maxV) {
    int count = 0;

    // BASE CASE
    if (root == NULL) return 0;

    // VOLTAGE WITHIN RANGE
    if (root->voltage >= minV && root->voltage <= maxV){
        count++;
        count += countStableSectors(root->left, minV, maxV);
        count += countStableSectors(root->right, minV, maxV);
    }

    // ELSE: MOVE DOWNWARDS
    else if (root->voltage < minV){
        count += countStableSectors(root->right, minV, maxV);
    }
    else if (root->voltage > maxV){
        count += countStableSectors(root->left, minV, maxV);
    }

    return count;
}

int main() {
    PowerNode *gridRoot = NULL;

    printf("--- GRIDLOCK SYSTEM ONLINE ---\n");

    // TEST 1: Registering Live Data (Insertions)
    printf("\n[1] Receiving Telemetry...\n");
    
    // Root (Standard)
    gridRoot = addSector(gridRoot, 115, "Downtown Core"); 
    
    // Low Voltage (Brownout Risks)
    addSector(gridRoot, 100, "Old Suburbs");
    addSector(gridRoot, 90, "Abandoned Zone"); 
    addSector(gridRoot, 105, "Residential Block A");

    // High Voltage (Surge Risks)
    addSector(gridRoot, 130, "Industrial Park");
    addSector(gridRoot, 125, "Neon District");
    addSector(gridRoot, 220, "Power Plant Main");

    printf(">> Current Grid Status (Sorted by Voltage):\n");
    printGridStatus(gridRoot);

    // TEST 2: Searching Specific Readings
    printf("\n[2] Verifying Surge in Industrial Park (130V)...\n");
    PowerNode *alert = findSector(gridRoot, 130);
    if (alert) printf(">> CONFIRMED: %s is reporting %dV.\n", alert->sectorName, alert->voltage);
    else printf(">> ERROR: Signal not found.\n");

    // TEST 3: The Stability Audit (Range Logic)
    // We want to count how many sectors are "Safe".
    // Let's assume Safe Range is 105V to 125V (Inclusive).
    // Expected Matches:
    // - Residential Block A (105)
    // - Downtown Core (115)
    // - Neon District (125)
    // Expected Count: 3
    // Excluded: 90, 100 (Too Low), 130, 220 (Too High)
    
    printf("\n[3] Auditing Safe Zones (105V - 125V)...\n");
    int safeCount = countStableSectors(gridRoot, 105, 125);
    printf(">> Sectors within Safe Limits: %d (Expected: 3)\n", safeCount);

    if (safeCount == 3) printf(">> AUDIT SUCCESS: Logic Verified.\n");
    else printf(">> AUDIT FAILURE: Check your recursion.\n");

    // TEST 4: Cleanup
    printf("\n[4] Shutting down grid...\n");
    shutdownGrid(gridRoot);
    printf(">> System Offline.\n");
    
    return 0;
}
