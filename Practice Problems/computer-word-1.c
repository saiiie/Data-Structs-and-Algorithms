// NEBULA 9 SPACE STATION

#include <stdio.h>
#include <stdbool.h>

// --- DEFINITIONS ---
typedef unsigned int SystemStatus;

// Bit assignments for systems
#define REACTOR_POS 0
#define OXYGEN_POS  1
#define HEATING_POS 2
#define GRAVITY_POS 3
#define SHIELDS_POS 4
#define COMMS_POS   5

// --- HELPER FUNCTIONS (ALREADY DONE) ---

void printSystemStatus(SystemStatus status) {
    printf("Current System Binary: ");
    for (int i = 5; i >= 0; i--) {
        if ((status >> i) & 1) printf("1");
        else printf("0");
    }
    printf("\n");
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

// 1. Turn ON a specific system (Set the bit at 'position')
void activateSystem(SystemStatus *status, int position) {
    if (position < 0 || position > 5) return;

    unsigned int bit_mask = (1 << position);
    *status |= bit_mask;
}

// 2. Turn OFF a specific system (Set the bit at 'position')
void deactivateSystem(SystemStatus *status, int position) {
    if (position < 0 || position > 5) return;

    unsigned int bit_mask = (1 << position);
    *status &= ~bit_mask;
}

// 3. Logic Check: Return TRUE if the system is CRITICAL.
// Critical Condition: REACTOR is ON, AND (Both HEATING and SHIELDS are ON).
bool isSystemCritical(SystemStatus status) {
    bool reactorOn = status & (1 << REACTOR_POS);
    bool heatingOn = status & (1 << HEATING_POS);
    bool shieldsOn = status & (1 << SHIELDS_POS);

    return reactorOn && heatingOn && shieldsOn;
}

int main() {
    SystemStatus nebulaSystems = 0; // All systems off initially

    printf("--- NEBULA 9 DIAGNOSTICS ---\n");

    // TEST 1: Activation
    printf("\n[1] Activating Reactor, Oxygen, and Heating...\n");
    activateSystem(&nebulaSystems, REACTOR_POS);
    activateSystem(&nebulaSystems, OXYGEN_POS);
    activateSystem(&nebulaSystems, HEATING_POS);
    printSystemStatus(nebulaSystems);
    // Expected Binary: 000111 (Decimal 7)

    // TEST 2: Deactivation
    printf("\n[2] Deactivating Oxygen...\n");
    deactivateSystem(&nebulaSystems, OXYGEN_POS);
    printSystemStatus(nebulaSystems);
    // Expected Binary: 000101 (Decimal 5)

    // TEST 3: Logic Check (Safe State)
    printf("\n[3] Checking Safety (Reactor + Heating ON, Shields OFF)...\n");
    if (isSystemCritical(nebulaSystems)) printf("WARNING: CRITICAL OVERLOAD!\n");
    else printf("System Status: STABLE.\n");
    // Expected: STABLE

    // TEST 4: Logic Check (Critical State)
    printf("\n[4] Activating Shields (Risk of Overload)...\n");
    activateSystem(&nebulaSystems, SHIELDS_POS);
    printSystemStatus(nebulaSystems); 
    // Expected Binary: 010101
    
    if (isSystemCritical(nebulaSystems)) printf("WARNING: CRITICAL OVERLOAD!\n");
    else printf("System Status: STABLE.\n");
    // Expected: CRITICAL OVERLOAD

    return 0;
}
