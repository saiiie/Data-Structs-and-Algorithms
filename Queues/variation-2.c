// ARRAY Queues Variation 2
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 5

// struct for queue, no count variable
typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// initialize queue
Queue* init() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    
    // initialize front to 1, skipping index 0 for sacrificial space
    q->front = 1;
    
    // initialize rear to 0, so that rear can increment correctly
    q->rear = 0;
    
    return q;
}

bool isEmpty(Queue* q) {
    // queue is empty if the front is one index 'ahead' of rear
    return (q->front == (q->rear + 1) % MAX);
}

bool isFull(Queue* q) {
    // queue is full if the front is two indices 'ahead' of rear
    return (q->front == (q->rear + 2) % MAX);
}

void enqueue(Queue* q, int value) {
    if (isFull(q)){
        printf("Queue is full.\n");
        return;
    }
    
    // move rear to next index ahead  
    q->rear = (q->rear + 1) % MAX;
    
    // place value at rear
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    
    // store number at the front of the queue
    int ret = q->items[q->front];
    
    // move front to next index ahead
    q->front = (q->front + 1) % MAX;
    
    return ret;
}

int front(Queue* q) {
    if (isEmpty(q)) return -1;
    return q->items[q->front];
}

void display(Queue* q) {
    if (isEmpty(q)){
        printf("Queue is empty.\n");
        return;
    }
    
    // calculate current count of elements
    int count = (q->rear - q->front + MAX) % MAX;
    
    // same display method for variation 1
    printf("Queue: ");
    for (int i = 0; i < count; i++){
        int temp = dequeue(q);
        printf("%d ", temp);
        enqueue(q, temp);
    }
    
    printf("\n");
}

int main() {
    Queue* q = init();
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);

    display(q);  // Expected: 10 20 30 40

    printf("Dequeued: %d\n", dequeue(q)); // Expected: 10
    printf("Dequeued: %d\n", dequeue(q)); // Expected: 20

    display(q);  // Expected: 30 40

    enqueue(q, 50);
    enqueue(q, 60);  // should wrap around

    display(q);  // Expected: 30 40 50 60

    printf("Front element: %d\n", front(q)); // Expected: 30

    while (!isEmpty(q)) {
        printf("Dequeued: %d\n", dequeue(q));
    }

    display(q);  // Expected: Queue is empty.
    
    return 0;
}