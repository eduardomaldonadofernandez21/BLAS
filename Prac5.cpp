#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <mkl.h>
#include <iostream>
#include <fstream>

/*
1. Crear tres matrices (A, B y C) de dimensión NxN y rellenarlas con valores
aleatorios.
2. Calcular el número de GFLOPS para distintos valores de N, realizando el
promedio de 100 ejecuciones de la operación A*B.
3. Repetir las pruebas utilizando el modo Parallel y comparar los resultados.
4. [OPTATIVO] Realizar pruebas con aritmética de precisión simple.
5. [OPTATIVO] Probar el efecto de los parámetros lda, ldb y ldc.
*/

double* randMat(int N) {
	double* matrix = (double*)mkl_malloc(N*sizeof(double), 64);
	if (matrix == NULL) { perror("Errror malloc"); exit(1); }
	for (int i = 0; i < N; i++) {
		matrix[i] = (double)rand() / (double)10;
	}
	return matrix;
}

float* randMatfloat(int N) {
	float* matrix = (float*)mkl_malloc(N*sizeof(float), 32);
	if (matrix == NULL) { perror("Errror malloc"); exit(1); }
	for (int i = 0; i < N; i++) {
		matrix[i] = (float)rand() / (float)10;
	}
	return matrix;
}

void showMatrix(double* m, int len) {
	printf("{");
	for (int i = 0; i < len; i++) {
		printf("%0.f ", m[i]);
	}
	printf("} \n");
}

double calculateProm(int N) {
	double fin, inicio = dsecnd(); // Inicializacón falsa
	double* A = randMat(N*N);
	double* B = randMat(N*N);
	double* C = randMat(N*N);
	inicio = dsecnd(); //Inicio de cronometraje
	for (int i = 0; i < 100; i++) {
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, N, B, N, 0, C, N);
	}
	fin = dsecnd(); //Fin de cronometraje
	mkl_free(A);
	mkl_free(B);
	mkl_free(C);
	printf("\nTiempo total para valor N = %i: %lf seg\n", N,(fin - inicio) * 1.0e3);
	printf("Tiempo promedio entre 100 para valor N = %i: %lf seg\n", N, ((fin - inicio) * 1.0e3)/100);
	return fin;

}

double calculateFloat(int N) {
	double fin, inicio = dsecnd(); // Inicializacón falsa
	float* fa = randMatfloat(N * N);
	float* fb = randMatfloat(N * N);
	float* fc = randMatfloat(N * N);
	inicio = dsecnd(); //Inicio de cronometraje
	for (int i = 0; i < 100; i++) {
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, fa, N, fb, N, 0, fc, N);
	}
	fin = dsecnd(); //Fin de cronometraje
	mkl_free(fa);
	mkl_free(fb);
	mkl_free(fc);
	printf("\nTiempo total para valor N = %i: %lf seg\n", N, (fin - inicio) * 1.0e3);
	printf("Tiempo promedio entre 100 para valor N = %i: %lf seg\n", N, ((fin - inicio) * 1.0e3) / 100);
	return fin;
}

int randomLen() {
	return rand() % 10 + 1;
}


int main(int argc, char* argv[]) {
	//1. Crear tres matrices (A, B y C) de dimensión NxN y rellenarlas con valores aleatorios.
	srand((unsigned int)time(0));
	double* A = randMat(9);
	double* B = randMat(9);
	double* C = randMat(9);

	showMatrix(A, 9);
	showMatrix(B, 9);
	showMatrix(C, 9);

	//2. Calcular el número de GFLOPS para distintos valores de N, realizando el promedio de 100 ejecuciones de la operación A * B
	//Valor N=3, N=5, N=7, N=9
	using namespace std;
	ofstream fileD;
	fileD.open("fileDouble.txt");
	for (int i = 100; i <= 500; i += 20) {
		fileD << calculateProm(i);
	}
	fileD.close();
	//[OPTATIVO] Realizar pruebas con aritmética de precisión simple.
	printf("\n Pruebas con aritmética de precicsión simple:\n");
	ofstream fileF;
	fileF.open("fileFloat.txt");
	for (int i = 100; i <= 500; i += 20){
		fileF << calculateFloat(i);
	}
	fileF.close();
	std::getchar();
	return 0;
}