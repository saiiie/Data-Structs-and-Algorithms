// ARRAY Queues Variation 1
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 5

// separate struct for List
typedef struct {
    int items[MAX];
    int count;
} List;

// struct for Queue
typedef struct {
    List list;
    int front;
    int rear;
} Queue;

// initialize the queue
Queue* init() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = -1;
    q->list.count = 0;
    return q;
}

bool isEmpty(Queue* q) {
    return (q->list.count == 0);
}

bool isFull(Queue* q) {
    return (q->list.count == MAX);
}

void enqueue(Queue* q, int value) {
    if (isFull(q)){
        printf("Queue is full.\n");
        return;
    }
    
    
    if (isEmpty(q)) {
        // handles case for empty queue, so front gets updated correctly
        q->front = 0;
        q->rear = 0;
    } else {
        // else, increment rear to next index
        q->rear = (q->rear + 1) % MAX;
    }
    
    // assignment of value to rear index 
    q->list.items[q->rear] = value;
    q->list.count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    
    // stores number to be dequeued
    int ret = q->list.items[q->front];
    
    if (q->front == q->rear) {
        // handles case for when queue has only one element left, so queue can reset correctly
        q->front = q->rear = -1;
    } else {
        // else, increment front to the next index
        q->front = (q->front + 1) % MAX;
    }
    
    // decrement count and return stored number
    q->list.count--;
    return ret;
}

int front(Queue* q) {
    if (isEmpty(q)) return -1;
    return q->list.items[q->front];
}

// display queue with NO accessing of index
void display(Queue* q) {
    if (isEmpty(q)){
        printf("Queue is empty.\n");
        return;
    }
    
    printf("Queue: ");
    // dequeues to display and enqueues to restore until count has been met
    for (int i = 0; i < q->list.count; i++){
        int temp = dequeue(q);
        printf("%d ", temp);
        enqueue(q, temp);
    }
    
    printf("\n\n");
}

int main(){
    Queue* q = init();
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);
    
    display(q);  // Expected: 10 20 30 40 50

    printf("Dequeued: %d\n", dequeue(q)); // Expected: 10
    printf("Dequeued: %d\n", dequeue(q)); // Expected: 20
    
    display(q);  // Expected: 30 40 50

    enqueue(q, 60);
    enqueue(q, 70);  // should wrap around
    
    display(q);  // Expected: 30 40 50 60 70
    
    printf("Front element: %d\n", front(q)); // Expected: 30

    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
    }
    
    display(q);  // Expected: Queue is empty.
    
    return 0;
}