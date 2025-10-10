#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// CHAINING :0 WOWOWOW
typedef struct Node{
    int key;
    struct Node* next;
} Node;

typedef struct{
    Node* table[TABLE_SIZE];
} HashTable;

void initialize(HashTable* ht){
    for (int i = 0; i < TABLE_SIZE; i++){
        ht->table[i] = NULL;
    }
}

int hash(int key){
    return key % TABLE_SIZE;
}

void insert(HashTable* ht, int key){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->next = NULL;

    int loc = hash(key);
    if (ht->table[loc] == NULL){
        ht->table[loc] = node;
    } else {
        Node* temp = ht->table[loc];
        
        while (temp->next != NULL){
            if (temp->key == key) return;
            temp = temp->next;
        }

        if (temp->key == key) return;
        temp->next = node;
    }
}

bool member(HashTable* ht, int key) {
    int loc = hash(key);
    Node* temp = ht->table[loc];

    while (temp != NULL) {
        if (temp->key == key)
            return true;
        temp = temp->next;
    }

    return false;
}

void delete(HashTable* ht, int key){
    int loc = hash(key);
    Node* temp = ht->table[loc];

    if (temp == NULL) return;

    if (temp->key == key){
        ht->table[loc] = temp->next;
        free(temp);
        return;
    }

    while (temp->next != NULL){
        if (temp->next->key == key){
            Node* toDelete = temp->next;
            temp->next = toDelete->next;
            free(toDelete);
        }
        temp = temp->next;
    }
}

void display(HashTable* ht){
    for (int i = 0; i < TABLE_SIZE; i++){
        printf("loc %d: ", i);
        Node* temp = ht->table[i];
        bool first = true;
        
        if (temp == NULL) continue;

        while (temp != NULL){
            if (!first) printf(" -> ");
            printf("%d", temp->key);
            temp = temp->next;
        }

        printf("\n");
    }
}

int main() {
    HashTable ht;
    initialize(&ht);

    insert(&ht, 15);
    insert(&ht, 25);
    insert(&ht, 35);
    insert(&ht, 5);
    insert(&ht, 42);
    insert(&ht, 7);
    insert(&ht, 17);

    printf("Hash Table after insertion:\n");
    display(&ht);

    printf("\n\nSearching for 25: %s\n", member(&ht, 25) ? "Found" : "Not Found");
    printf("Searching for 99: %s\n", member(&ht, 99) ? "Found" : "Not Found");

    delete(&ht, 25);
    delete(&ht, 99);

    printf("\nHash Table after deleting 25:\n");
    display(&ht);

    return 0;
}
