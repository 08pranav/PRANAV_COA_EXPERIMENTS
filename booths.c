#include <stdio.h>
#include <stdlib.h>

void arithmeticRightShift(int* A, int* Q, int* Q_1, int n) {
    *Q_1 = *Q & 1;
    *Q = (*Q >> 1) | ((*A & 1) << (n - 1));
    *A = *A >> 1;
    
    if (*A < 0) {
        *A |= (1 << (n - 1));
    }
}

void printBinary(int num, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int boothMultiplication(int multiplicand, int multiplier, int n) {
    int A = 0;
    int Q = multiplier;
    int Q_1 = 0;
    int M = multiplicand;
    int count = n;
    
    printf("\nA = ");
    printBinary(A, n);
    printf(" Q = ");
    printBinary(Q, n);
    printf(" Q_1 = %d M = ", Q_1);
    printBinary(M, n);
    printf(" Count = %d\n", count);
    
    while (count > 0) {
        int Q0 = Q & 1;
        
        printf("\nStep %d: Q0 = %d Q_1 = %d\n", n - count + 1, Q0, Q_1);
        
        if (Q0 == 1 && Q_1 == 0) {
            A = A - M;
            printf("A = A - M = ");
            printBinary(A, n);
            printf("\n");
        }
        else if (Q0 == 0 && Q_1 == 1) {
            A = A + M;
            printf("A = A + M = ");
            printBinary(A, n);
            printf("\n");
        }
        else {
            printf("No operation\n");
        }
        
        printf("Before shift A = ");
        printBinary(A, n);
        printf(" Q = ");
        printBinary(Q, n);
        printf(" Q_1 = %d\n", Q_1);
        
        arithmeticRightShift(&A, &Q, &Q_1, n);
        
        printf("After shift  A = ");
        printBinary(A, n);
        printf(" Q = ");
        printBinary(Q, n);
        printf(" Q_1 = %d\n", Q_1);
        
        count--;
    }
    
    
    long long result = ((long long)A << n) | (Q & ((1 << n) - 1));
    if (A < 0) {
        result |= ~((1LL << (2 * n)) - 1);
    }
    return (int)result;
}

int main() {
    int multiplicand, multiplier, n;
    
    printf("Enter number of bits: ");
    scanf("%d", &n);
    
    printf("Enter multiplicand: ");
    scanf("%d", &multiplicand);
    
    printf("Enter multiplier: ");
    scanf("%d", &multiplier);
    
    printf("\nMultiplicand = %d (", multiplicand);
    printBinary(multiplicand, n);
    printf(")\n");
    printf("Multiplier = %d (", multiplier);
    printBinary(multiplier, n);
    printf(")\n");
    
    
    int result = boothMultiplication(multiplicand, multiplier, n);
    int expected = multiplicand * multiplier;
    
    printf("\nResult = ");
    printBinary(result, 2 * n);
    printf("\n");
    printf("Decimal result = %d\n", result);
    printf("Expected result = %d\n", expected);
    printf("Status = %s\n", (result == expected) ? "CORRECT" : "INCORRECT");
    
    return 0;
}