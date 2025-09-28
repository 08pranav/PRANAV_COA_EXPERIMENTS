#include<stdio.h>
#include<string.h>

void toBinary(int num, int bits, char* binary) {
    int i;
    for(i = bits - 1; i >= 0; i--) {
        binary[bits - 1 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    binary[bits] = '\0';
}

void restoring(int q, int m, int n) {
    int a = 0;
    int i;
    char binaryA[33], binaryQ[33], binaryM[33];
    
    printf("Restoring Division:\n");
    toBinary(a, n, binaryA);
    toBinary(q, n, binaryQ);
    toBinary(m, n, binaryM);
    printf("Initial: A=%s Q=%s M=%s\n", binaryA, binaryQ, binaryM);
    
    for(i = 0; i < n; i++) {
        a = (a << 1) | ((q >> (n-1)) & 1);
        q = q << 1;
        
        a = a - m;
        
        if(a < 0) {
            q = q & (~1);
            a = a + m;
        } else {
            q = q | 1;
        }
        
        toBinary(a, n, binaryA);
        toBinary(q, n, binaryQ);
        printf("Step %d: A=%s Q=%s\n", i+1, binaryA, binaryQ);
    }
    
    // Mask to n bits to get correct decimal values
    int mask = (1 << n) - 1;
    q = q & mask;
    a = a & mask;
    
    toBinary(q, n, binaryQ);
    toBinary(a, n, binaryA);
    printf("Quotient: %s (%d)\n", binaryQ, q);
    printf("Remainder: %s (%d)\n", binaryA, a);
}

void nonrestoring(int q, int m, int n) {
    int a = 0;
    int i;
    char binaryA[33], binaryQ[33], binaryM[33];
    
    printf("\nNon-Restoring Division:\n");
    toBinary(a, n, binaryA);
    toBinary(q, n, binaryQ);
    toBinary(m, n, binaryM);
    printf("Initial: A=%s Q=%s M=%s\n", binaryA, binaryQ, binaryM);
    
    for(i = 0; i < n; i++) {
        a = (a << 1) | ((q >> (n-1)) & 1);
        q = q << 1;
        
        if(a >= 0) {
            a = a - m;
        } else {
            a = a + m;
        }
        
        if(a >= 0) {
            q = q | 1;
        } else {
            q = q & (~1);
        }
        
        toBinary(a, n, binaryA);
        toBinary(q, n, binaryQ);
        printf("Step %d: A=%s Q=%s\n", i+1, binaryA, binaryQ);
    }
    
    if(a < 0) {
        a = a + m;
    }
    
    // Mask to n bits to get correct decimal values
    int mask = (1 << n) - 1;
    q = q & mask;
    a = a & mask;
    
    toBinary(q, n, binaryQ);
    toBinary(a, n, binaryA);
    printf("Quotient: %s (%d)\n", binaryQ, q);
    printf("Remainder: %s (%d)\n", binaryA, a);
}

int main() {
    int dividend, divisor;
    int n = 8; // Fixed 8-bit width
    
    printf("Enter dividend: ");
    scanf("%d", &dividend);
    printf("Enter divisor: ");
    scanf("%d", &divisor);
    
    restoring(dividend, divisor, n);
    nonrestoring(dividend, divisor, n);
    
    return 0;
}