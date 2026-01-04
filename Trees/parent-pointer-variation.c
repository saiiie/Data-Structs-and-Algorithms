#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define ROOT -1
#define EMPTY -2

typedef int Tree[MAX];

void initialize(Tree);
void makeRoot(Tree, int);
void setParent(Tree, int, int);
int parent(int, Tree);
int leftMost(Tree);
int rightMost(Tree);

int main() {
    Tree T;
    initialize(T);

    // --- Build Tree ---
    // Structure:
    //      0 (Root)
    //   /  |  \
    //  1   2   3
    //      |   |
    //      6   4
    // Leaves: 1, 4, 6

    makeRoot(T, 0);          // 0 is root

    setParent(T, 1, 0);      // 1's parent is 0
    setParent(T, 2, 0);      // 2's parent is 0
    setParent(T, 3, 0);      // 3's parent is 0

    setParent(T, 6, 2);      // 6's parent is 2
    setParent(T, 4, 3);      // 4's parent is 3

    // --- Print parent info ---
    printf("Parent of 1: %d\n", parent(1, T)); // Expected: 0
    printf("Parent of 6: %d\n", parent(6, T)); // Expected: 2
    printf("Parent of 0 (root): %d\n", parent(0, T)); // Expected: -1 (ROOT)

    // --- Leftmost leaf ---
    int leftLeaf = leftMost(T);
    printf("Leftmost leaf: %d\n", leftLeaf); // Expected: 1 (smallest index leaf)

    // --- Rightmost leaf ---
    int rightLeaf = rightMost(T);
    printf("Rightmost leaf: %d\n", rightLeaf); // Expected: 6 (largest index leaf)

    return 0;
}

void initialize(Tree T){
    for (int i = 0; i < MAX; i++)
        T[i] = EMPTY;
}

void makeRoot(Tree T, int index){
    T[index] = ROOT;
}

void setParent(Tree T, int child, int parent){
    T[child] = parent;
}

int parent(int n, Tree T){
    return T[n];
}

int leftMost(Tree T){
    for (int i = 0; i < MAX; i++){
        if (T[i] == EMPTY) continue;
        
        int flag = 0;
        for (int j = 0; j < MAX; j++){
            if (T[j] == i){
                flag = 1;
                break;
            }
        }

        if (flag == 0) return i;
    }

    return EMPTY;
}

int rightMost(Tree T){
    for (int i = MAX - 1; i >= 0; i--){
        if (T[i] == EMPTY) continue;
        
        int flag = 0;
        for (int j = 0; j < MAX; j++){
            if (T[j] == i){
                flag = 1;
                break;
            }
        }

        if (flag == 0) return i;
    }

    return EMPTY;
}