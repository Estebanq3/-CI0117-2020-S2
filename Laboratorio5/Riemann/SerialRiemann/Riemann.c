//Sumas de Riemann
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct timespec walltime_t;
void walltime_start(walltime_t* start){
    clock_gettime(CLOCK_MONOTONIC, start);
}

double walltime_elapsed(const walltime_t* start){
    walltime_t finish;
    clock_gettime(CLOCK_MONOTONIC, &finish);

    double elapsed = (finish.tv_sec - start->tv_sec);
    elapsed += (finish.tv_nsec - start->tv_nsec) / 1000000000.0;

    return elapsed;
}

int main(int argc, char* arg[]){
	walltime_t* walltime = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_start(walltime);

	if(argc != 4){ //Sino se introducen 4 paràmetros el programa se sale 1
		fprintf(stderr, "Error, numero ivalido de parametros\n");
        return 1;
	}

	//VARIABLES
	float b = (float)strtoul(arg[1], NULL, 10); //limite superior
	float a = (float)strtoul(arg[2], NULL, 10); //limite inferior
	int n = (int)strtoul(arg[3], NULL, 10); //número de rectángulos

	int contador;
	float delta;
	float sumatoria;
	float x;
	float function;
	
	printf("b: %F\na: %F\nn: %d\n", b, a, n); //imprimimos datos digitados por usuario

	//INICIO DE OPERACIONES
	sumatoria = 0;
	contador = 0;
	delta = (b-a) / n; //calculamos delta x
	
	while(contador <= n){
		x = (delta*contador+a);
		function = (x*x)+1; //funcion (x*x)+1
		sumatoria = sumatoria + (function); //aqui vamos almacenando la sumatoria de los rectangulos
		contador++;
	}

	sumatoria = sumatoria* delta; //Obtenemos el resultado de la sumatoria final
	double time = walltime_elapsed(walltime);


	printf( "El resultado de las sumas de Riemann es: %F\n", sumatoria );
	printf( "El tiempo fue de: %F\n", time );

return 0;

}