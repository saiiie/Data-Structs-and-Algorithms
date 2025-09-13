#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

Stack* initialize();
bool isFull(Stack*);
bool isEmpty(Stack*);
void push(Stack*, int);
int pop(Stack*);
int peek(Stack*);
void display(Stack*);

int main() {
    Stack* s = initialize();

    printf("=== Pushing elements ===\n");
    for (int i = 1; i <= 5; i++) {
        push(s, i * 10);
        display(s);
    }

    printf("\n=== Peek top element ===\n");
    printf("Top: %d\n", peek(s));

    printf("\n=== Pop two elements ===\n");
    printf("Popped: %d\n", pop(s));
    printf("Popped: %d\n", pop(s));
    display(s);

    printf("\n=== Push more elements ===\n");
    push(s, 60);
    push(s, 70);
    display(s);

    printf("\n=== Pop everything ===\n");
    while (!isEmpty(s)) {
        printf("Popped: %d\n", pop(s));
        display(s);
    }

    free(s);
    return 0;
}


Stack* initialize(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool isFull(Stack* s){
    return false;
}

bool isEmpty(Stack* s){
    if (s->top == NULL) return true;
    return false;
}

void push(Stack* s, int value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = s->top;
    s->top = node;
}

int pop(Stack* s){
    if (isEmpty(s)) return -1;

    Node* temp = s->top;
    int data = temp->data;
    s->top = temp->next;
    free(temp);
    return data;
}
int peek(Stack* s){
    if (isEmpty(s)) return -1;
    return s->top->data;
}

void display(Stack* s){
    if (isEmpty(s)){
        printf("Stack is empty.\n");
        return;
    }

    Node* temp = s->top;
    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}