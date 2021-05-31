#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <methods.h>

int convert(int n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;


bool busquedaBinaria(char *fileName, int x, int low, int high) {
    FILE *fPtr;
    fPtr = fopen(filename)

    while (low <= high) {
        int mid = low + (high - low)/2;
        int puntero = mid*32
        fseek(fPtr, (mid*32), SEEK_SET);
        char num[32];
        char c = fgetc(fPtr);
        strcpy(num, c);
        for (int i = 0; i<31; i++){
            c = fgetc(fPtr);
            strcat(num, c);
        }
        int entero = atoi(num);
        entero = convert(entero);
        if (entero == x)
            return true;
        
        if (entero < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    fclose(fPtr);
    return false;
}

bool main(void) {
    char name[20];
    int value;
    int N;
    printf("Ingrese nombre del archivo:");
    scanf("%s", &name);
    printf("Ingrese la cantidad de elementos en el arreglo: ");
    int x = scanf("%d", &N);
    printf("Ingrese valor a buscar:")
    int y = scanf("%d", &value);

    return busquedaBinaria(name, value, 0, N-1);

}