#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <mkl.h>

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
	double* matrix = (double*)mkl_malloc(N * N * sizeof(double), 64);
	for (int i = 0; i < N; i++) {
		matrix[i] = (double)rand() / (double)10;
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

void calculateProm(int N, double* A, double* B, double* C) {
	double fin, inicio = dsecnd(); // Inicializacón falsa
	inicio = dsecnd(); //Inicio de cronometraje
	for (int i = 0; i < 100; i++) {
		A = randMat(N * N);
		B = randMat(N * N);
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1, A, N, B, N, 0, C, N);
	}
	fin = dsecnd(); //Fin de cronometraje
	printf("Tiempo total para valor N = %i: %lf ms\n", N,(fin - inicio) * 1.0e3);
	printf("Tiempo promedio entre 100 para valor N = %i: %lf ms\n", N, ((fin - inicio) * 1.0e3)/100);

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

	showMatrix(A,9);
	showMatrix(B,9);
	showMatrix(C,9);

	//2. Calcular el número de GFLOPS para distintos valores de N, realizando el promedio de 100 ejecuciones de la operación A * B
	//Valor N=3, N=5, N=7, N=9
	calculateProm(3,A,B,C);
	calculateProm(5,A,B,C);
	calculateProm(7,A,B,C);
	calculateProm(9,A,B,C);
	std::getchar();
	mkl_free(A);
	mkl_free(B);
	mkl_free(C);
	return 0;
}