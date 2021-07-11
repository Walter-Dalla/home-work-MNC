#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void clearArray(float* vector, int size) {
    int index;
    for (index = 0; index < size; index++)
    {
        vector[index] = 0;
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

void printVectorFloat(float* vector, int colSize) {
    int col;

    for (col = 0; col < colSize; col++)
    {
        printf("%.2f\n", vector[col]);
    }
}

void createMatrixFloat(float **matrix, int colSize, int rowSize) {
    int col, row, defaultValue = 0;

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
float Determinante(int matrixSize, float**matrix) {
    int col, row, newMatrixCol, newMatrixRow, indexK;
    float det = 0, subDet = 0;
    if(matrixSize == 1){
        return matrix[0][0];
    }

    if(matrixSize == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    for (indexK = 0; indexK < matrixSize; indexK++){
        int newMatrixSize = matrixSize - 1;
        float **newMatrix = (float **) malloc(newMatrixSize * sizeof(float *));
        createMatrixFloat(newMatrix, newMatrixSize, newMatrixSize);

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

        det += subDet * matrix[indexK][0] *  pow(-1, indexK);
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
void GaussCompacto(int systemOrder, float **matrixCoeficiente, float* vetorIndependente, float* vetorSolucao){
    int index;

    // Criterio de parada
    for (index = 1; index <= systemOrder; index++)
    {
        float det = Determinante(index, matrixCoeficiente);
        if(det == 0){
            return;
        }
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
void MatrizInversa(int systemOrder, float **matriz, float** matrizInversa){
    float determinante = Determinante(systemOrder, matriz);

    if(determinante == 0) {
        return;
    }

    int col, row;
    float** identidade = (float **)malloc((systemOrder) * sizeof(float *));


    createMatrixFloat(identidade, systemOrder, systemOrder);

    for (row = 0; row < systemOrder; row++)
    {
        for (col = 0; col < systemOrder; col++)
        {
            if(col == row){
                identidade[row][col] = 1;
            }
            else {
                identidade[row][col] = 0;
            }
        }
    }
    
    for (row = 0; row < systemOrder; row++)
    {
        float* vetorInversaAux = malloc((systemOrder) * sizeof(float *));
        clearArray(vetorInversaAux, systemOrder);
        
        GaussCompacto(systemOrder, matriz, identidade[row], vetorInversaAux);
        for (col = 0; col < systemOrder; col++)
        {
            matrizInversa[col][row] = vetorInversaAux[col];
        }
    }
}



void main() {
    int matrixSize = 3;
    int col, row, index = 0, input;

    float **matrix = (float **)malloc(matrixSize * sizeof(float *));
    createMatrixFloat(matrix, matrixSize, matrixSize);

    float** matrizInversa = (float **)malloc(matrixSize * sizeof(float *));
    createMatrixFloat(matrizInversa, matrixSize, matrixSize);

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

    MatrizInversa(matrixSize, matrix, matrizInversa);

    printMatrixFloat(matrizInversa, matrixSize, matrixSize);

}