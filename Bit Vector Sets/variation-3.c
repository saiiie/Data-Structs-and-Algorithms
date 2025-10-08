#include <stdio.h>
#include <stdbool.h>

#define ARRAY_SIZE 8

typedef bool Set[ARRAY_SIZE];

void initialize(Set set){
    for (int i = 0; i < ARRAY_SIZE; i++){
        set[i] = 0;
    }
}

void insert(Set set, int elem){
    if (elem < 0 || elem >= ARRAY_SIZE) return;
    set[elem] = 1;
}

void delete(Set set, int elem){
    if (elem < 0 || elem >= ARRAY_SIZE) return;
    set[elem] = 0;
}

bool find(Set set, int elem){
    if (elem < 0 || elem >= ARRAY_SIZE) return 0;

    bool found = 0;
    if (set[elem] == 1) found = 1;
    return found;
}

void unite(Set A, Set B, Set C){
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (A[i] == 1 || B[i] == 1){
            C[i] = 1;
        } else{
            C[i] = 0;
        }
    }
}

void intersection(Set A, Set B, Set C){
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (A[i] == 1 && B[i] == 1){
            C[i] = 1;
        } else{
            C[i] = 0;
        }
    }
}

void difference(Set A, Set B, Set C){
    for (int i = 0; i < ARRAY_SIZE; i++){
        C[i] = (A[i] == 1 && B[i] == 0);
    }
}

void display(Set set){
    bool first = true;

    printf("{");
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (!first) printf(", ");
        printf("%d", i);
        first = false;
    }
    printf("}\n");
}

int main() {
    Set A, B, C;

    initialize(A);
    initialize(B);

    insert(A, 1);
    insert(A, 3);
    insert(B, 2);
    insert(B, 3);

    printf("Set A: ");
    display(A);

    printf("Set B: ");
    display(B);

    unite(A, B, C);
    printf("A ∪ B: ");
    display(C);

    intersection(A, B, C);
    printf("A ∩ B: ");
    display(C);

    difference(A, B, C);
    printf("A - B: ");
    display(C);

    printf("Is 3 in A? %s\n", find(A, 3) ? "Yes" : "No");
    printf("Is 2 in A? %s\n", find(A, 2) ? "Yes" : "No");

    delete(A, 3);
    printf("After deleting 3, A: ");
    display(A);

    return 0;
}
