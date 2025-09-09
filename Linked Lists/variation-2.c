#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} Node;

typedef struct{
    Node* head;
    int count;
} List;

List* initialize();
void empty(List*);
void insertFirst(List*, int);
void insertLast(List*, int);
void insertPos(List*, int, int);
void deleteStart(List*);
void deleteLast(List*);
void deletePos(List*, int);
int retrieve(List*, int);
int locate(List*, int);
void display(List*);

int main(){
    List* L = initialize();

    insertFirst(L, 2);
    insertFirst(L, 1);
    insertFirst(L, 0);
    insertLast(L, 8);
    insertLast(L, 9);
    insertPos(L, 3, 3);
    insertPos(L, 4, 4);
    insertPos(L, 5, 5);
    display(L);

    deletePos(L, 0);
    deleteStart(L);
    deleteLast(L);
    display(L);

    int data = retrieve(L, 4);
    if (data != -1){
        printf("Retrieved data %d.\n", data);
    } else{
        printf("Invalid position.\n");
    }

    int pos = locate(L, 4);
    if (pos != -1){
        printf("Located at index %d.\n", pos);
    } else{
        printf("Data does not exist.\n");
    }

    return 0;
}

List* initialize(){
    List* L = (List*)malloc(sizeof(List));

    if (L == NULL){
        printf("Memory allocation unsuccessful.\n");
        return NULL;
    }

    L->head = NULL;
    L->count = 0;
    return L;
}

void empty(List* L){
    while(L->head != NULL){
        Node* curr = L->head;
        L->head = L->head->next;
        free(curr);
    }
    L->head = NULL;
    L->count = 0;
}

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertFirst(List* L, int data){
    Node* node = createNode(data);
    node->next = L->head;
    L->head = node;
    L->count++;
}

void insertLast(List* L, int data){
    Node* node = createNode(data);
    Node* curr = L->head;
    for(int i = 0; i < L->count - 1 ; curr = curr->next, i++);
    curr->next = node;
    L->count++;
}

void insertPos(List* L, int data, int pos){
    if (pos > L->count || pos < 0){
        printf("Invalid position.\n");
        return;
    }

    if (pos == 0){
        insertFirst(L, data);
        return;
    } else if (pos == L->count){
        insertLast(L, data);
        return;
    }

    Node* node = createNode(data);

    Node* curr = L->head;
    for(int i = 0; i < pos - 1; curr = curr->next, i++);
    node->next = curr->next;
    curr->next = node;
    L->count++;
}

void deleteStart(List* L){
    Node* temp = L->head;
    L->head = temp->next;
    free(temp);
    L->count--;
}

void deleteLast(List* L){
    if (L->count == 1){
        deleteStart(L);
        return;
    }

    Node* curr = L->head;
    for(int i=0; i < L->count - 2; curr = curr->next, i++);
    Node* temp = curr->next;
    curr->next = NULL;
    free(temp);
    L->count--;
}

void deletePos(List* L, int pos){
    if (pos > L->count || pos < 0){
        printf("Invalid position.\n");
        return;
    }

    Node* curr = L->head;
    for(int i=1; i < pos; curr = curr->next, i++);
    Node* temp = curr->next;
    curr->next = temp->next;
    free(temp);
    L->count--;
}

int retrieve(List* L, int pos){
    if (pos >= L->count || pos < 0){
        return -1;
    }

    Node* curr = L->head;
    for(int i=0; i < pos; curr = curr->next, i++);
    return curr->data;
}

int locate(List* L, int data){
    if (L->head == NULL) return -1;

    Node* curr = L->head;
    for (int i = 0; i < L->count; curr = curr->next, i++){
        if (curr->data == data) return i;
    }
    return -1;
}

void display(List* L){
    Node* curr = L->head;
    printf("List: ");
    for(int i = 0; i < L->count; i++){
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}