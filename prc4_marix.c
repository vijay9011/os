#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

// Dimensions of matrices
int rowA, colA, rowB, colB;
int matrixA[MAX][MAX], matrixB[MAX][MAX], result[MAX][MAX];

// Structure to pass data to threads
typedef struct {
    int row;
    int col;
} MatrixCell;

void* multiplyCell(void* arg) {
    MatrixCell* cell = (MatrixCell*) arg;
    int sum = 0;
    for (int k = 0; k < colA; ++k) {
        sum += matrixA[cell->row][k] * matrixB[k][cell->col];
    }
    result[cell->row][cell->col] = sum;
    free(cell);
    pthread_exit(0);
}

int main() {
    printf("Enter the number of rows and columns for Matrix A: ");
    scanf("%d %d", &rowA, &colA);
    printf("Enter the number of rows and columns for Matrix B: ");
    scanf("%d %d", &rowB, &colB);

    if (colA != rowB) {
        printf("Matrix multiplication not possible with the given dimensions.\n");
        return -1;
    }

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colA; ++j) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < rowB; ++i) {
        for (int j = 0; j < colB; ++j) {
            scanf("%d", &matrixB[i][j]);
        }
    }

    pthread_t threads[rowA][colB];

    // Creating threads for each cell of the result matrix
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; {
            MatrixCell* cell = (MatrixCell*) malloc(sizeof(MatrixCell));
            cell->row = i;
            cell->col = j;
            pthread_create(&threads[i][j], NULL, multiplyCell, (void*) cell);
        }
    }

    // Joining threads
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Printing the result matrix
    printf("Resultant Matrix:\n");
    for (int i = 0; i < rowA; ++i) {
        for (int j = 0; j < colB; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}
