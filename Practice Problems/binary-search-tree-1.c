#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h> // For INT_MIN and INT_MAX

// --- Structure Definitions ---

typedef struct AssetNode {
    int priorityCode; // The BST Key (lower number = higher priority)
    char assetName[30];
    struct AssetNode *left;
    struct AssetNode *right;
} AssetNode;

typedef struct {
    AssetNode *root;
    int count;
} AssetNetwork;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---
void initNetwork(AssetNetwork *net);
AssetNode* createNode(int code, char *name);
void inOrderTraversal(AssetNode *node);
AssetNode* searchAsset(AssetNode *node, int code);
void corruptTree(AssetNetwork *net);

// --- YOUR TASKS START HERE ---
AssetNode* insertSatellite(AssetNode *root, int code, char *name);
AssetNode* findHighestPriorityInRange(AssetNode *root, int maxCode);
bool isValidBST(AssetNode *node, int min, int max);

int main() {
    AssetNetwork net;
    initNetwork(&net);

    // --- BUILD A VALID BST ---
    // Keys: 50, 30, 70, 10, 40, 60, 80, 15 (inserted out of order)
    printf("\n[Test 1] Building Asset Network (Insertion)...\n");
    net.root = insertSatellite(net.root, 50, "HQ_Link");
    net.root = insertSatellite(net.root, 30, "Sensor_A");
    net.root = insertSatellite(net.root, 70, "Backup_B");
    net.root = insertSatellite(net.root, 10, "Uplink_X");
    net.root = insertSatellite(net.root, 40, "Monitor_C");
    net.root = insertSatellite(net.root, 60, "Relay_D");
    net.root = insertSatellite(net.root, 80, "Drone_E");
    net.root = insertSatellite(net.root, 15, "Stealth_Z");

    printf("\nIn-Order Traversal (Should be sorted by code):\n");
    inOrderTraversal(net.root);
    printf("\n\n");

    // --- TEST VALIDATION ON VALID TREE ---
    printf("[Test 2] Initial BST Validation...\n");
    if (isValidBST(net.root, INT_MIN, INT_MAX)) {
        printf("PASSED: The network is currently valid.\n");
    } else {
        printf("FAILED: Validation reported an error on a valid tree.\n");
    }
    
    // --- TEST SEARCH IN RANGE ---
    printf("\n[Test 3] Finding Highest Priority Asset (code <= 35)...\n");
    AssetNode *found = findHighestPriorityInRange(net.root, 35); // Expected code: 30
    if (found && found->priorityCode == 30) {
        printf("PASSED: Found highest priority asset: %s [%d]\n", found->assetName, found->priorityCode);
    } else {
        printf("FAILED: Expected code 30, but found %s [%d]\n", found ? found->assetName : "NULL", found ? found->priorityCode : -1);
    }
    
    // --- CORRUPT AND TEST VALIDATION ---
    corruptTree(&net);
    printf("\n[Test 4] Validation Check on CORRUPTED Tree...\n");
    if (!isValidBST(net.root, INT_MIN, INT_MAX)) {
        printf("PASSED: Validation correctly identified the corruption.\n");
    } else {
        printf("FAILED: Validation failed to detect the corruption!\n");
    }

    return 0;
}

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

// Initializes the network structure
void initNetwork(AssetNetwork *net) {
    net->root = NULL;
    net->count = 0;
    printf("[System] Asset Tracking Network Initialized.\n");
}

// Helper function to create a new node
AssetNode* createNode(int code, char *name) {
    AssetNode *newNode = (AssetNode*)malloc(sizeof(AssetNode));
    if (newNode == NULL) {
        perror("Failed to allocate node");
        exit(EXIT_FAILURE);
    }
    newNode->priorityCode = code;
    strcpy(newNode->assetName, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Displays assets in order of Priority Code (In-Order Traversal)
void inOrderTraversal(AssetNode *node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("[%d] %s -> ", node->priorityCode, node->assetName);
        inOrderTraversal(node->right);
    }
}

// Searches for a specific Priority Code
AssetNode* searchAsset(AssetNode *node, int code) {
    if (node == NULL || node->priorityCode == code) {
        return node;
    }
    if (code < node->priorityCode) {
        return searchAsset(node->left, code);
    } else {
        return searchAsset(node->right, code);
    }
}

// Helper function to intentionally break the BST property for testing
void corruptTree(AssetNetwork *net) {
    AssetNode *node10 = searchAsset(net->root, 10);
    AssetNode *node15 = searchAsset(net->root, 15);
    
    // Switch the pointers: move a higher code (15) to the left side of 10
    // This makes the subtree rooted at 10 invalid.
    if (node10 && node15) {
        printf("\n[System] CORRUPTING TREE: Moving Node 15 to the left of Node 10.\n");
        node10->left = node15; // Node 15 is now incorrectly placed
    }
}

typedef struct AssetNode {
    int priorityCode; // The BST Key (lower number = higher priority)
    char assetName[30];
    struct AssetNode *left;
    struct AssetNode *right;
} AssetNode;

// --- YOUR TASKS START HERE ---

/**
 * 1. insertSatellite
 * Inserts a new asset node while maintaining the BST property.
 * @param root: The current root of the (sub)tree to check
 * @param code: The asset's unique Priority Code (key)
 * @param name: The asset's name
 * @return: The new root of the (sub)tree after insertion
 * * Instructions:
 * - This function MUST be recursive.
 * - If root is NULL, create and return the new node.
 * - Traverse left if the new code is lower; traverse right if higher.
 */
AssetNode* insertSatellite(AssetNode *root, int code, char *name) {
    // INSERTS NODE ONCE POSITION IS FOUND
    if (root == NULL){
        AssetNode* asset = malloc(sizeof(AssetNode));
        strcpy(asset->assetName, name);
        asset->priorityCode = code;
        asset->left = NULL;
        asset->right = NULL;
        return root;
    }

    // ELSE, TRAVERSE TO CORRECT SUBTREE
    if (code < root->priorityCode){
        root->left = insertSatellite(root->left, code, name);
    }
    else if (code > root->priorityCode){
        root->right = insertSatellite(root->right, code, name);
    }

    return root;
}

/**
 * 2. findHighestPriorityInRange
 * Finds the asset with the HIGHEST PRIORITY (lowest code) that is
 * still less than or equal to the given maximum code (k).
 * @param root: The root of the BST
 * @param maxCode: The search limit (k)
 * @return: The asset node found, or NULL if no asset fits the criteria.
 * * Instructions:
 * - This requires a guided search, not just finding the minimum value.
 * - Search for the code, but keep track of the "best" candidate found so far.
 */
AssetNode* findHighestPriorityInRange(AssetNode *root, int maxCode) {
    AssetNode* best = NULL;

    while (root != NULL){
        if (maxCode >= root->priorityCode){
            best = root;
            root = root->left;
        }
    }

    return best;
}

/**
 * 3. isValidBST (The Logic Challenge)
 * Recursively validates if the structure is a true Binary Search Tree.
 * @param node: The current node to check
 * @param min: The absolute minimum boundary for this node's subtree (exclusive)
 * @param max: The absolute maximum boundary for this node's subtree (exclusive)
 * @return: true if the subtree rooted at 'node' is a valid BST, false otherwise.
 * * Instructions:
 * - This function MUST be recursive.
 * - The trick is that every node must satisfy the BST property relative to its *ancestors*,
 * not just its parent.
 * - Pass the current node's value as the new 'max' for the left recursion, and the new 'min' for the right recursion.
 */
bool isValidBST(AssetNode *node, int min, int max) {
    bool isBST = true;

    while (isBST == true && node != NULL){
        isBST = isValidBST(node->left, min, node->priorityCode);
        isBST = isValidBST(node->right, node->priorityCode, max);
    }

    return isBST;
}
