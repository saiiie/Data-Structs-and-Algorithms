#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct Eptr{
    int elem[MAX];
    int count;
} *Eptr;

void initialize(Eptr);
void insertPos(Eptr, int, int);
void deletePos(Eptr, int);
int locate(Eptr, int);
int retrieve(Eptr, int);
void insertSorted(Eptr, int);
void displayList(Eptr);
void makeNULL(Eptr*);

int main(){
    int pos, elem, i;
    Eptr L = malloc(MAXof(*L));
    initialize(L);

    printf("%d", L->count);

    insertPos(L, 2, 0);
    insertPos(L, 1, 0);
    insertPos(L, 4, 2);
    insertPos(L, 5, 3);
    insertPos(L, 7, 4);
    insertPos(L, 7, 4);
    insertPos(L, 8, 6);
    insertPos(L, 9, 7);
    insertPos(L, 8, 7);
    displayList(L);

    deletePos(L, 5);
    deletePos(L, 7);
    deletePos(L, 7);
    displayList(L);

    printf("LOCATING BY POSITION:\n");
    for(i=0; i<MAX/2; i++){
        pos = locate(L, i);
        if (pos != -1){
            printf("%d located at position %d.\n", i, pos);
        } else{
            printf("%d not in list!\n", i);
        }
    }

    printf("\nLOCATING BY DATA:\n");
    for(int i=0; i<MAX/2; i++){
        elem = retrieve(L, i);
        if (elem != -1){
            printf("%d located at position %d.\n", elem, i);
        } else{
            printf("%d not in list!\n", elem);
        }
    }

    insertSorted(L, 3);
    insertSorted(L, 6);
    insertSorted(L, 9);
    insertSorted(L, 10);
    displayList(L);

    makeNULL(&L);
    if (L == NULL) printf("Memory freed!\n");
    return 0;
}

void initialize(Eptr L){
    L->count = 0;
}

void insertPos(Eptr L, int data, int pos){
    if (L->count == MAX){
        printf("List is full!\n");
        return;
    }

    if (pos > L->count || pos < 0){
        printf("Cannot insert! Valid positions 0-%d only.\n", L->count);
        return;
    }

    int i;
    for (i = L->count-1; i >= pos; i--){
        L->elem[i+1] = L->elem[i];
    }
        
    L->elem[pos] = data;
    L->count++;
    printf("Data %d inserted at position %d.\n", data, pos);
}

void deletePos(Eptr L, int pos){
    if (pos >= L->count || pos < 0){
        printf("Cannot delete! Valid positions 0-%d only.\n", L->count);
        return;
    }

    for (int i=pos; i<L->count; i++){
        L->elem[i] = L->elem[i+1];
    }

    L->count--;
    printf("Data deleted at position %d.\n", pos);
}

int locate(Eptr L, int data){
    for (int i=0; i<L->count; i++){
        if (L->elem[i] == data){
            return i;
        }
    }

    return -1;
}

int retrieve(Eptr L, int pos){
    if (pos >= L->count || pos < 0){
        printf("Valid positions 0-%d only!", L->count);
        return -1;
    }

    return L->elem[pos];
}

void insertSorted(Eptr L, int data){
    if (L->count == MAX){
        printf("List is full!\n");
        return;
    }

    int pos = 0;
    while (pos < L->count && L->elem[pos] < data) pos++;
    for (int j = L->count - 1; j >= pos; j--) L->elem[j+1] = L->elem[j];
    
    L->elem[pos] = data;
    L->count++;
    printf("Inserted %d at position %d.\n", data, pos);
}

void displayList(Eptr L){
    printf("\nUpdated List: ");
    for(int i=0; i<L->count;i++){
        printf("%d ", L->elem[i]);
    }
    printf("\n\n");
}

void makeNULL(Eptr *L){
    free(*L);
    *L = NULL;
}