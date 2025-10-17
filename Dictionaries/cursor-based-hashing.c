#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 10
#define MAX 20

typedef struct {
    char code[4];
    char city[20];
    int next;
} Node;

typedef struct {
    Node data[MAX];
    int avail;
} Dictionary;

void initDictionary(Dictionary* D){
    D->avail = SIZE;
    for (int i = 0; i < MAX; i++){
        
        if (i >= SIZE){
            if (i == MAX - 1){
                D->data[i].next = -1;
            }
            D->data[i].next = i + 1;
        }
        else {
            D->data[i].next = -1;
        }
        
        D->data[i].code[0] = '\0';
    }
}

int hash(char code[]){
    return ((code[0]-'A')*26*26 + (code[1]-'A')*26 + (code[2]-'A')) % SIZE;
}

bool insert(Dictionary* D, char code[], char city[]){
    int loc = hash(code);

    // case for when primary slot is empty
    if (D->data[loc].code[0] == '\0'){
        strcpy(D->data[loc].city, city);
        strcpy(D->data[loc].code, code);
        return true;
    }
    
    else { // case for when slot is not empty
            if (D->avail == -1) return false;

        int cell = D->avail;
        D->avail = D->data[cell].next;
        
        strcpy(D->data[cell].city, city);
        strcpy(D->data[cell].code, code);
        D->data[cell].next = -1;
        
        // chaining to primary slot
        while (D->data[loc].next != -1){
            loc = D->data[loc].next;
        }
        D->data[loc].next = cell;
        return true;
    }
    
    return false;
}

int search(Dictionary D, char code[]){
    int loc = hash(code);
    
    while (loc != -1){
        if (strcmp(D.data[loc].code, code) == 0) return loc;
        loc = D.data[loc].next;
    }
    
    return -1;
}

bool delete(Dictionary* D, char code[]){
    int loc = hash(code);
    int prev = -1;
    
    while (loc != -1){
        
        if (strcmp(D->data[loc].code, code) == 0){
            // case when there is no chaining
            if (prev == -1){
                D->data[loc].code[0] = '\0';
                return true;
            }
            
            // deleting node
            D->data[prev].next = D->data[loc].next;
            D->data[loc].code[0] = '\0';
            
            // updating avail
            D->data[loc].next = D->avail;
            D->avail = loc;
            return true;
        } 
        
        prev = loc;
        loc = D->data[loc].next;
    }
    
    return false;
}


void display(Dictionary D){
    printf("\n%-6s %-10s %-6s\n", "Index", "Code", "Next");
    printf("-------------------------\n");
    
    for (int i = 0; i < MAX; i++){
        if (D.data[i].code[0] != '\0'){
            printf("%-6d %-10s %-6d\n", i, D.data[i].code, D.data[i].next);
        } else {
            printf("%-6d %-10s %-6d\n", i, "---", D.data[i].next);
        }
        
        if (i == SIZE - 1){
            printf("-------------------------\n");
        }
    }
    printf("\n");
}

int main(){
    Dictionary D;
    initDictionary(&D);

    insert(&D, "LAX", "Los Angeles");
    insert(&D, "NRT", "Tokyo");
    insert(&D, "DXB", "Dubai");
    insert(&D, "SYD", "Sydney");
    insert(&D, "HND", "Haneda");
    insert(&D, "SIN", "Singapore");

    printf("\n--- INITIAL STATE ---\n");
    display(D);

    printf("\nDeleting 'DXB'...\n");
    delete(&D, "DXB");

    printf("\n--- AFTER DELETION ---\n");
    display(D);

    printf("\nSearching for 'HND'...\n");
    int idx = search(D, "HND");
    if (idx != -1)
        printf("Found 'HND' at index %d.\n", idx);
    else
        printf("'HND' not found.\n");

    return 0;
}
