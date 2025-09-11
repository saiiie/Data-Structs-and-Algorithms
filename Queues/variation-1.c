#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int items[MAX];
    int count;
} List;

typedef struct{
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
bool isFull(Queue*);
bool isEmpty(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);
int front(Queue*);
void display(Queue*);

int main(){
    Queue* q = initialize();

    printf("=== Enqueueing elements ===\n");
    for (int i = 1; i <= 5; i++) {
        enqueue(q, i * 10);
        display(q);
    }

    printf("\n=== Dequeueing two elements ===\n");
    printf("Dequeued: %d\n", dequeue(q));
    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    printf("\n=== Test Wraparound ===\n");
    enqueue(q, 60);
    enqueue(q, 70);
    display(q);

    printf("\n=== Peek front element ===\n");
    printf("Front: %d\n", front(q));

    printf("\n=== Dequeueing all elements ===\n");
    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
        display(q);
    }

    printf("\nFinal state:\n");
    display(q);

    free(q); // cleanup
    return 0;
}

Queue* initialize(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    q->list.count = 0;
    return q;
}

bool isFull(Queue* q){
    if (q->list.count == MAX) return true;
    return false;
}

bool isEmpty(Queue* q){
    if (q->list.count == 0) return true;
    return false;
}

void enqueue(Queue* q, int value){
    if (isFull(q)){
        printf("Queue is full.\n");
        return;
    }

    if (isEmpty(q)){
        q->front = q->rear = 0;
    } else{
        q->rear = (q->rear + 1) % MAX;
    }

    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q){
    if (isEmpty(q)) return -1;

    int value = q->list.items[q->front];
    if (q->list.count == 1){
        q->front = q->rear = 0;
    } else{
        q->front = (q->front + 1) % MAX;
    }

    q->list.count--;
    return value;
}

int front(Queue* q){
    if (isEmpty(q)) return -1;
    return q->list.items[q->front];
}

void display(Queue* q){
    if (isEmpty(q)){
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue: ");
    for (int c = 0, index = q->front; c < q->list.count; index = (index + 1) % MAX, c++){
        printf("%d ", q->list.items[index]);
    }

    printf("\n");
}