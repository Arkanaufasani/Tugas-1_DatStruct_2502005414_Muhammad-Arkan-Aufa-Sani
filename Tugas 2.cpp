#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 100

struct StackStructure {
    int topIndex;
    char elements[CAPACITY];
};

struct StackStructure* initializeStack() {
    struct StackStructure* stackPtr = (struct StackStructure*)malloc(sizeof(struct StackStructure));
    stackPtr->topIndex = -1;
    return stackPtr;
}

int checkEmpty(struct StackStructure* stackPtr) {
    return stackPtr->topIndex == -1;
}

int checkFull(struct StackStructure* stackPtr) {
    return stackPtr->topIndex == CAPACITY - 1;
}

void insertElement(struct StackStructure* stackPtr, char val) {
    if (!checkFull(stackPtr)) {
        stackPtr->elements[++stackPtr->topIndex] = val;
    }
}

char removeElement(struct StackStructure* stackPtr) {
    if (!checkEmpty(stackPtr)) {
        return stackPtr->elements[stackPtr->topIndex--];
    }
    return -1;
}

char viewTop(struct StackStructure* stackPtr) {
    if (!checkEmpty(stackPtr)) {
        return stackPtr->elements[stackPtr->topIndex];
    }
    return -1;
}

int getOperatorPriority(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    } else if (operator == '^') {
        return 3;
    }
    return -1;
}

void convertInfixToPostfix(char* infixExpr, char* postfixExpr) {
    struct StackStructure* stackPtr = initializeStack();
    int index = 0;
    
    for (int i = 0; infixExpr[i] != '\0'; i++) {
        char currentChar = infixExpr[i];
        
        if ((currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9')) {
            postfixExpr[index++] = currentChar;
        } else if (currentChar == '(') {
            insertElement(stackPtr, currentChar);
        } else if (currentChar == ')') {
            while (!checkEmpty(stackPtr) && viewTop(stackPtr) != '(') {
                postfixExpr[index++] = removeElement(stackPtr);
            }
            removeElement(stackPtr);
        } else {
            while (!checkEmpty(stackPtr) && getOperatorPriority(viewTop(stackPtr)) >= getOperatorPriority(currentChar)) {
                postfixExpr[index++] = removeElement(stackPtr);
            }
            insertElement(stackPtr, currentChar);
        }
    }
    
    while (!checkEmpty(stackPtr)) {
        postfixExpr[index++] = removeElement(stackPtr);
    }
    postfixExpr[index] = '\0';
}

void convertPostfixToInfix(char* postfixExpr, char* infixExpr) {
    struct StackStructure* stackPtr = initializeStack();
    char tempBuffer[2];
    
    for (int i = 0; postfixExpr[i] != '\0'; i++) {
        char currentChar = postfixExpr[i];
        
        if ((currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= '0' && currentChar <= '9')) {
            tempBuffer[0] = currentChar;
            tempBuffer[1] = '\0';
            insertElement(stackPtr, tempBuffer[0]);
        } else {
            char operand2 = removeElement(stackPtr);
            char operand1 = removeElement(stackPtr);
            infixExpr[0] = '(';
            infixExpr[1] = operand1;
            infixExpr[2] = currentChar;
            infixExpr[3] = operand2;
            infixExpr[4] = ')';
            infixExpr[5] = '\0';
            insertElement(stackPtr, infixExpr[0]);
        }
    }
}

int main() {
    char infixInput[CAPACITY], postfixOutput[CAPACITY], convertedInfix[CAPACITY];
    printf("Masukkan ekspresi infix: ");
    scanf("%s", infixInput);
    
    convertInfixToPostfix(infixInput, postfixOutput);
    printf("Postfix: %s\n", postfixOutput);
    
    convertPostfixToInfix(postfixOutput, convertedInfix);
    printf("Infix dari Postfix: %s\n", convertedInfix);
    
    return 0;
}
