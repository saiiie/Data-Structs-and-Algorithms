#include <stdio.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V){
    V->avail = 0;

    for (int i = 0; i < MAX - 1; i++){
        V->H[i].next = i + 1;
    }

    V->H[MAX-1].next = -1;
}

int allocSpace(VHeap* V){
    int cell = V->avail;

    if (cell == -1) return -1;
    
    V->avail = V->H[V->avail].next;
    return cell;
}

void deallocSpace(VHeap* V, int index){
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(int* L, VHeap* V, int elem){
    int cell = allocSpace(V);

    if (cell == -1) return;

    V->H[cell].elem = elem;
    V->H[cell].next = *L;
    *L = cell;
}

void insertLast(int* L, VHeap* V, int elem){
    int cell = allocSpace(V);

    if (cell == -1) return;

    V->H[cell].elem = elem;
    V->H[cell].next = -1;

    if (*L == -1){
        *L = cell;
        return;
    }

    int trav = *L;
    while (V->H[trav].next != -1) trav = V->H[trav].next;
    V->H[trav].next = cell;
}

void insertPos(int* L, VHeap* V, int elem, int pos){
    int cell = allocSpace(V);

    if (cell == -1) return;

    if (pos == 0){
        insertFirst(L, V, elem);
        return;
    }

    int trav = *L;
    int count = 0;
    while (count < pos - 1 && V->H[trav].next != -1){
        trav = V->H[trav].next;
        count++;
    }

    if (V->H[trav].next == -1){
        insertLast(L, V, elem);
        return;
    }

    V->H[cell].next = V->H[trav].next;
    V->H[trav].next = cell;
}

void insertSorted(int* L, VHeap* V, int elem){
    // AYAW KO MUNA NETO LATER NA 
}

void deleteElem(int* L, VHeap* V, int elem){
    int trav = *L;
    int prev;

    if (V->H[trav].elem == elem){
        *L = V->H[trav].next;
        deallocSpace(V, trav);
        return;
    }

    while (trav != -1 && V->H[trav].elem != elem){
        prev = trav;
        trav = V->H[trav].next;
    }

    if (trav == -1) return;

    V->H[prev].next = V->H[trav].next;
    deallocSpace(V, trav);
}

void deleteAllOccurrence(int* L, VHeap* V, int elem){
    // LATER NADEN ITO
}

void display(int L, VHeap V){
    int i = L;

    while (i != -1){
        printf("%d ", V.H[i].elem);
        i = V.H[i].next;
    }

    printf("\n");
}

int main() {
    VHeap VH;
    List L = -1; // Empty list

    initialize(&VH);

    insertFirst(&L, &VH, 10);
    insertFirst(&L, &VH, 20);
    insertLast(&L, &VH, 30);
    insertPos(&L, &VH, 25, 1);

    printf("List after insertions: ");
    display(L, VH);

    deleteElem(&L, &VH, 20);
    printf("List after deleting 20: ");
    display(L, VH);

    insertLast(&L, &VH, 40);
    insertLast(&L, &VH, 50);
    printf("List after adding 40 and 50: ");
    display(L, VH);

    deleteElem(&L, &VH, 100); // test deleting non-existent value
    printf("Attemp to delete non-existent: ");
    display(L, VH);

    return 0;
}