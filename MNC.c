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

void printMatrixFloat(float** matrix, int colSize, int rowSize) {
    int col, row;

    for (col = 0; col < colSize; col++)
    {
        for (row = 0; row < rowSize; row++)
        {
            printf("%.2f ", matrix[col][row]);
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

void createMatrixFloat(float **matrix, int colSize, int rowSize) {
    int col, row, defaultValue = 0;

    // matrix = (int **)malloc(colSize * sizeof(int *));
    for (row = 0; row < rowSize; row++) {
        matrix[row] = (float *)malloc(rowSize * sizeof(float));
    }

    for (col = 0; col < colSize; col++)
    {
        for (row = 0; row < rowSize; row++)
        {
            matrix[col][row] = defaultValue;
        }
    }
}

//Exercicio 1
int Determinante(int matrixSize, int**matrix) {
    int col, row, newMatrixCol, newMatrixRow, indexK, det = 0, subDet = 0;
    if(matrixSize == 1){
        return matrix[0][0];
    }
    if(matrixSize == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    for (indexK = 0; indexK < matrixSize; indexK++){
        int newMatrixSize = matrixSize - 1;
        int **newMatrix = (int **) malloc(newMatrixSize * sizeof(int *));
        createMatrix(newMatrix, newMatrixSize, newMatrixSize);

        for (col = 0, newMatrixCol = 0; col < matrixSize; col++)
        {
            if(col == indexK){
                continue;
            }

            for (row = 1, newMatrixRow = 0; row < matrixSize; row++)
            {
                newMatrix[newMatrixCol][newMatrixRow++] = matrix[col][row];
            }

            newMatrixCol++;
        }
        subDet = Determinante(newMatrixSize, newMatrix);

        det += subDet * matrix[indexK][0] *  (int) pow(-1, indexK);
    }

    return det;
}



float nextU(int i, int j, float** matrix, float** solv){
    float a = matrix[i][j];

    float sum = 0;
    int k;

    for (k = 0; k < i; k++) {
        sum += solv[i][k] * solv[k][j];
    }

    return a - sum;
}

float nextL(int i, int j, float** matrix, float** solv){
    int a = matrix[i][j];

    int sum = 0;
    int k;

    for (k = 0; k < i; k++) {
        sum += solv[i][k] * solv[k][j];
    }

    return (a - sum)/solv[j][j];
}

//Exercicio 6
void GaussCompacto(int systemOrder, int **matrixCoeficiente, float* vetorIndependente, float* vetorSolucao){
    int index;

    // Criterio de parada
    for (index = 1; index <= systemOrder; index++)
    {
        int det = Determinante(index, matrixCoeficiente);
        if(det == 0){
            return;
        }
        printf("sub dets = %i\n", det);
    }


    int i, j;
    float **solv = (float **)malloc((systemOrder) * sizeof(float *));
    createMatrixFloat(solv, systemOrder, systemOrder + 1);

    float **matrixPlus = (float **)malloc((systemOrder) * sizeof(float *));
    createMatrixFloat(matrixPlus, systemOrder, systemOrder + 1);


    // criar matrix ampliada e popular
    for (i = 0; i < systemOrder; i++)
    {
        for (j = 0; j < systemOrder; j++)
        {
            matrixPlus[i][j] = matrixCoeficiente[i][j];
        }
        matrixPlus[i][systemOrder] = vetorIndependente[i];
    }
    
    // Popular matriz solucão intermediaria
    for(i = 0; i < systemOrder; i++) {
        for(j = 0; j < systemOrder + 1; j++) {
            if(i > j){
                solv[i][j] = nextL(i, j, matrixPlus, solv);
            }
            else {
                solv[i][j] = nextU(i, j, matrixPlus, solv);
            }
        }
    }
    
    // calcular vetor de solução
    for (i = systemOrder - 1; i >= 0; i--)
    {
        float sum = solv[i][systemOrder];
        for(j = systemOrder -1; j >= 0; j--) {
            if(!(i > j)){
                sum -= vetorSolucao[j] * solv[i][j];
            }
        }
        vetorSolucao[i] = sum / solv[i][i];
    }
}


//Exercicio 10


void main() {
    int matrixSize = 3;
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
    float vet[] = {6.0, 3.0, 3.0};
    float *solucao = malloc(matrixSize * sizeof(float *));;

    GaussCompacto(matrixSize, matrix, vet, solucao);

    // printMatrix(matrix, matrixSize, matrixSize);
    // int det = Determinante(matrixSize, matrix);
    // printf("\nResultado = %i\n", det);
    // printMatrix(matrix, matrixSize, matrixSize);

}