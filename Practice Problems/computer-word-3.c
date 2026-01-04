// VOID STREAM ENCRYPTOR (COMPWORD #5)

#include <stdio.h>
#include <stdlib.h>

#define SECRET_KEY 0xAA55 // Binary: 1010 1010 0101 0101

int* textToBitStream(char string[]) {
    int idx = 0;
    int* arr = malloc(sizeof(int) * 32);

    for (int i = 0; i < 4; i++){
        unsigned char c = string[i];

        for (int j = 7; j >= 0; j--){
            arr[idx] = (c >> j) & 1;
            idx++;
        }
    }
    
    return arr;
}

unsigned short* packAndEncrypt(int bitArray[]) {
    int idx = 0;
    unsigned short int* arr = malloc(sizeof(short int) * 2);

    for (int i = 0; i < 2; i++){
        unsigned short int temp = 0;

        for (int j = 0; j < 16; j++){
            temp = (temp << 1);
            temp |= bitArray[idx++];
        }

        temp = temp ^ SECRET_KEY;
        arr[i] = temp;
    }

    
    return arr;
}

void displayRawBits(int bitArray[]) {
    int i;
    for (i = 0; i < 32; i++) {
        printf("%d", bitArray[i]);
        if ((i + 1) % 8 == 0) printf(" "); 
    }
    printf("\n");
}

int main() {
    // Test Case: "WIFI"
    // 'W' = 01010111
    // 'I' = 01001001
    // 'F' = 01000110
    // 'I' = 01001001
    char message[5] = {'W', 'I', 'F', 'I', '\0'};
    
    int *rawBits = NULL;
    unsigned short *encryptedData = NULL;
    int choice, x;

    printf("=== Void-Stream Encryptor ===\n\n");
    printf("Target Message: %s\n\n", message);

    printf("1. EXPLODE: Convert string to Bit Stream (int array)\n");
    printf("2. ENCRYPT: Pack bits to short and XOR with Key\n");
    printf("3. FULL PROCESS: Display both steps\n");
    printf("\nChoice: ");
    scanf("%d", &choice);
    printf("\n");

    switch(choice) {
        case 1:
            rawBits = textToBitStream(message);
            if (rawBits != NULL) {
                printf("Raw Bit Stream:\n");
                displayRawBits(rawBits);
                free(rawBits);
            }
            break;

        case 2:
            // For simulation, we need the bits first
            rawBits = textToBitStream(message);
            encryptedData = packAndEncrypt(rawBits);
            
            printf("Encrypted Packets (Decimal):\n");
            for(x = 0; x < 2; x++) {
                printf("[%d]: %hu\n", x, encryptedData[x]);
            }
            
            free(rawBits);
            free(encryptedData);
            break;

        case 3:
            rawBits = textToBitStream(message);
            printf("Step 1 - Raw Bits:\n");
            displayRawBits(rawBits);
            
            encryptedData = packAndEncrypt(rawBits);
            printf("\nStep 2 - Encrypted Data:\n");
            printf("Key Used: 0xAA55 (43605)\n");
            
            for(x = 0; x < 2; x++) {
                printf("Word %d: %hu\n", x, encryptedData[x]);
            }

            free(rawBits);
            free(encryptedData);
            break;

        default:
            printf("Invalid Choice.\n");
            break;
    }

    return 0;
}