#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(int** matrix, int colSize, int rowSize) {
    int col, row;

    for (col = 0; col < colSize; col++)
    {
        for (row = 0; row < rowSize; row++)
        {
            printf("%i ", matrix[col][row]);
        }
        printf("\n");
    }
}

void createMatrix(int **matrix, int colSize, int rowSize) {
    int col, row, defaultValue = 0;

    // matrix = (int **)malloc(colSize * sizeof(int *));
    for (row = 0; row < rowSize; row++) {
        matrix[row] = (int *)malloc(rowSize * sizeof(int));
    }

    for (col = 0; col < colSize; col++)
    {
        for (row = 0; row < rowSize; row++)
        {
            matrix[col][row] = defaultValue;
        }
    }
}


int laplace(int**matrix, int colSize, int rowSize) {
    int col, row, newMatrixCol, newMatrixRow, indexK, det = 0, subDet = 0;

    if(colSize == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    for (indexK = 0; indexK < colSize; indexK++){
        int newColSize = colSize - 1;
        int **newMatrix = (int **) malloc(newColSize * sizeof(int *));
        createMatrix(newMatrix, newColSize, newColSize);

        for (col = 0, newMatrixCol = 0; col < colSize; col++)
        {
            if(col == indexK){
                continue;
            }

            for (row = 1, newMatrixRow = 0; row < rowSize; row++)
            {
                newMatrix[newMatrixCol][newMatrixRow++] = matrix[col][row];
            }

            newMatrixCol++;
        }
        subDet = laplace(newMatrix, newColSize, newColSize) ;

        det += subDet * matrix[indexK][0] *  (int) pow(-1, indexK);
    }

    return det;
}




void main() {
    int matrixSize = 4;
    int col, row, index = 0, input;

    int **matrix = (int **)malloc(matrixSize * sizeof(int *));
    createMatrix(matrix, matrixSize, matrixSize);
    
    for (col = 0; col < matrixSize; col++)
    {
        for (row = 0; row < matrixSize; row++)
        {
            scanf("%i", &input);
            matrix[col][row] = input;
        }
    }
    
    printMatrix(matrix, matrixSize, matrixSize);
    int det = laplace(matrix, matrixSize, matrixSize);
    printf("\nResultado = %i\n", det);
    printMatrix(matrix, matrixSize, matrixSize);

}