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
    int pos, i;
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
    displayList(L);

    L = deletePos(L, 5);
    L = deletePos(L, 7);
    L = deletePos(L, 7);
    displayList(L);

    for(i=0; i<size/2; i++){
        pos = locate(L, i);
        if (pos != -1){
            printf("%d located at position %d.\n", i, pos);
        } else{
            printf("%d not in list!\n", i);
        }
    }

    L = insertSorted(L, 3);
    L = insertSorted(L, 6);
    L = insertSorted(L, 9);
    L = insertSorted(L, 10);
    displayList(L);

    return 0;
}

List initialize(List L){
    L.count = 0;
    return L;
}

List insertPos(List L, int data, int pos){
    if (L.count == size){
        printf("List is full!\n");
        return L;
    }

    if (pos > L.count || pos < 0){
        printf("Cannot insert! Valid positions 0-%d only.\n", L.count);
        return L;
    }

    int i;
    for (i = L.count-1; i >= pos; i--){
        L.elem[i+1] = L.elem[i];
    }
        
    L.elem[pos] = data;
    L.count++;
    printf("Data %d inserted at position %d.\n", data, pos);
    return L;
}

List deletePos(List L, int pos){
    if (pos > L.count || pos < 0){
        printf("Cannot delete! Valid positions 0-%d only.\n", L.count);
        return L;
    }

    for (int i=pos; i<L.count; i++){
        L.elem[i] = L.elem[i+1];
    }

    L.count--;
    printf("Data deleted at position %d.\n", pos);
    return L;
}

int locate(List L, int data){
    for (int i=0; i<L.count; i++){
        if (L.elem[i] == data){
            return i;
        }
    }

    return -1;
}

List insertSorted(List L, int data){
    if (L.count == size){
        printf("List is full!\n");
        return L;
    }

    int pos = 0;
    while (pos < L.count && L.elem[pos] < data) pos++;
    for (int j = L.count - 1; j >= pos; j--) L.elem[j+1] = L.elem[j];
    
    L.elem[pos] = data;
    L.count++;
    printf("Inserted %d at position %d.\n", data, pos);
    return L;
}

void displayList(List L){
    printf("\nUpdated List: ");
    for(int i=0; i<L.count;i++){
        printf("%d ", L.elem[i]);
    }
    printf("\n\n");
}