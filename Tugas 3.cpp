#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define HASH_SIZE 10

struct listNode {
    char value[100];
    struct listNode* nextPtr;
} *bucketArray[26], *pointer;

int calculateCharHash(char value[]) {
    int hashIndex = -1;
    char initialChar;
    initialChar = value[0];
    hashIndex = tolower(initialChar) - 97;
    return hashIndex;
}

int divisionMethod(int keyValue) {
    return keyValue % HASH_SIZE;
}

int foldingMethod(int keyValue) {
    int segment1 = keyValue / 1000;
    int segment2 = keyValue % 1000;
    return (segment1 + segment2) % HASH_SIZE;
}

int middleSquareMethod(int keyValue) {
    int squareResult = keyValue * keyValue;
    return (squareResult / 100) % 100;  // Ambil dua digit tengah
}

int extractDigitMethod(int keyValue) {
    return keyValue % HASH_SIZE;
}

int rotationMethod(int keyValue) {
    return (keyValue >> 3) ^ keyValue;
}

void displayHashTable() {
    for (int i = 0; i < 26; i++) {
        if (bucketArray[i] != NULL) {
            printf("Slot [%d]:\n", i);
            pointer = bucketArray[i];
            while (pointer != NULL) {
                printf("%s ", pointer->value);
                pointer = pointer->nextPtr;
            }
            printf("\n");
        }
    }
}

void insertAtEnd(int hashIndex, char value[]) {
    struct listNode* freshNode = (struct listNode*)malloc(sizeof(struct listNode));
    strcpy(freshNode->value, value);
    freshNode->nextPtr = NULL;
    
    if (bucketArray[hashIndex] == NULL) {
        bucketArray[hashIndex] = freshNode;
    }
    else {
        pointer = bucketArray[hashIndex];
        while (pointer->nextPtr != NULL)
            pointer = pointer->nextPtr;
        pointer->nextPtr = freshNode;
    }
}

int main() {
    int selection, hashingMethod;
    char inputValue[100];
    
    printf("Pilih Fungsi Hash:\n");
    printf("1. Hash Function (Karakter Pertama)\n");
    printf("2. Metode Pembagian\n");
    printf("3. Metode Folding\n");
    printf("4. Metode Mid-Square\n");
    printf("5. Metode Ekstraksi Digit\n");
    printf("6. Metode Rotasi\n");
    scanf("%d", &hashingMethod);
    
    do {
        printf("Masukkan Data: ");
        scanf("%s", inputValue);
        getchar();
        
        if (strcmpi(inputValue, "exit") == 0) break;
        
        switch (hashingMethod) {
        case 1:
            insertAtEnd(calculateCharHash(inputValue), inputValue);
            break;
        case 2:
            insertAtEnd(divisionMethod(atoi(inputValue)), inputValue);
            break;
        case 3:
            insertAtEnd(foldingMethod(atoi(inputValue)), inputValue);
            break;
        case 4:
            insertAtEnd(middleSquareMethod(atoi(inputValue)), inputValue);
            break;
        case 5:
            insertAtEnd(extractDigitMethod(atoi(inputValue)), inputValue);
            break;
        case 6:
            insertAtEnd(rotationMethod(atoi(inputValue)), inputValue);
            break;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (1);
    
    displayHashTable();
    getchar();
    return 0;
}
