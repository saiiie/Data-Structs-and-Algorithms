#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    
    return 0;
}

Queue* initialize(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isFull(Queue* q){
    return false;
}

bool isEmpty(Queue* q){
    if (q->front == NULL) return true;
    return false;
}

void enqueue(Queue* q, int value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;

    if (isEmpty(q)){
        q->front = node;
        q->rear = node;
    } else {
        node->next = q->rear;
        q->rear = node;
    }
}

int dequeue(Queue* q){
    if (isEmpty(q)) return -1;

    Node* temp = q->rear;
    int value = temp->data;
    q->rear = temp->next;
    free(temp);
    return value;
}

int front(Queue* q){
    if (isEmpty(q)) return -1;
}

void display(Queue* q){
    
}