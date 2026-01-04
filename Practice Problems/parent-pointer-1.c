#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_AGENTS 50
#define ROOT -1

typedef struct
{
    char codename[30];
    int parentIndex; // The index of this agent's handler
} Agent;

typedef struct
{
    Agent agents[MAX_AGENTS];
    int count; // Current number of agents in the network
} Network;

// --- PRE-IMPLEMENTED HELPER FUNCTIONS ---

// Initializes the network with the "Ghost Leader" at index 0
void initNetwork(Network *net, char *leaderName)
{
    strcpy(net->agents[0].codename, leaderName);
    net->agents[0].parentIndex = ROOT;
    net->count = 1;
    printf("[System] Network initialized. Leader: %s\n", leaderName);
}

// Returns the index of an agent by name, or -1 if not found
int getAgentID(Network *net, char *name)
{
    for (int i = 0; i < net->count; i++)
    {
        if (strcmp(net->agents[i].codename, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// specific debug function to visualize the array
void printNetworkStatus(Network *net)
{
    printf("\n--- GHOST NETWORK REGISTRY ---\n");
    printf("ID | Codename       | Handler ID\n");
    printf("---|----------------|-----------\n");
    for (int i = 0; i < net->count; i++)
    {
        printf("%02d | %-14s | %d\n", i, net->agents[i].codename, net->agents[i].parentIndex);
    }
    printf("------------------------------\n");
}

// --- YOUR TASKS START HERE ---

void recruitOperative(Network *net, char *name, char *handlerName){
    int handlerId = -1;

    // CASE: ARRAY IS FULL
    if (net->count == MAX_AGENTS) return;

    // CASE: CHECK IF HANDLER EXISTS
    for (int i = 0; i < net->count; i++){
        if (strcmp(net->agents[i].codename, handlerName) == 0){
            handlerId = i;
            break;
        }
    }

    // IF: HANDLER DOES NOT EXIST
    if (handlerId == -1){
        return;
    }

    // ELSE: INSERT NEW AGENT
    else {
        net->agents[net->count].parentIndex = handlerId;
        strcpy(net->agents[net->count].codename, name);
        net->count++;
    }
}

bool verifyClearance(Network *net, int superiorID, int subordinateID){
    while (subordinateID != 0){
        // SUPERIOR LOCATED
        if (net->agents[subordinateID].parentIndex == superiorID)
            return true;
        
        // ELSE, UPDATE INDEX
        subordinateID = net->agents[subordinateID].parentIndex;
    }

    return false;
}

int findRendezvousPoint(Network *net, int agentA_ID, int agentB_ID){
    int idx = (agentA_ID < agentB_ID) ? net->agents[agentA_ID].parentIndex : net->agents[agentA_ID].parentIndex;
    bool foundA = false;
    bool foundB = false;

    while (idx != -1){
        foundA = verifyClearance(net, idx, agentA_ID);
        foundB = verifyClearance(net, idx, agentB_ID);

        // IF: COMMON ANCESTOR FOUND
        if (foundA == true && foundB == true){
            return idx;
        }

        // ELSE: UPDATE PARENT
        else {
            idx = net->agents[idx].parentIndex;
        }
    }

    return -1;
}

int main(){
    Network ghostNet;

    // 1. Initialize
    initNetwork(&ghostNet, "Zero"); // Zero is the Root (ID 0)

    // 2. Build the Tree
    // Hierarchy:
    // Zero -> Alpha
    // Zero -> Beta
    // Alpha -> Cobra
    // Alpha -> Viper
    // Beta -> Python
    // Cobra -> Shadow

    printf("\n[Test 1] Recruiting Operatives...\n");
    recruitOperative(&ghostNet, "Alpha", "Zero");
    recruitOperative(&ghostNet, "Beta", "Zero");
    recruitOperative(&ghostNet, "Cobra", "Alpha");
    recruitOperative(&ghostNet, "Viper", "Alpha");
    recruitOperative(&ghostNet, "Python", "Beta");
    recruitOperative(&ghostNet, "Shadow", "Cobra");

    printNetworkStatus(&ghostNet);

    // 3. Test Clearance
    printf("\n[Test 2] Verifying Clearance Levels...\n");
    int idAlpha = getAgentID(&ghostNet, "Alpha");
    int idShadow = getAgentID(&ghostNet, "Shadow");
    int idPython = getAgentID(&ghostNet, "Python");

    // Alpha should command Shadow (Grandparent relationship)
    if (verifyClearance(&ghostNet, idAlpha, idShadow))
        printf("PASSED: Alpha has clearance over Shadow.\n");
    else
        printf("FAILED: Alpha should have clearance over Shadow.\n");

    // Alpha should NOT command Python (Different branch)
    if (!verifyClearance(&ghostNet, idAlpha, idPython))
        printf("PASSED: Alpha has NO clearance over Python.\n");
    else
        printf("FAILED: Alpha managed to access Python's file!\n");

    // 4. Test Rendezvous (LCA)
    printf("\n[Test 3] Calculating Rendezvous Points (LCA)...\n");
    int idViper = getAgentID(&ghostNet, "Viper");

    // LCA of Viper and Shadow should be Alpha
    int lca1 = findRendezvousPoint(&ghostNet, idViper, idShadow);
    if (lca1 == idAlpha)
        printf("PASSED: Viper and Shadow meet at Alpha.\n");
    else
        printf("FAILED: Expected Alpha (%d), got ID %d\n", idAlpha, lca1);

    // LCA of Shadow and Python should be Zero (Root)
    int idZero = getAgentID(&ghostNet, "Zero");
    int lca2 = findRendezvousPoint(&ghostNet, idShadow, idPython);
    if (lca2 == idZero)
        printf("PASSED: Shadow and Python meet at Zero.\n");
    else
        printf("FAILED: Expected Zero (%d), got ID %d\n", idZero, lca2);

    return 0;
}
