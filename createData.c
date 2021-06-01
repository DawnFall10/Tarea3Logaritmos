#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], M[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

char *decimal_to_binary(int n) {
  int c, d, t;
  char *p;

  t = 0;
  p = (char*)malloc(18+1);

  if (p == NULL)
    exit(EXIT_FAILURE);

  for (c = 17 ; c >= 0 ; c--)
  {
    d = n >> c;

    if (d & 1)
      *(p+t) = 1 + '0';
    else
      *(p+t) = 0 + '0';

    t++;
  }
  *(p+t) = '\0';

  return  p;
}

void createData(int N, char *fileName) {
    int randArray[N];
    for (int i = 0; i < N; i++)
        randArray[i] = rand() % 200000;
    mergeSort(randArray, 0, N - 1);

    FILE* fPtr;
    char name[20];
    char txt[] = ".txt";
    strcpy(name, fileName);
    strcat(name, txt);
    fPtr = fopen(name, "w+");
    char binario[32];
    if (fPtr == NULL) {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        strcpy(binario, decimal_to_binary(randArray[i]));
        fprintf(fPtr, "%s", binario);
    }
    fclose(fPtr);
    printf("Archivo creado\n");
}

void main(void) {
    long N;
    char name[20];
    printf("Ingrese nombre del archivo a crear:");
    scanf("%s", &name);
    printf("Ingrese la cantidad de elementos para el arreglo: ");
    int x = scanf("%ld", &N);
    createData(N, name);
}
