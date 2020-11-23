#include <cstdio>
#include <cstdlib>
#include <mkl.h>


/*
1. Definir una matriz (A) y dos vectores (x, y) y realizar las siguientes
operaciones:
a) A*x
b) 3*A*x+4*y
2. Probar el efecto de los parámetros de layout y trasposición en el ejercicio
anterior.
3. [OPTATIVO] Probar el efecto de los parámetros de incremento y lda en el
ejercicio anterior.


cblas_dgemv ( const CBLAS_LAYOUT layout,
const CBLAS_TRANSPOSE TransA,
const int M, const int N,
const double alpha, const double * A, const int lda,
const double * X, const int incX,
const double beta,double * Y, const int incY )

y := alpha*A*x + beta*y
y := alpha*A**T*x + beta*y
*/

double* random(const int size) {
	double v[4];
	for (int i = 0; i < size; i++) {
		v[i] = (rand() % 10) + 1;
	}
	return v;
}

void showMatrix(double* m, int len) {
	printf("{");
	for (int i = 0; i < len; i++) {
		printf("%2.2f ", m[i]);
	}
	printf("} \n");
}

int main(int argc, char* argv[]) {
	double A[] = {4.0, 1.5, 3.0, 7.0, 6.5, 8.5, 2.5, 3.5, 5.0 };
	double x[] = {1.0, 2.5, 8.5};
	double y[] = {3.0, 5.0, 8.0};
	//a) A*x
	cblas_dgemv(CblasRowMajor, CblasNoTrans, 3, 3, 1, A, 3, x, 1, 0, y, 1);
	printf("A*x:\n");
	showMatrix(y, 3);
	//b) 3*A*x+4*y
	double Y[] = { 3.0, 5.0, 8.0 };
	printf("\n3*A*x + 4*y:\n");
	cblas_dgemv(CblasRowMajor, CblasNoTrans, 3, 3, 3, A, 3, x, 1, 4, Y, 1);
	showMatrix(Y, 3);
	//Probar el efecto de los parámetros de layout y trasposición en el ejercicio anterior.
	printf("\nEstablecemos el parametro de la matriz Transpuesta: CblasTrans\n");
	double res[] = {3.0, 5.0, 8.0};
	cblas_dgemv(CblasRowMajor, CblasTrans, 3, 3, 3, A, 3, x, 1, 4,res, 1);
	showMatrix(res,3);
	printf("\nEstablecemos el parametro del Layout: CblasColMajor\n");
	double res1[] = { 3.0, 5.0, 8.0 };
	cblas_dgemv(CblasColMajor, CblasNoTrans, 3, 3, 3, A, 3, x, 1, 4, res1, 1);
	showMatrix(res1, 3);
	//[OPTATIVO] Probar el efecto de los parámetros de incremento y lda en el ejercicio anterior
	std::getchar();
	return 0;
}