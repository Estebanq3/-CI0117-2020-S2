#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct { //Memoria compartida
    pthread_mutex_t* mutexes;
    size_t totalThreads;
} shared_data_t;

typedef struct { //Datos de cada hilo
    size_t thread_num;
    shared_data_t* shared_data;

} thread_data_t;


void* helloWorld(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_data_t* shared_data = data->shared_data;

    pthread_mutex_lock(&(shared_data->mutexes[thread_num]));
    printf("Hello world from thread number # %zu.\n", thread_num);
    pthread_mutex_unlock(&(shared_data->mutexes[(thread_num+1)%shared_data->totalThreads]));
    
    return NULL;
}


int main(int argc, char* arg[]) {
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC,&before);

    size_t thread_count = 0;

    if (argc >= 2) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }



    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));
    shared_data_t* shared_data = malloc(sizeof(shared_data_t));
    shared_data->mutexes = malloc(thread_count*sizeof(pthread_mutex_t));

    
    

    //***DATOS
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));
    shared_data->totalThreads = thread_count;

    

    for(int i = 0; i < thread_count; ++i){
       pthread_mutex_init(&(shared_data->mutexes[i]),NULL);
    }

    for(int i = 1; i < thread_count; ++i){
       pthread_mutex_lock(&(shared_data->mutexes[i]));
    }

    for (size_t i = 0; i < thread_count; ++i) {
        thread_data_list[i].thread_num = i;
        thread_data_list[i].shared_data = shared_data;
        pthread_create(&threads[i], NULL, helloWorld, (void*)&thread_data_list[i]);
    }

    
    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Hello world from main thread\n");
    
    
    free(threads);
    free(shared_data);
    free(thread_data_list);

    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC,&after);

    printf("%ld sec, %ld nanoseconds before\n", before.tv_sec, before.tv_nsec);
    printf("%ld sec, %ld nanoseconds before\n", after.tv_sec, after.tv_nsec);
    printf("%ld sec, %ld nanoseconds elapsed\n", after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);
    double seconds = after.tv_nsec-before.tv_nsec;
    seconds = seconds/100000000;
    printf("Tiempo de ejecuciòn fue de: %f\n ", seconds);

    return 0;
}