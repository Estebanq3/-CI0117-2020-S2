#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


typedef struct timespec walltime_t;


typedef struct {
    float b,a,n,delta,sumatoria, sumas_parciales; //b limite superior, a limite inferior, n numero de rectàngulos, delta (b-a)/n, sumatoria general y sumas parciales
    int rectxhilo; // cantidad de rectàngulos por hilo
    pthread_mutex_t mutex; //mutex de la zona crìtica
} shared_data_t;

typedef struct {
    float limiteInf,limiteSup; //limite superior e inferior correspondiente a cada hilo.
    shared_data_t * shared_data;
} thread_data_t;

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

//Funcion asignada en el enunciado (x*x)+1
float function(float x){
    return (x*x) + 1;
}

//Càlculo de las àreas de cada rectàngulo correspondiente a cada hilo, mediante la fòrmula.
void * riemman_sum(void * args){
    thread_data_t* data = (thread_data_t*) args;
    shared_data_t* shared_data = data->shared_data; 
    float sumas_parciales; //almacena las àreas parciales
    for (float i = data->limiteInf; i < data->limiteSup && i < shared_data->b; i = i + shared_data->delta){
        //mutex de la zona crìtica
        pthread_mutex_lock(&shared_data->mutex);
        sumas_parciales += function(i) * shared_data->delta;
        pthread_mutex_unlock(&shared_data->mutex);            
    }
    //mutex de zona crìtica
    pthread_mutex_lock(&shared_data->mutex);
    shared_data->sumatoria += sumas_parciales; 
    pthread_mutex_unlock(&shared_data->mutex);    
    return NULL;
}    

int main(int argc, char * argv[]){
    walltime_t* walltime = (walltime_t*)calloc(1, sizeof (walltime_t));
    walltime_start(walltime);
    size_t thread_count = 0;
    //si no se insertan 5 paràmetros entonces se termina el programa
    if (argc != 5){
        return 1;
    }
    shared_data_t* shared_data = (shared_data_t*)calloc(1, sizeof(shared_data_t));
    //VARIABLES
    shared_data->b = (float)strtoul(argv[1], NULL, 10);
    shared_data->a = (float)strtoul(argv[2], NULL, 10);
    shared_data->n = (float)strtoul(argv[3], NULL, 10);
    thread_count = (size_t)strtoul(argv[4], NULL, 10);
    shared_data->delta = (shared_data->b - shared_data->a) / shared_data->n;
    printf("b: %F\na: %F\nn: %f\n", shared_data->b, shared_data->a, shared_data->n); //imprimimos datos digitados por usuario
    //Rectàngulos por hilo
    shared_data->rectxhilo = shared_data->n / ((float) thread_count);
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));
    pthread_mutex_init(&shared_data->mutex, NULL);
    for (size_t i = 0; i < thread_count; ++i){
        thread_data_list[i].limiteInf = shared_data->a;
        thread_data_list[i].limiteSup = shared_data->a + (shared_data->rectxhilo * shared_data->delta);
        thread_data_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, riemman_sum, (void*)&thread_data_list[i]);
        shared_data->a = shared_data->a + (shared_data->rectxhilo * shared_data->delta);
    }
    for (size_t i = 0; i < thread_count; ++i){
        pthread_join(threads[i],NULL);
    }
    double time = walltime_elapsed(walltime);
    printf("La suma de riemann es: %f\n", shared_data->sumatoria);
    printf("El tiempo empleado es de: %f\n", time);

    pthread_mutex_destroy(&shared_data->mutex);
    free(thread_data_list);
    free(threads);
    free(shared_data);
    
    return 0;
}