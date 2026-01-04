// MYSTIC ALCHEMISTS GUILD (COMPWORD #4)

#include <stdio.h>
#include <stdbool.h>

// --- DEFINITIONS ---
typedef unsigned int Potion;

// Ingredient Bit Definitions
#define TOADSTOOL   (1 << 0) // 1
#define LEAD        (1 << 1) // 2
#define SULFUR      (1 << 2) // 4
#define ARSENIC     (1 << 3) // 8
#define MERCURY     (1 << 4) // 16
#define GOLD_DUST   (1 << 5) // 32

// A Mask representing all dangerous ingredients (Arsenic | Mercury | Toadstool)
#define TOXIC_MASK  (ARSENIC | MERCURY | TOADSTOOL) 

// --- HELPER FUNCTION ---
void analyzeCauldron(Potion p) {
    printf("Cauldron Content (Binary): ");
    for (int i = 5; i >= 0; i--) {
        printf("%d", (p >> i) & 1);
    }
    printf(" (Decimal: %u)\n", p);
}

// --- STUDENT TO IMPLEMENT THESE 3 FUNCTIONS ---

void infuseIngredient(Potion *p, unsigned int ingredientFlag) {
    *p = *p | ingredientFlag;
}

void purifyPotion(Potion *p) {
    unsigned int bit_mask;
    bit_mask |= ARSENIC;
    bit_mask |= MERCURY;
    bit_mask |= TOADSTOOL;

    *p &= ~bit_mask;
}

int checkReaction(Potion p) {
    bool mercury = p & MERCURY;
    bool sulfur = p & SULFUR;
    bool gold = p & GOLD_DUST;
    bool lead = p & LEAD;

    if (mercury == true && sulfur == true)
        return -1;
    else if (gold == false && lead == false)
        return 1;
    else
        return 0;
}

int main() {
    Potion cauldron = 0;
    
    printf("--- ALCHEMY LAB 101 ---\n");

    // TEST 1: Basic Infusion
    printf("\n[1] Adding Sulfur and Mercury...\n");
    infuseIngredient(&cauldron, SULFUR);
    infuseIngredient(&cauldron, MERCURY);
    analyzeCauldron(cauldron);
    // Expected: 010100 (Decimal 20)

    // TEST 2: Danger Check
    printf("\n[2] Checking Reaction...\n");
    int result = checkReaction(cauldron);
    if (result == -1) printf(">> RESULT: BOOM! Explosion detected.\n");
    else printf(">> RESULT: Stable.\n");
    // Expected: BOOM!

    // TEST 3: Complex Clearing (Masking)
    printf("\n[3] Adding Arsenic, Toadstool, and Gold Dust, then Purifying...\n");
    infuseIngredient(&cauldron, ARSENIC);
    infuseIngredient(&cauldron, TOADSTOOL);
    infuseIngredient(&cauldron, GOLD_DUST);
    printf("Before Purify: "); analyzeCauldron(cauldron);
    
    purifyPotion(&cauldron); // Should remove Mercury, Arsenic, Toadstool
    printf("After Purify:  "); analyzeCauldron(cauldron);
    // Expected: Should retain Sulfur (4) and Gold Dust (32).
    // Mercury(16), Arsenic(8), Toadstool(1) should be gone.
    // Result binary: 100100 (36)

    // TEST 4: Success Logic
    printf("\n[4] Checking Final Product...\n");
    // Current state: Gold Dust is ON. Lead is OFF. Sulfur is ON.
    // Logic: Gold ON + Lead OFF = Perfect.
    result = checkReaction(cauldron);
    if (result == 1) printf(">> RESULT: PERFECT ELIXIR! You passed.\n");
    else printf(">> RESULT: Unstable Sludge.\n");

    return 0;
}
