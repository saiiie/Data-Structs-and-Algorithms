#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int items[MAX];
    int top;
} Stack;

Stack* init();
bool isFull(Stack*);
bool isEmpty(Stack*);
void push(Stack*, int value);
int pop(Stack*);
int peek(Stack*);
int top(Stack*);
void display(Stack*);

int main(){
    Stack* s = init();

    printf("Pushing values 100, 200, 300, 400:\n");
    push(s, 10);
    push(s, 20);
    push(s, 30);
    push(s, 40);
    display(s);

    printf("Peek top element: %d\n", peek(s));
    printf("Current top index: %d\n\n", top(s));

    printf("Popping values:\n");
    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Pop from empty stack: %d\n", pop(s));

    return 0;
}


Stack* init(){
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = MAX;
    return s;
}

bool isFull(Stack* s){
    if (s->top == 0) return true;
    return false;
}

bool isEmpty(Stack* s){
    if (s->top == MAX) return true;
    return false;
}

void push(Stack* s, int value){
    if (isFull(s)){
        printf("Stack is full.\n");
        return;
    }

    s->top--;
    s->items[s->top] = value;
}

int pop(Stack* s){
    if (isEmpty(s)) return -1;

    int value = s->items[s->top];
    s->top++;
    return value;
}

int peek(Stack* s){
    if (isEmpty(s)) return -1;
    return s->items[s->top];
}

int top(Stack* s){
    return s->top;
}

void display(Stack* s){
    if (isEmpty(s)){
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack: ");
    for (int i = s->top; i <= MAX; i++){
        printf("%d ", s->items[i]);
    }

    printf("\n\n");
}