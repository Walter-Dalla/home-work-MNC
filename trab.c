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

void clearVector(float* vector, int size) {
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

void printMatrixWithName(float** matrix, int colSize, int rowSize, char* name) {
    int col, row;

    for (col = 0; col < colSize; col++)
    {
        if(colSize / 2 == col){
            printf("%s   =", name);
        }
        
        printf("\t");

        for (row = 0; row < rowSize; row++)
        {
            printf("%.2f \t", matrix[col][row]);
        }
        printf("\n");
    }
}

void printVector(float* vector, int colSize) {
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
        printf("Digite a posicao %i do vetor", col);
        scanf("%f", &vector[col]);
        printf("\n");
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

// Rotina 2
void SistemaTrianguloInferior()
{
    int k, l;
    int i, j;
    int numFinal[10];
    int ordem;

    getMatrixSimetricSize(&ordem);
    float** matriz = (float **)malloc(ordem * sizeof(float *));
    createMatrix(matriz, ordem, ordem);
    scanfMatrix(ordem, ordem, matriz);
    printMatrix(matriz, ordem, ordem);
    float *termosInd = (float*) malloc(ordem * sizeof(float*));
    createVetor(termosInd, ordem);
    scanfVector(ordem,termosInd);

    numFinal[0] = termosInd[0] / matriz[0][0];

    for (i = 1; i < ordem; i++)
    {
        int soma = 0;
        for (j = 0; j < i; j++)
        {
            soma += matriz[i][j] * numFinal[j];
        }
        numFinal[i] = (termosInd[i] - soma) / matriz[i][i];
    }

    printf("vetor solucao = ");
    for (i = 0; i < ordem; i++)
    {
        printf("%d  ", numFinal[i]);
    }
}

// Rotina 3
void SistemaTrianguloSuperior()
{

    int i, j;
    int numFinal2[10];
    int ordem;


    getMatrixSimetricSize(&ordem);
    float** matriz = (float **)malloc(ordem * sizeof(float *));
    createMatrix(matriz, ordem, ordem);
    scanfMatrix(ordem, ordem, matriz);
    printMatrix(matriz, ordem, ordem);
    float *termosInd = (float*) malloc(ordem * sizeof(float*));
    createVetor(termosInd, ordem);
    scanfVector(ordem,termosInd);


    ordem -= 1;

    numFinal2[ordem] = termosInd[ordem] / matriz[ordem][ordem];

    for (i = ordem - 1; i >= 0; i--)
    {
        int soma = 0;
        for (j = i + 1; j <= ordem; j++)
        {
            soma += matriz[i][j] * numFinal2[j];
        }
        numFinal2[i] = (termosInd[i] - soma) / matriz[i][i];
    }

    printf("vetor solucao = ");
    for (i = 0; i <= ordem; i++)
    {
        printf("%d  ", numFinal2[i]);
    }
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
                    // SomatÃ³rio
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

int CriterioLinhas(int ordem, float** matriz){
    int i,j,soma;
    float resultado[ordem];
    for (i = 0; i < ordem; i++)
    {
        soma = 0;
        for (j = 0; j < ordem; j++)
        {
            if (j != i)
            {
                soma += fabs(matriz[i][j]);
            }
        }
        resultado[i] = soma / matriz[i][i];
    }

    float maiorResultado = 0;

    for (i = 0; i < ordem; i++)
    {
        if (fabs(resultado[i]) > maiorResultado)
        {
            maiorResultado = resultado[i];
        }
    }

    if (maiorResultado < 1)
    {
        return 1;
    }
    else
    {
        return 0;
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


// 7
void Gauss(int ordem, float **matriz, float *vetorIndependente) {

    float multiplicador;
    int i, j, k;

    float **matrizAmpliada = (float**) malloc((ordem + 1) * sizeof(float*));
    createMatrix(matrizAmpliada, ordem, ordem + 1);

    float *vetor = (float*) malloc(ordem * sizeof(float*));
    clearVector(vetor, ordem);

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

    for(i = 0; i < ordem; i++) {
        for(j = 0; j <= ordem ; j++) {
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

// Rotina 8

float validarConvergencia(int Lin, int Col, float ** Matriz){
    
	int i, a, c;
	float numerador[i], denominador[i];
	float MatrizAb[i][c]; //Valor absoluto
    
    //Metodo Linhas
    
    //Tornando a matriz em matriz absoluta
	for(i = 0; i < Lin; i++){
		for(c = 0; c < Col; c++){
			MatrizAb[i][c] = fabs(Matriz[i][c]);
		}
	}	
	
	system("cls");
	printf("Matriz Absoluta\n");

    for(i = 0; i < Lin; i++){
		for(c = 0; c < Col; c++){
			printf("%.2f\t", MatrizAb[i][c]);
		}
		printf("\n");
	}
	
	//Limpa
	for(i = 0; i < Lin; i++){
        numerador[i] = 0;
        denominador[i] = 0;
	}	
	
	//Separaï¿½ï¿½o da diagonal dos valores
	for(i = 0; i < Lin; i++){
		for(c = 0; c < Col; c++){
			if(i == c){
				denominador[i] = MatrizAb[i][c]; //Separaï¿½ï¿½o da diagonal dos valores
			}
			else {		
				numerador[i] += MatrizAb[i][c]; //Soma dos valores fora da diagonal
			}
		}
	}
	
	float convergencia_l[i], convergencia_c[i];

	//Divisï¿½o
	for(i = 0; i < Lin; i++){
		convergencia_l[i] = numerador[i]/denominador[i];
	}
	
	for(a = 0; a < Lin; a++) {
		if(convergencia_l[a] >= 1){
		
			//Metodo Coluna
			
			//Limpa
			for(i = 0; i < Lin; i++){
				numerador[i] = 0;
				denominador[i] = 0;
			}	
			
			for(i = 0; i < Lin; i++){
				for(c = 0; c < Col; c++){
					if(i == c){
						denominador[i] = MatrizAb[c][i]; //Separaï¿½ï¿½o da diagonal dos valores
					}
					else {		
						numerador[i] += MatrizAb[c][i]; //Soma dos valores fora da diagonal
					}
				}
			}
			
			for(i = 0; i < Lin; i++){
				convergencia_c[i] = numerador[i]/denominador[i];
				if (convergencia_c[i] >= 1){
					printf("\nConvergencia nao garantida.\n");
					return 0;
				}
			}
		}
	}
	
	printf("\nConvergencia garantida.\n");

}

float realizarSolucao(int km, float e, int Col, int Lin, float **Matriz, float *Inicial, float *Termos){
	
	int parar = 0, k = 0, i = 0, c = 0;
	float numerador_r[Col], denominador_r[Col], resultado_r[Col], denominador_f, numerador_f, parada;
	
	do{
		printf ("\nInteracao %d\n", k);
		
		for(i = 0; i < Lin; i++){
			numerador_r[i] = 0;
			denominador_r[i] = 0;
			resultado_r[i] = 0;
			numerador_f = 0;
			denominador_f = 0;
		}
	
		//Formula interativa
		for(i = 0; i < Lin; i++){
			for(c = 0; c < Col; c++){
				if(i == c){
					denominador_r[i] = Matriz[i][c];
				}
				else {		
					numerador_r[i] -= (Matriz[i][c]*Inicial[c]); //Inserï¿½ï¿½o dos termos iniciais no sistema
				}
			}
		}
        
		for(i = 0; i < Lin; i++){
			resultado_r[i] = (numerador_r[i] + Termos[i])/denominador_r[i]; //Resultado da interaï¿½ï¿½o
			numerador_r[i] = resultado_r[i];
			float aux =  sqrt(pow(resultado_r[i] - Inicial[i],2 ));
            if(i == 0 || aux > numerador_f){
                numerador_f =  aux;
            }
            
            printf("%.4f\n", numerador_r[i]);

			Inicial[i] = numerador_r[i];
			if (denominador_f < fabs(Inicial[i])) denominador_f = fabs(Inicial[i]);
			
		}	
		parada = fabs(numerador_f/denominador_f);
		printf ("\nParada = [%.4f]", parada);
		printf ("\n----------------------\n");	
	
		k++;
		
		if (k == km || parada <= e){
			parar = 1;
		}
	}while (parar != 1);
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
    
    // Popular matriz solucÃ£o intermediaria
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
    
    // calcular vetor de soluÃ§Ã£o
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


// Rotina 9
int CriterioSassenfeld(int ordem, float** matriz)
{

    float B[ordem], resultado[ordem];
    int i, j;
    float soma = 0;

    for (j = 1; j < ordem; j++)
    {
        soma += fabs(matriz[0][j]);
    }

    B[0] = soma / matriz[0][0];

    for (i = 1; i < ordem; i++)
    {
        soma = 0;
        for (j = 0; j < ordem; j++)
        {
            if (j != i)
            {
                if (j < i)
                {
                    soma += (float) fabs(matriz[i][j]) * B[j];
                }
                else
                {
                    soma += (float) fabs(matriz[i][j]);
                }
            }
        }
        B[i] = soma / matriz[i][i];
    }

    float maiorB = 0;

    for (i = 0; i < ordem; i++)
    {
        if ((float) fabs(B[i]) > maiorB)
        {
            maiorB = B[i];
        }
    }

    if (maiorB < 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void GaussSeidel()
{
    int ordem;
    int i, j, maxIteracao;
    float precisao;
    int continua=1, iteracoes = 0;



    getMatrixSimetricSize(&ordem);
    float** matriz = (float **)malloc(ordem * sizeof(float *));
    createMatrix(matriz, ordem, ordem);
    scanfMatrix(ordem, ordem, matriz);
    printMatrix(matriz, ordem, ordem);
    float *termosInd = (float*) malloc(ordem * sizeof(float*));
    createVetor(termosInd, ordem);
    scanfVector(ordem,termosInd);

    float matrizAnterior[ordem];
    float aproxSolucao[ordem];

    printf("\nInsira os termos de aproximação inicial para solução: \n");

    for (i = 0; i < ordem; i++)
    {
        printf("[%d]: ", i);
        scanf("%f", &aproxSolucao[i]);
    }


    printf("\nInsira o valor da precisão: ");
    scanf("%f",&precisao);
    printf("\nInsira o valor máximo de iterações: ");
    scanf("%d",&maxIteracao);

    if (CriterioSassenfeld(ordem, matriz) == 0 && CriterioLinhas(ordem, matriz) == 0)
    {
        printf("\n\nA matriz inserida não cumpre nenhum critério que garante convergência\n\n");
        continua = 0;
    }

    if (continua!=0){
        do
        {
            iteracoes++;

            for (i = 0; i < ordem; i++)
            {
                matrizAnterior[i] = aproxSolucao[i];
            }

            for (i = 0; i < ordem; i++)
            {
                float resultado = 0;
                for (j = 0; j < ordem; j++)
                {
                    if (j != i)
                    {
                        resultado += matriz[i][j] * aproxSolucao[j];
                    }
                }
                aproxSolucao[i] = ((termosInd[i] - resultado) / matriz[i][i]);
            }

            float maioraproxSolucao = 0;

            //pega o maior
            for (i = 0; i < ordem; i++)
            {
                if (fabs(aproxSolucao[i]) > maioraproxSolucao)
                {
                    maioraproxSolucao = aproxSolucao[i];
                }
            }

            float CP[ordem];

            for (i = 0; i < ordem; i++)
            {
                CP[i] = fabs(aproxSolucao[i] - matrizAnterior[i]) / maioraproxSolucao;
            }

            float maiorCP = 0;
            for (i = 0; i < ordem; i++)
            {
                if (fabs(CP[i]) > maiorCP)
                {
                    maiorCP = CP[i];
                }
            }

            if (maiorCP > precisao)
            {
                continua = 1;
            }
            else
            {
                continua = 0;
            }
        } while (continua == 1 && iteracoes <= maxIteracao);

        printf("\n\nNúmero de iterações: %d\n\n", iteracoes);
        printf("Vetor solução: ");
        for (i = 0; i < ordem; i++)
        {
            printf("%f     ", aproxSolucao[i]);
        }
    }

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
        float* vetorInversaAux = (float*)malloc((systemOrder) * sizeof(float *));
        clearVector(vetorInversaAux, systemOrder);
        
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
    SistemaTrianguloInferior();
}

void op3() {
    SistemaTrianguloSuperior();
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
    createMatrix(matriz, ordem, ordem);

    float *vetorIndependente = (float*) malloc(ordem * sizeof(float*));
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
    int matrixSize;
    getMatrixSimetricSize(&matrixSize);
    
    float** matrix = (float **)malloc(matrixSize * sizeof(float *));
    createMatrix(matrix, matrixSize, matrixSize);
    scanfMatrix(matrixSize, matrixSize, matrix);
    printMatrix(matrix, matrixSize, matrixSize);
    
    float * vectorIndepent = (float*)malloc((matrixSize) * sizeof(float));
    clearVector(vectorIndepent, matrixSize);
    scanfVector(matrixSize, vectorIndepent);
    printVector(vectorIndepent, matrixSize);

    float * solutionVector = (float*)malloc((matrixSize) * sizeof(float));
    clearVector(solutionVector, matrixSize);


    GaussCompacto(matrixSize, matrix, vectorIndepent, solutionVector);
    
    printVector(solutionVector, matrixSize);
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
    int Lin, Col, i, c, km;
	float e;
	float Termos[i]; //Valores do termo
	float Inicial[i]; //Suposiï¿½ï¿½o inicial
	
	//Ordem
	printf("Definir quantidade de linhas.\n");
	scanf("%d", &Lin);
	printf("Definir quantidade de colunas.\n");
	scanf("%d", &Col);
	
	float **Matriz = (float**) malloc(Lin * sizeof(float*));
    createMatrix(Matriz, Lin, Col);
    
	//Inclusï¿½o dos valores na matriz
	for(i = 0; i < Lin; i++){
		for(c = 0; c < Col; c++){
			printf ("\nElemento[%d][%d] = ", i, c);
			scanf("%f", &Matriz[i][c]);
		}
	}
	
	printf("\nQual precisao desejada?\n");
	scanf("%f", &e);
	
	
	printf("Defina o limite de interacoes\n");
	scanf("%d", &km);
	
	//Inclusï¿½o dos "termos parciais"
	printf("\nInserir os Termos\n");
	for(i = 0; i < Lin; i++){
		scanf("%f", &Termos[i]); 
		printf ("\nValor = [%.4f]\n", Termos[i]);
	}
	
	//Inclusï¿½o dos termos iniciais
	printf("\nInserir os Termos Iniciais\n");
	for(i = 0; i < Lin; i++){
		scanf("%f", &Inicial[i]);
		printf ("\nValor = [%.4f]\n", Inicial[i]);
	}
	
	validarConvergencia(Lin, Col, Matriz);
	realizarSolucao(km, e, Col, Lin, Matriz, Inicial, Termos);
}
void op9() {
    GaussSeidel();
}
void op10() {
    int matrixSize;
    getMatrixSimetricSize(&matrixSize);
    printf("%i\n\n", matrixSize);
    
    float** matrix = (float **)malloc(matrixSize * sizeof(float *));
    createMatrix(matrix, matrixSize, matrixSize);
    scanfMatrix(matrixSize, matrixSize, matrix);
    printMatrix(matrix, matrixSize, matrixSize);


    float** matrixInverse = (float **)malloc(matrixSize * sizeof(float *));
    createMatrix(matrixInverse, matrixSize, matrixSize);
    
    MatrizInversa(matrixSize, matrix, matrixInverse);
    printf("\n\n");
    printMatrixWithName(matrixInverse, matrixSize, matrixSize, "M-1");
}

void menu() {
    printf("\n--------- MENU ---------");
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
    int op;
    do{
        menu();
        printf("\n\nDigite sua opcao: ");
        scanf("%d", &op);
        while(op < 1 || op > 11) {
            printf("Opcao invalida! Redigite: ");
            scanf("%d", &op);
        }
        printf("\nOp: %i\n", op);

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

        printf("\nDeseja realizar outra acao?\n");
        printf("\n01 - Sim");
        printf("\n02 - Nao");

        scanf("%d", &op);
        
    }while(op == 1);
}