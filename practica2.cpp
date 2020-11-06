#include <cstdio>
#include <cstdlib>
#include <mkl.h>

void product_scale(double v1[] , double v2[]) {
	double res = cblas_ddot(3, v1, 0, v2, 0);
	printf("Producto escalar: %d\n", res);

}
/*
Construir dos vectores conteniendo el valor ASCII los 10 primeros
caracteres de tu nombre (vN) y de tu apellido (vA), completando con 0 si
es necesario. Obtener el resultado de sumar al primer vector el triple del
segundo y mostrar el resultado mapeado a caracteres ‘a…z’
*/

double *sumASCII(char name[], char last[]) {
	double nameAscii[10];
	double lastAscii[10];
	for (int i = 0; i < 10; i++) {
		nameAscii[i] = double(name[i]);
		lastAscii[i] = double(last[i]);
		//printf("%.0f\n",lastAscii[i]);
	}
	printf("\n");
	cblas_daxpy(10,3,nameAscii,1,lastAscii,1); 
	for (int i = 0; i < 10; i++) {
		printf("%c", ((int(lastAscii[i]) % 25) + 97));
	}
	return lastAscii;

}

int main(int argc, char* argv[]) {
	double v1[3] = { 1.0, 0.0, 0.0 };
	double v2[3] = { 0.0, 0.0, 1.0 };
	product_scale(v1,v2);
	char nombre[11] = {"EduardoAle"};
	char apellido[11] = {"GarciaSosa"};
	sumASCII(nombre, apellido);
	std::getchar();
	return 0;
}