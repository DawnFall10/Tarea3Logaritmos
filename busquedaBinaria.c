#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define BILLION  1000000.0


long long binaryToDecimal(long long n)
{
    long long num = n;
    long long dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    long long temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;
}

int bstr_to_dec(const char * str)
{
    int val = 0;
     
    while (*str != '\0')
        val = 2 * val + (*str++ - '0');
    return val;
}

int busquedaBinaria(char *fileName, int x, int low, int high) {
    FILE *fPtr;
    fPtr = fopen(fileName, "r");

    while (low <= high) {
        int mid = low + (high - low)/2;
        int puntero = mid*18;
        char *eptr;
        fseek(fPtr, (mid*18), SEEK_SET);
        char num[18] = "0";
        char c = fgetc(fPtr);
        strncat(num, &c, 1);
        for (int i = 0; i<17; i++){
            c = fgetc(fPtr);
            strncat(num, &c, 1);
        }
        long long entero = atoll(num);
        entero = binaryToDecimal(entero);
        if (entero == x)
            return 1;
        
        if (entero < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    fclose(fPtr);
    return 0;
}

int main(void) {
    char name[20];
    long long value;
    int N;
    struct timespec start, end;
    
    printf("Ingrese nombre del archivo:");
    scanf("%s", &name);
    printf("Ingrese la cantidad de elementos en el arreglo: ");
    int x = scanf("%d", &N);
    printf("Ingrese valor a buscar:");
    int y = scanf("%d", &value);
    clock_gettime(CLOCK_REALTIME, &start);
    int result = busquedaBinaria(name, value, 0, N-1);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec)/BILLION;
    if (result == 1) {
        printf("True\n");
        printf("The elapsed time is %f miliseconds\n", time_spent);
    }
    else {
        printf("False\n");
        printf("The elapsed time is %f miliseconds\n", time_spent);
    }
}
