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
	printf("\nTiempo total para valor N = %i: %lf seg\n", N,(fin - inicio));
	printf("Tiempo promedio entre 100 para valor N = %i: %lf seg\n", N, ((fin - inicio))/100);
	return (fin - inicio);

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
	printf("\nTiempo total para valor N = %i: %lf seg\n", N, (fin - inicio));
	printf("Tiempo promedio entre 100 para valor N = %i: %lf seg\n", N, ((fin - inicio)) / 100);
	return (fin - inicio);
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
	using namespace std;
	ofstream fileD, fileFlops;
	fileD.open("fileDouble.txt");
	fileFlops.open("fileFlops.txt");
	for (int i = 100; i <= 700; i += 20) {
		double t = calculateProm(i);
		fileD << t << std::endl;
		fileFlops << (100/t)*pow(10,-8) << std::endl;
		printf("GFlops para matriz %ix%i: %lf\n", i,i, (100 / t) * pow(10, -8));
	}
	fileD.close();
	fileFlops.close();


	//[OPTATIVO] Realizar pruebas con aritmética de precisión simple.
	printf("\n Pruebas con aritmética de precicsión simple:\n");
	ofstream fileF, fileFflops;
	fileF.open("fileFloat.txt");
	fileFflops.open("fileFflops.txt");
	for (int i = 100; i <= 700; i += 20){
		double t = calculateFloat(i);
		fileF << t << std::endl;
		fileFflops << (100 / t) * pow(10, -8) << std::endl;
		printf("GFlops para matriz %ix%i: %lf\n", i, i, (100 / t) * pow(10, -8));
	}
	fileF.close();
	fileFlops.close();
	std::getchar();
	return 0;
}