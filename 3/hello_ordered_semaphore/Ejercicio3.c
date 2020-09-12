#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct { //Memoria compartida
    size_t totalThreads;
    sem_t* semaphores;
} shared_data_t;

typedef struct { //Datos de cada hilo
    size_t thread_num;
    shared_data_t* shared_data;

} thread_data_t;


void* helloWorld(void* args) {

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_data_t* shared_data = data->shared_data;

    sem_wait(&(shared_data->semaphores[thread_num]));
    printf("Hello world from thread number # %zu.\n", thread_num);
    sem_post(&(shared_data->semaphores[(thread_num+1)%shared_data->totalThreads]));
    
    
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
    shared_data->semaphores = malloc(thread_count*sizeof(sem_t));
    
   
    //DATOS
    shared_data->totalThreads = thread_count;
    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));



    for(int i = 0; i < thread_count; ++i){
       sem_init(&(shared_data->semaphores[i]),0,1);
    }

    for(int i = 1; i < thread_count; ++i){
       sem_wait(&(shared_data->semaphores[i]));
    }


    //se queda igual
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