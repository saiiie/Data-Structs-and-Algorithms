// PARENT POINTER 2 (THE HEIRLOOM REGISTRY)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FAMILY 50
#define ROOT -1
#define UNKNOWN -2

// --- Structure Definitions ---

typedef struct {
    char *name;      // DYNAMIC: Must be malloc'd
    char *heirloom;  // DYNAMIC: Must be malloc'd (e.g., "The Gold Watch")
} Person;

typedef struct {
    Person people[MAX_FAMILY];   // Data array
    int parent[MAX_FAMILY];      // The Parent Pointer Tree (Index = Child, Value = Parent)
    int count;
} AncestryTree;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

// Initializes the registry
void initRegistry(AncestryTree *tree) {
    tree->count = 0;
    for (int i = 0; i < MAX_FAMILY; i++) {
        tree->parent[i] = UNKNOWN;
        tree->people[i].name = NULL;
        tree->people[i].heirloom = NULL;
    }
    printf("[System] Registry initialized.\n");
}

// Finds the index of a person by name
int findPersonID(AncestryTree *tree, char *name) {
    for (int i = 0; i < tree->count; i++) {
        if (tree->people[i].name != NULL && strcmp(tree->people[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

// helper to free dynamic memory to prevent leaks
void freeRegistry(AncestryTree *tree) {
    for (int i = 0; i < tree->count; i++) {
        free(tree->people[i].name);
        free(tree->people[i].heirloom);
    }
    printf("[System] Registry memory cleared.\n");
}

// helper for string duplication (since some compilers don't support strdup)
char* createString(char* str) {
    char* newStr = (char*)malloc(strlen(str) + 1);
    if (newStr) strcpy(newStr, str);
    return newStr;
}

// --- YOUR TASKS START HERE ---

/**
 * 1. registerBirth
 * Adds a new family member to the registry.
 * @param tree: Pointer to the registry
 * @param name: Name of the new member
 * @param heirloom: The item they possess
 * @param parentName: Name of their parent (NULL if they are the Founder/Root)
 * * Instructions:
 * - Find the parent's ID using findPersonID (unless parentName is NULL).
 * - Allocate memory for the new member's name and heirloom (use createString or malloc).
 * - Store the parent's ID in the 'parent' array at the new index.
 * - If parentName is NULL, set parent to ROOT.
 * - Increment count.
 */
void registerBirth(AncestryTree *tree, char *name, char *heirloom, char *parentName) {
    // LOCATE PARENT INDEX
    int parent = findPersonID(tree, parentName);

    // ALLOCATE MEMORY & INSERT
    tree->people[tree->count].heirloom = createString(heirloom);
    tree->people[tree->count].name = createString(name);
    tree->parent[tree->count] = parent;
    tree->count++;
}

/**
 * 2. traceLineage
 * Prints the path from the child UP to the Founder.
 * Format: "Child (Item) -> Parent (Item) -> Grandparent (Item)..."
 * @param tree: Pointer to the registry
 * @param name: The name of the person to start tracing from
 * * Instructions:
 * - Find the start index.
 * - Use a loop to follow the 'parent' array indices upwards.
 * - Stop when you hit ROOT.
 * - Print the Name and Heirloom at each step.
 */
void traceLineage(AncestryTree *tree, char *name) {
    // DISPLAY MEMBER INFO
    int idx = findPersonID(tree, name);
    printf("%s (%s) ", tree->people[idx].name, tree->people[idx].heirloom);

    // BASE CASE + FORMATTING
    if (tree->parent[idx] == ROOT){
        printf("\n");
        return;
    }
    else {
        printf("-> ");
    }

    // MOVE UPWARDS
    char* parent = createString(tree->people[tree->parent[idx]].name);
    traceLineage(tree, parent);
}

bool isAncestor(AncestryTree* tree, int child, int ancestor){
    while (child != 0){
        // IF: ANCESTOR TRACED
        if (tree->parent[child] == ancestor || child == ancestor)
            return true;
        
        // ELSE: MOVE UPWARDS
        child = tree->parent[child];
    }

    // ANCESTOR NOT IN LINEAGE
    return false;
}

/**
 * 3. findCommonMatriarch (The Logic Challenge)
 * Finds the nearest common ancestor (Lowest Common Ancestor) of two people.
 * @param tree: Pointer to the registry
 * @param nameA: First person
 * @param nameB: Second person
 * @return: The index of the common ancestor, or -1 if none found.
 * * Instructions:
 * - You have two paths moving upwards. You need to find where they merge.
 * - Approach 1 (Easy memory, slow): Move A up one step, then trace B all the way up to see if it hits A. Repeat.
 * - Approach 2 (Fast, extra memory): Create a temporary boolean array/marker. Trace A all the way up, marking every ancestor visited. Then trace B up; the first marked node you hit is the answer.
 */
int findCommonMatriarch(AncestryTree *tree, char *nameA, char *nameB) {
    int personA = findPersonID(tree, nameA);
    int personB = findPersonID(tree, nameB);
    int idx = (personA > personB) ? personB : personA;

    while (idx != -1){
        // COMMON MATRIARCH FOUND!
        if (isAncestor(tree, personA, idx) && isAncestor(tree, personB, idx))
            return idx;
        
        // ELSE: MOVE UPWARDS
        else
            idx = tree->parent[idx];
    }

    return -1;
}

int main() {
    AncestryTree vandergelt;
    initRegistry(&vandergelt);

    // --- 1. Build the Family Tree ---
    printf("\n--- [Test 1] Registering Family Members ---\n");
    
    // Generation 1 (Root)
    registerBirth(&vandergelt, "Victoria", "The Diamond Brooch", NULL);
    
    // Generation 2
    registerBirth(&vandergelt, "Edward", "Silver Pocket Watch", "Victoria");
    registerBirth(&vandergelt, "Florence", "Pearl Necklace", "Victoria");
    
    // Generation 3 (Cousins)
    registerBirth(&vandergelt, "George", "War Medal", "Edward");
    registerBirth(&vandergelt, "Mary", "Silk Scarf", "Edward");
    registerBirth(&vandergelt, "Thomas", "Antique Pipe", "Florence");
    
    // Generation 4
    registerBirth(&vandergelt, "Henry", "Gold Ring", "George");

    // Verify Data Entry
    int idHenry = findPersonID(&vandergelt, "Henry");
    if (idHenry != -1 && strcmp(vandergelt.people[idHenry].heirloom, "Gold Ring") == 0) {
        printf("PASSED: Henry registered with Gold Ring.\n");
    } else {
        printf("FAILED: Henry data missing or incorrect.\n");
    }

    // --- 2. Trace Lineage ---
    printf("\n--- [Test 2] Tracing Lineage ---\n");
    printf("Tracing lineage for Henry (Should go Henry->George->Edward->Victoria):\n");
    // Expected output involves names and their heirlooms
    traceLineage(&vandergelt, "Henry");
    
    printf("\nTracing lineage for Thomas (Should go Thomas->Florence->Victoria):\n");
    traceLineage(&vandergelt, "Thomas");


    // --- 3. Solve Disputes (LCA Logic) ---
    printf("\n--- [Test 3] Finding Common Matriarch (LCA) ---\n");

    // Case A: Siblings (George and Mary) -> Parent is Edward
    int lca1 = findCommonMatriarch(&vandergelt, "George", "Mary");
    int idEdward = findPersonID(&vandergelt, "Edward");
    
    if (lca1 == idEdward) 
        printf("PASSED: George and Mary connect at Edward.\n");
    else 
        printf("FAILED: Expected Edward (%d), got ID %d\n", idEdward, lca1);

    // Case B: Cousins (Henry and Thomas) -> Grandmother is Victoria
    // Henry -> George -> Edward -> Victoria
    // Thomas -> Florence -> Victoria
    int lca2 = findCommonMatriarch(&vandergelt, "Henry", "Thomas");
    int idVictoria = findPersonID(&vandergelt, "Victoria");
    
    if (lca2 == idVictoria) 
        printf("PASSED: Henry and Thomas connect at Victoria.\n");
    else 
        printf("FAILED: Expected Victoria (%d), got ID %d\n", idVictoria, lca2);

    // Case C: Direct Ancestry (Henry and Edward) -> Ancestor is Edward
    // If one person is the ancestor of the other, the ancestor is the LCA.
    int lca3 = findCommonMatriarch(&vandergelt, "Henry", "Edward");
    if (lca3 == idEdward) 
        printf("PASSED: Henry and Edward connect at Edward.\n");
    else 
        printf("FAILED: Expected Edward (%d), got ID %d\n", idEdward, lca3);


    // Cleanup
    printf("\n");
    freeRegistry(&vandergelt);

    return 0;
}