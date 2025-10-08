#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned int field : 8;
} Set;

void initialize(Set* set){
    set->field = 0;
}

void insert(Set *set, int elem){
    if (elem < 0 || elem > 7) return;
    unsigned char bit_mask = (1 << elem);
    set->field |= bit_mask;
}

void delete(Set *set, int elem){
    if (elem < 0 || elem > 7) return;
    unsigned char bit_mask = (1 << elem);
    set->field &= ~bit_mask;
}

bool find(Set set, int elem){
    bool found = false;
    if (set.field & (1 << elem)) found = true;
    return found;
}

Set unite(Set A, Set B){
    Set C;
    C.field = A.field | B.field;
    return C;
}

Set intersection(Set A, Set B){
    Set C;
    C.field = A.field & B.field;
    return C;
}

Set difference(Set A, Set B){
    Set C;
    C.field = A.field & ~B.field;
    return C;
}

void display(unsigned char set){
    int bits = 8 * sizeof(set);
    bool first = true;

    for (int i = 0; i < bits; i++){
        unsigned char bit_mask = (1 << i);

        if (set & bit_mask){
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }

    }
}

int main() {
    Set A, B, C;

    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 3);
    insert(&B, 2);
    insert(&B, 3);

    printf("Set A: { ");
    display(A.field);
    printf(" }\n");

    printf("Set B: { ");
    display(B.field);
    printf(" }\n");

    C = unite(A, B);
    printf("A ∪ B: { ");
    display(C.field);
    printf(" }\n");

    C = intersection(A, B);
    printf("A ∩ B: { ");
    display(C.field);
    printf(" }\n");

    C = difference(A, B);
    printf("A - B: { ");
    display(C.field);
    printf(" }\n");

    printf("Is 3 in A? %s\n", find(A, 3) ? "Yes" : "No");
    printf("Is 2 in A? %s\n", find(A, 2) ? "Yes" : "No");

    delete(&A, 3);
    printf("After deleting 3, A: { ");
    display(A.field);
    printf(" }\n");

    return 0;
}