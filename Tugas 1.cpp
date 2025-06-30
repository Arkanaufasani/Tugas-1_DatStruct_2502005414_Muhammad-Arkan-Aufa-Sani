#include <stdio.h>
#include <stdlib.h>

// Struktur node untuk doubly linked list
struct listNode
{
    int data;
    struct listNode *nextPtr;
    struct listNode *prevPtr;
} *headPtr, *tailPtr, *currentPtr;

// Fungsi untuk menambahkan elemen di awal list
void insertAtBeginning(int val)
{
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    newNode->data = val;
    
    if (headPtr == NULL)
    {
        headPtr = tailPtr = newNode;
        newNode->nextPtr = NULL;
        newNode->prevPtr = NULL;
    }
    else
    {
        newNode->nextPtr = headPtr;
        headPtr->prevPtr = newNode;
        headPtr = newNode;
        headPtr->prevPtr = NULL;
    }
}

// Fungsi untuk menambahkan elemen di akhir list
void insertAtEnd(int val)
{
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    newNode->data = val;
    
    if (headPtr == NULL)
    {
        headPtr = tailPtr = newNode;
        tailPtr->nextPtr = NULL;
        tailPtr->prevPtr = NULL;
    }
    else
    {
        tailPtr->nextPtr = newNode;
        newNode->prevPtr = tailPtr;
        tailPtr = newNode;
        tailPtr->nextPtr = NULL;
    }
}

// Fungsi untuk menambahkan elemen setelah node dengan nilai tertentu
void insertAfterValue(int val, int targetValue)
{
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    newNode->data = val;

    if (headPtr == NULL)
    {
        headPtr = tailPtr = newNode;
        newNode->nextPtr = NULL;
        newNode->prevPtr = NULL;
    }
    else
    {
        struct listNode *currentPtr = headPtr;
        while (currentPtr != NULL)
        {
            if (currentPtr->data == targetValue)
            {
                if (currentPtr == tailPtr)
                {
                    insertAtEnd(val);
                }
                else
                {
                    newNode->nextPtr = currentPtr->nextPtr;
                    newNode->prevPtr = currentPtr;
                    currentPtr->nextPtr->prevPtr = newNode;
                    currentPtr->nextPtr = newNode;
                }
                return;
            }
            currentPtr = currentPtr->nextPtr;
        }
        printf("Data %d tidak ditemukan\n", targetValue);
    }
}

// Fungsi untuk menghapus elemen dari akhir list
void removeFromEnd()
{
    if (headPtr == NULL)
    {
        printf("List kosong\n");
    }
    else
    {
        if (headPtr == tailPtr)
        {
            free(headPtr);
            headPtr = tailPtr = NULL;
        }
        else
        {
            struct listNode *nodeToDelete = tailPtr;
            tailPtr = tailPtr->prevPtr;
            tailPtr->nextPtr = NULL;
            free(nodeToDelete);
        }
    }
}

// Fungsi untuk menghapus elemen dari awal list
void removeFromBeginning()
{
    if (headPtr == NULL)
    {
        printf("List kosong\n");
    }
    else
    {
        if (headPtr == tailPtr)
        {
            free(headPtr);
            headPtr = tailPtr = NULL;
        }
        else
        {
            struct listNode *nodeToDelete = headPtr;
            headPtr = headPtr->nextPtr;
            headPtr->prevPtr = NULL;
            free(nodeToDelete);
        }
    }
}

// Fungsi untuk menghapus elemen dengan nilai tertentu
void removeByValue(int targetValue)
{
    if (headPtr == NULL)
    {
        printf("List kosong\n");
        return;
    }
    
    struct listNode *currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        if (currentPtr->data == targetValue)
        {
            if (currentPtr == headPtr)
            {
                removeFromBeginning();
            }
            else if (currentPtr == tailPtr)
            {
                removeFromEnd();
            }
            else
            {
                currentPtr->prevPtr->nextPtr = currentPtr->nextPtr;
                currentPtr->nextPtr->prevPtr = currentPtr->prevPtr;
                free(currentPtr);
            }
            return;
        }
        currentPtr = currentPtr->nextPtr;
    }
    printf("Data %d tidak ditemukan\n", targetValue);
}

// Fungsi untuk menampilkan seluruh isi list
void displayList()
{
    if (headPtr == NULL)
    {
        printf("List kosong\n");
        return;
    }

    currentPtr = headPtr;
    while (currentPtr != NULL)
    {
        printf("%d ", currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }
    printf("\n");
}

int main()
{
    printf("Operasi Doubly Linked List\n");

    insertAtBeginning(76);
    insertAtBeginning(90);
    insertAtBeginning(45);
    insertAtEnd(100);
    insertAfterValue(55, 90);
    removeFromEnd();
    removeFromBeginning();
    removeByValue(55);
    
    displayList();

    return 0;
}
