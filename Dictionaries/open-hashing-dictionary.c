#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[SIZE];
} Dictionary;

void initialize(Dictionary* d){
    for (int i = 0; i < SIZE; i++) d->buckets[i] = NULL;
}

int hash(int key){
    return key % SIZE;
}

Node* createNode(int key, int value){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = NULL;
    
    return node;
}

void insert(Dictionary* d, int key, int value){
    int loc = hash(key);

    Node* node = createNode(key, value);
    node->next = d->buckets[loc];
    d->buckets[loc] = node;
}

bool member(Dictionary* d, int key, int* value){
    int loc = hash(key);

    Node* temp = d->buckets[loc];
    while (temp != NULL){
        if (temp->key == key){
            *value = temp->value;
            return true;
        }
        temp = temp->next;
    }

    return false;
}

void delete(Dictionary* d, int key){
    int loc = hash(key);

    Node* curr = d->buckets[loc];
    Node* prev = NULL;
    while (curr != NULL){
        if (curr->key == key){
            if (prev == NULL){
                d->buckets[loc] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

void display(Dictionary* d){
    for (int i = 0; i < SIZE; i++){
        bool first = true;
        Node* temp = d->buckets[i];
        printf("Bucket %d: ", i);

        if (temp == NULL){
            printf("EMPTY\n");
            continue;
        }

        while (temp != NULL){
            if (!first) printf(" -> ");
            printf("(%d, %d)", temp->key, temp->value);
            first = false;
            temp = temp->next;
        }

        printf("\n");
    }
}

int main() {
    Dictionary d;
    initialize(&d);

    // Insert a bunch of key-value pairs
    insert(&d, 10, 100);
    insert(&d, 20, 200);
    insert(&d, 30, 300);
    insert(&d, 40, 400);
    insert(&d, 50, 500);
    insert(&d, 25, 250);
    insert(&d, 35, 350);
    insert(&d, 45, 450);
    insert(&d, 15, 150);
    insert(&d, 7, 700);
    insert(&d, 17, 170);
    insert(&d, 27, 270);

    printf("=== Initial Dictionary ===\n");
    display(&d);
    printf("\n");

    // Search for a few keys
    int val;
    if (member(&d, 25, &val))
        printf("Key 25 found with value: %d\n", val);
    else
        printf("Key 25 not found\n");

    if (member(&d, 11, &val))
        printf("Key 11 found with value: %d\n", val);
    else
        printf("Key 11 not found\n");

    printf("\nDeleting Multiple Keys...\n");
    delete(&d, 10);  // first element in bucket
    delete(&d, 27);  // middle element in bucket
    delete(&d, 45);  // last element in bucket
    delete(&d, 99);  // non-existent key

    printf("\n=== After Multiple Deletions ===\n");
    display(&d);
    
    return 0;
}