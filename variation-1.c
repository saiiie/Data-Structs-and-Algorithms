#include <stdio.h>
#include <stdlib.h>

#define size 10

typedef struct{
    int elem[size];
    int count;
} List;

List initialize(List);
List insertPos(List, int, int);
List deletePos(List, int);
int locate(List, int);
List insertSorted(List, int);
void displayList(List);

int main(){
    List L = initialize(L);
    L.count = 0;
    
    L = insertPos(L, 3, 1);
    L = insertPos(L, 4, 2);
    L = insertPos(L, 6, 4);
    L = insertPos(L, 7, 5);
    L = insertPos(L, 9, 8);
    L = insertPos(L, 10, 9);

    displayList(L);
    return 0;
}

List initialize(List L){
    for (int i=0; i<size; i++){
        L.elem[i] = -1;
    }
    return L;
}

List insertPos(List L, int data, int pos){
    if (pos < 0 || pos > size){
        printf("Invalid position!\n");
        return L;
    }

    if (L.count == size-1){
        printf("List if full!\n");
        return L;
    }

    if (L.elem[pos] == -1) L.count++;
    L.elem[pos] = data;
    return L;    
}

List deletePos(List L, int pos){
    if (pos < 0 || pos > size){
        printf("Invalid position!\n");
        return L;
    }

    if (L.count == 0){
        printf("List is empty!\n");
        return L; 
    }

    if (L.elem[pos] == -1){
        printf("Position already empty!\n");
        return L;
    }

    L.elem[pos] = -1;
    L.count--;
    return L; 
}

int locate(List L, int data){
    if (L.count == 0){
        printf("List is empty!\n");
        return -1; 
    }

    for(int i=0; i<size; i++){
        if (L.elem[i] == data){
            return i;
        }
    }

    printf("Data not present!\n");
    return -1;
}

List insertSorted(List L, int data){
    if (L.count == size-1){
        printf("List is full!\n");
        return L;
    }

    if (L.elem[0] >= data){
        for (int i=L.count; i>0; i--){
            
        }
    }
}

void displayList(List L){
    for(int i=0; i<L.count;i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}