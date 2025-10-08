#include <stdio.h>
#include <stdbool.h>

void initialize(unsigned char* set){
    *set = 0;
}

void insert(unsigned char* set, int elem){
    if (elem < 0 || elem > 7) return;
    unsigned char bit_mask = (1 << elem);
    *set |= bit_mask;
}

void delete(unsigned char* set, int elem){
    if (elem < 0 || elem > 7) return;
    unsigned char bit_mask = (1 << elem);
    *set &= ~bit_mask;
}

bool find(unsigned char* set, int elem){
    bool found = false;
    if (*set & (1 << elem)) found = true;
    return found;
}

unsigned char unite(unsigned char A, unsigned char B){
    unsigned char set = A | B;
    return set;
}

unsigned char intersection(unsigned char A, unsigned char B){
    unsigned char set = A & B;
    return set;
}

unsigned char difference(unsigned char A, unsigned char B){
    unsigned char set = A & (~B);
    return set;
}

void display(unsigned char set){
    int bits = 8 * sizeof(set);
    bool first = true;

    printf("{ ");
    for (int i = 0; i < bits; i++){
        bool isSet = find(set, i);

        if (isSet){
            if (!first) printf(", ");

            printf("%d", i);
            first = false;
        }
    }
    printf(" }\n");
}

int main(){
    unsigned char A, B, C;
    initialize(&A);
    initialize(&B);

    insert(&A, 1);
    insert(&A, 6);

    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 7);

    printf("Set A: ");
    display(A);
    printf("Set B: ");
    display(B);

    C = unite(A, B);
    printf("Union: ");
    display(C);

    C = intersection(A, B);
    printf("Intersection: ");
    display(C);

    C = difference(A, B);
    printf("Difference: ");
    display(C);

    return 0;
}