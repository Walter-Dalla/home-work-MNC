#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define FALSE 0
#define TRUE 1 

void Gauss(int ordem, float **matriz, float *vetorIndependente);
float Determinante(int matrixSize, float**matrix);
void createMatrix(float **matrix, int colSize, int rowSize);
void createVetor(float *vetor, int ordem);
int verifica_simetrica(int ordem, float **matriz);


/**
 * Utils
 */

void getMatrixSimetricSize(int* matrixOrder){

    printf("Digite a ordem da matriz (N x N)");
    scanf("%i", matrixOrder);
}

void getMatrixSize(int* matrixRow, int* matrixCol){

    printf("Digite a quantiade de linhas e colunas da matriz (N x M)");
    scanf("%i %i", matrixRow, matrixCol);
}

void clearArray(float* vector, int size) {
    int index;
    for (index = 0; index < size; index++)
    {
        vector[index] = 0;
    }
}

void printMatrix(float** matrix, int colSize, int rowSize) {
    int col, row;

    for (col = 0; col < colSize; col++)
    {
        if(colSize / 2 == col){
            printf("M   =");
        }
        
        printf("\t");

        for (row = 0; row < rowSize; row++)
        {
            printf("%.2f \t", matrix[col][row]);
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


void createMatrix(float **matrix, int colSize, int rowSize) {
    int col, row, defaultValue = 0;

    for (row = 0; row < rowSize; row++) {
        matrix[row] = (float *)malloc(rowSize * sizeof(float));
    }

    for (col = 0; col < colSize; col++)
    {
        for (row = 0; row < rowSize; row++) {
            matrix[col][row] = defaultValue;
        }
    }
}

void createVetor(float *vetor, int ordem) {
    int col, row, defaultValue = 0;

    for (row = 0; row < ordem; row++) {
        vetor[row] = defaultValue;
    }
}

int verifica_simetrica(int ordem, float **matriz) {
    int i, j;
    int ehSimetrica = FALSE;
    for(i = 0; i < ordem; i++) {
        for(j = 0; j < ordem; j++) {
            if(matriz[i][j] == matriz[j][i]) {
                ehSimetrica = TRUE;
            }
        }
    }

    return ehSimetrica;
}

void scanfMatrix(int matrixColSize, int matrixRowSize, float** matrix){
    int col, row;

    for (col = 0; col < matrixColSize; col++)
    {
        for (row = 0; row < matrixRowSize; row++)
        {
            printf("Digite a posicao M[%i][%i] da matriz: ", col+1, row+1);
            scanf("%f", &matrix[col][row]);
            printf("\n");
        }
    }
}


void scanfVector(int vectorSize, float* vector){
    int col;
    float input;
    
    for (col = 0; col < vectorSize; col++)
    {
        scanf("%i", &input);
        vector[col] = input;
    }
}

/**
 * Rotinas
 */

//Rotina 1
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

        det += subDet * matrix[indexK][0] *  pow(-1, indexK);

        free(newMatrix);
    }

    return det;
}

// Rotina 5
void Cholesky(int ordem, float **matriz, float *vetorIndependente) {
    int i, j, k;
    float determinante;
    float somaCaso1 = 0, somaCaso2 = 0;

    int ehSimetrica;
    ehSimetrica = verifica_simetrica(ordem, matriz);

    if(!ehSimetrica) {
        printf("\n A matriz nao e simetrica\n");
        return;
    }

    for(i = 0; i < ordem; i++) {
        determinante = Determinante(i + 1, matriz);
        if(determinante < 0) break;
    }

    if(determinante < 0) {
        printf("\n A matriz nao e definida positiva.\n");
        return;
    }

    float **novaMatriz = (float**) malloc(ordem * sizeof(float*));
    createMatrix(novaMatriz, ordem, ordem);

    for(i = 0; i < ordem; i++) {
        for(j = 0; j < ordem; j++) {
            if(i >= j) {
                if(i == 0 && j == 0) {
                    novaMatriz[i][j] = sqrt(matriz[i][j]);
                } else if (j == 0) {
                    novaMatriz[i][j] = matriz[i][j] / novaMatriz[j][j];
                } else if (j == i) {
                    // Somatório
                    k = 0;
                    if(i - 1 > k) {  // 2 > 0 
                        for(k = 0; k <= i - 1; k++) { // k < 2
                            somaCaso1 += pow(novaMatriz[i][k], 2);
                        }
                    } else {
                        somaCaso1 += pow(novaMatriz[i][k], 2);
                    }
                    novaMatriz[i][j] = sqrt(matriz[i][i] - somaCaso1);
                    somaCaso1 = 0;

                } else if(i != j) {
                    k = 0;
                    if(j - 1 > k) { 
                        for(k = 0; k <= j - 1; k++) { 
                            somaCaso2 += novaMatriz[i][k] * novaMatriz[j][k];
                        }
                    } else {
                        somaCaso2 += novaMatriz[i][k] * novaMatriz[j][k];
                    }
                    novaMatriz[i][j] = (matriz[i][j] - somaCaso2) / novaMatriz[j][j];
                    somaCaso2 = 0;

                }
                } else {
                    novaMatriz[i][j] = 0;
                }            
        }
    }

    printf("\n\n");

    float **novaMatrizTransposta = (float**) malloc(ordem * sizeof(float*));
    createMatrix(novaMatrizTransposta, ordem, ordem);

    for(i = 0; i < ordem; i++) {
        for(j = 0; j < ordem; j++) {
            novaMatrizTransposta[i][j] = novaMatriz[j][i];
        }
    }

    Gauss(ordem, novaMatriz, vetorIndependente);
    Gauss(ordem, novaMatrizTransposta, vetorIndependente);

    printf("\nSolucao:\n");
	for(i = 0; i < ordem; i++) {
	  	printf("Vetor [%d] = %.0f\n", i, vetorIndependente[i]);
	}
    
}


//Rotina 6
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
    createMatrix(solv, systemOrder, systemOrder + 1);

    float **matrixPlus = (float **)malloc((systemOrder) * sizeof(float *));
    createMatrix(matrixPlus, systemOrder, systemOrder + 1);


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

    free(solv);
    free(matrixPlus);
}


//Rotina 10
void MatrizInversa(int systemOrder, float **matriz, float** matrizInversa){
    float determinante = Determinante(systemOrder, matriz);

    if(determinante == 0) {
        return;
    }

    int col, row;
    float** identidade = (float **)malloc((systemOrder) * sizeof(float *));


    createMatrix(identidade, systemOrder, systemOrder);

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

    free(identidade);
}

void op1() {
    int matrixSize;
    getMatrixSimetricSize(&matrixSize);
    printf("%i\n\n", matrixSize);
    
    float** matrix = (float **)malloc(matrixSize * sizeof(float *));
    createMatrix(matrix, matrixSize, matrixSize);

    scanfMatrix(matrixSize, matrixSize, matrix);
    printMatrix(matrix, matrixSize, matrixSize);

    float det = Determinante(matrixSize, matrix);
    printf("A det(M) = %.2f", det);
}

void op2() {
    
}
void op3() {

}
void op4() {

}

void op5() {
    // A = G . Gt
    printf("\n---- Cholesky");
    int ordem;
    int i, j;

    printf("\n\nDigite a ordem do sistema: ");
    scanf("%d", &ordem);
    float **matriz = (float**) malloc(ordem * sizeof(float*));
    float *vetorIndependente = (float*) malloc(ordem * sizeof(float*));

    createMatrix(matriz, ordem, ordem);
    createVetor(vetorIndependente, ordem);

    printf("\n--- Matriz ---");
    
    for(i = 0; i < ordem; i++) {
		for(j = 0; j < ordem; j++) {
			printf("\nDigite o elemento de linha %d e coluna %d: ", i + 1, j + 1);
			scanf("%f", &matriz[i][j]);
		}
	}

    for(i = 0; i < ordem; i++) { 
		printf("\nDigite o vetor %d: ", i + 1);
		scanf("%f", &vetorIndependente[i]);
	}

    Cholesky(ordem, matriz, vetorIndependente);

}

void op6() {

}

void Gauss(int ordem, float **matriz, float *vetorIndependente) {

    float multiplicador;
    int i, j, k;

    float **matrizAmpliada = (float**) malloc((ordem + 1) * sizeof(float*));
    createMatrix(matrizAmpliada, ordem, ordem + 1);

    float *vetor = (float*) malloc(ordem * sizeof(float*));
    createVetor(vetor, ordem);

    for(i = 0; i < ordem; i++) {
        for(j = 0; j < ordem; j++) {
            matrizAmpliada[i][j] = matriz[i][j];
        }
    }

    for(i = 0; i < ordem; i++) {
        matrizAmpliada[i][ordem] = vetorIndependente[i];
    }

    for(i = 0; i < ordem - 1; i++) {
		if(matrizAmpliada[i][i] == 0.0) {
			printf("Erro matematico!");
			exit(0);
		}
		for(j = i + 1; j< ordem + 1; j++) {
			multiplicador = matrizAmpliada[j][i] / matrizAmpliada[i][i];			   
			for(k = 0; k < ordem + 1; k++) {
			  	matrizAmpliada[j][k] = matrizAmpliada[j][k] - multiplicador * matrizAmpliada[i][k];
			}
		}
	}

    printf("\nMatriz na sua forma final\n");

    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j <= ordem ; j++) {
            printf("%.1f\t", matrizAmpliada[i][j]);
        }
        printf("\n");
    }

	vetorIndependente[ordem - 1] = matrizAmpliada[ordem - 1][ordem] / matrizAmpliada[ordem - 1][ordem - 1];
	 for(i = ordem - 1; i >= 0; i--) 
	 {
		vetorIndependente[i] = matrizAmpliada[i][ordem];
		for(j = i + 1; j<= ordem; j++) {
		  	vetorIndependente[i] = vetorIndependente[i] - matrizAmpliada[i][j]*vetorIndependente[j];
		}
		vetorIndependente[i] = vetorIndependente[i]/matrizAmpliada[i][i];
	}

}

void op7() {

    printf("\n---- Eliminacao de Gauss");
    int ordem;
    int i, j;

    printf("\n\nDigite a ordem do sistema: ");
    scanf("%d", &ordem);
    float **matriz = (float**) malloc(ordem * sizeof(float*));
    float *vetorIndependente = (float*) malloc(ordem * sizeof(float*));

    createMatrix(matriz, ordem, ordem);
    createVetor(vetorIndependente, ordem);

    printf("\n--- Matriz ---");
    
    for(i = 0; i < ordem; i++) {
		for(j = 0; j < ordem; j++) {
			printf("\nDigite o elemento de linha %d e coluna %d: ", i + 1, j + 1);
			scanf("%f", &matriz[i][j]);
		}
	}

    for(i = 0; i < ordem; i++) { 
		printf("\nDigite o vetor %d: ", i + 1);
		scanf("%f", &vetorIndependente[i]);
	}

    Gauss(ordem, matriz, vetorIndependente);

    printf("\nSolucao:\n");
	for(i = 0; i < ordem; i++) {
	  	printf("vetorIndependente [%d] = %.0f\n", i, vetorIndependente[i]);
	}

}

void op8() {

}
void op9() {

}
void op10() {

}

void menu() {
    printf("--------- MENU ---------");
    printf("\n01 - Rotina Determinante");
    printf("\n02 - Rotina Sistema Triangular Inferior");
    printf("\n03 - Rotina Sistema Triangular Superior");
    printf("\n04 - Rotina Decomposicao LU");
    printf("\n05 - Rotina Cholesky");
    printf("\n06 - Rotina Gauss Compacto");
    printf("\n07 - Rotina Gauss Jordan");
    printf("\n08 - Rotina Jacobi");
    printf("\n09 - Rotina Gauss Seidel");
    printf("\n10 - Rotina Matriz Inversa");
    printf("\n11 - Sair");
}


int main() {
    menu();
    int op;
    printf("\n\nDigite sua opcao: ");
    scanf("%d", &op);
    while(op < 1 || op > 11) {
        printf("Opcao invalida! Redigite: ");
        scanf("%d", &op);
    }

    switch(op) {
        case 1: op1(); break;
        case 2: op2(); break;
        case 3: op3(); break;
        case 4: op4(); break; 
        case 5: op5(); break;
        case 6: op6(); break;
        case 7: op7(); break;
        case 8: op8(); break;
        case 9: op9(); break;
        case 10: op10(); break;
        case 11: exit(1); break;
    }
}