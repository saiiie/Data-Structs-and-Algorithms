#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct{
    int* elemPTR;
    int count;
    int max;
} List;

void initialize(List*);
void insertPos(List*, int, int);
void deletePos(List*, int);
int locate(List*, int);
int retrieve(List*, int);
void insertSorted(List*, int);
void display(List*);
void resize(List*);
void makeNULL(List*);

int main(){
    List *L = (List*)malloc(sizeof(List));
    initialize(L);

    insertPos(L, 2, 0);
    insertPos(L, 1, 0);
    insertPos(L, 4, 2);
    insertPos(L, 5, 3);
    insertPos(L, 7, 4);
    insertPos(L, 7, 4);
    insertPos(L, 8, 6);
    insertPos(L, 9, 7);
    insertPos(L, 8, 7);
    display(L);

    deletePos(L, 5);
    deletePos(L, 7);
    deletePos(L, 7);
    display(L);

    for(int i=0; i<L->max/2; i++){
        int pos = locate(L, i);
        if (pos != -1){
            printf("%d located at position %d.\n", i, pos);
        } else{
            printf("%d not in list!\n", i);
        }
    }
    printf("\n");

    insertSorted(L, 3);
    insertSorted(L, 6);
    insertSorted(L, 9);
    insertSorted(L, 10);
    display(L);

    return 0;
}

void initialize(List* L){
    L->elemPTR = NULL;
    L->count = 0;
    L->max = LENGTH;
}

void insertPos(List* L, int data, int pos){
    if (pos > L->count) return;
    if (L->count == L->max) resize(L);

    for (int i = L->count-1; i >= pos; i--){
        L->elemPTR[i+1] = L->elemPTR[i];
    }

    L->elemPTR[pos] = data;
    L->count++;
    printf("Data %d inserted at position %d.\n", data, pos);
}

void deletePos(List* L, int pos){
    if (pos > L->count) return;

    for (int i=pos; i<L->count; i++){
        L->elemPTR[i] = L->elemPTR[i+1];
    }

    L->count--;
    printf("Data deleted at position %d.\n", pos);
}

int locate(List* L, int data){
    for (int i=0; i<L->count; i++){
        if (L->elemPTR[i] == data){
            return i;
        }
    }
    return -1;
}

int retrieve(List* L, int pos){
    if (pos > L->count) return;
    return L->elemPTR[pos];
}

void insertSorted(List* L, int data){
    if (L->count == L->max) resize(L);

    int pos = 0;
    while (pos < L->count && L->elemPTR[pos] < data) pos++;
    
    insertPos(L, data, pos);
}

void display(List* L){
    printf("Updated List: ");
    for(int i=0; i<L->count;i++){
        printf("%d ", L->elemPTR[i]);
    }
    printf("\n\n");
}

void resize(List* L){
    int newSize = L->max * 2;
    L->elemPTR = (int*)realloc(L->elemPTR, newSize * sizeof(int));
    L->max = newSize;
}

void makeNULL(List* L){
    free(L);
}