#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void* funcionVacia(void* args){
    //funciòn vacìa del hilo secundario
    return NULL; //no retornamos nada

}


int main(int argc, char* arg[]) {

    size_t T = 0;
    int min_tiempo = 0;

    if (argc >= 1) {
        T = (size_t)strtoul(arg[1], NULL, 10);
    } else {
        T = 1;
    }

    pthread_t* threads = malloc((size_t)T * sizeof(pthread_t)); //solicito memoria para los threads T que tengo que crear

    for (size_t i = 0; i < T; ++i) {
        int auxtime = 0;
        struct timespec before;
        clock_gettime(CLOCK_MONOTONIC,&before);
        pthread_create(&threads[i], NULL, funcionVacia, NULL);
        pthread_join(threads[i], NULL);
        struct timespec after;
        clock_gettime(CLOCK_MONOTONIC,&after);

        printf("%ld sec, %ld nanoseconds before\n", before.tv_sec, before.tv_nsec);
        printf("%ld sec, %ld nanoseconds before\n", after.tv_sec, after.tv_nsec);
        printf("%ld sec, %ld nanoseconds elapsed\n", after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);
        
        auxtime = (after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);
        printf("Aux time:%d\n", auxtime);
        if( min_tiempo == 0){
            min_tiempo = auxtime;
        }else{
            if( min_tiempo > auxtime){
                min_tiempo = auxtime;
            }
        }
        
    }

    double seconds = min_tiempo;
    seconds = seconds/ 100000000;

    
    printf("Minimum thread creation and destruction time(seconds) was: %f ", seconds);
    printf("Out of a total of trials: %ld\n", T);

    
    
    return 0;
}