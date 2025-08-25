#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct{
    int* elemPTR;
    int count;
    int max;
} List;

List initialize(List);
List insertPos(List, int, int);
List deletePos(List, int);
int locate(List, int);
List insertSorted(List, int);
void display(List);
List resize(List);

int main(){
    List L = initialize(L);

    L = insertPos(L, 2, 0);
    L = insertPos(L, 1, 0);
    L = insertPos(L, 4, 2);
    L = insertPos(L, 5, 3);
    L = insertPos(L, 7, 4);
    L = insertPos(L, 7, 4);
    L = insertPos(L, 8, 6);
    L = insertPos(L, 9, 7);
    L = insertPos(L, 8, 7);
    display(L);

    L = deletePos(L, 5);
    L = deletePos(L, 7);
    L = deletePos(L, 7);
    display(L);

    for(int i=0; i<L.max/2; i++){
        int pos = locate(L, i);
        if (pos != -1){
            printf("%d located at position %d.\n", i, pos);
        } else{
            printf("%d not in list!\n", i);
        }
    }
    printf("\n");

    L = insertSorted(L, 3);
    L = insertSorted(L, 6);
    L = insertSorted(L, 9);
    L = insertSorted(L, 10);
    display(L);

    return 0;
}

List initialize(List L){
    L.elemPTR = (int*)malloc(sizeof(int) * LENGTH);
    L.count = 0;
    L.max = LENGTH;
    return L;
}

List insertPos(List L, int data, int pos){
    if (L.count == L.max){
        L = resize(L);
    } else if (pos < 0 || pos > L.count){
        printf("Valid positions 0-%d only.\n", L.count - 1);
        return L;
    }

    for (int i = L.count-1; i >= pos; i--){
        L.elemPTR[i+1] = L.elemPTR[i];
    }
    
    L.elemPTR[pos] = data;
    L.count++;
    printf("Data %d inserted at position %d.\n", data, pos);
    return L;
}

List deletePos(List L, int pos){
    if (pos >= L.count || pos < 0){
        printf("Cannot delete! Valid positions 0-%d only.\n", L.count);
        return L;
    }

    for (int i=pos; i<L.count; i++){
        L.elemPTR[i] = L.elemPTR[i+1];
    }

    L.count--;
    printf("Data deleted at position %d.\n", pos);
    return L;
}

int locate(List L, int data){
    for (int i=0; i<L.count; i++){
        if (L.elemPTR[i] == data){
            return i;
        }
    }

    return -1;
}

List insertSorted(List L, int data){
    if (L.count == L.max) L = resize(L);

    int pos = 0;
    while (pos < L.count && L.elemPTR[pos] < data) pos++;
    
    L = insertPos(L, data, pos);
    return L;
}

void display(List L){
    printf("Updated List: ");
    for(int i=0; i<L.count;i++){
        printf("%d ", L.elemPTR[i]);
    }
    printf("\n\n");
}

List resize(List L){
    int newSize = L.max * 2;
    L.elemPTR = (int*)realloc(L.elemPTR, newSize * sizeof(int));
    L.max = newSize;

    if (L.elemPTR != NULL) printf("Memory reallocation successful!\n");
    return L;
}