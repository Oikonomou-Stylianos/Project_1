#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      // errno
#include <pthread.h>    // compile with -pthread

// gcc -pthread -o mutex mutex.c
// ./mutex

int static_value = 0;
pthread_mutex_t mutex;


void *routine(){

    int i;
    for(i = 0; i < 1000000; i++){
     
        pthread_mutex_lock(&mutex);     // comment this line to see the unwanted behavior
        static_value++;
        pthread_mutex_unlock(&mutex);
    }
}

#define THREAD_NUM 2

int main(void){

    pthread_t *threads;
    threads = (pthread_t *)malloc(sizeof(pthread_t ) * THREAD_NUM);
    pthread_mutex_init(& , NULL);

    int i;
    for(i = 0; i < THREAD_NUM; i++){

        if(pthread_create(&threads[i], NULL, &routine, NULL))
            printf("Error : %d\n", errno);
    }

    for(i = 0; i < THREAD_NUM; i++){

        if(pthread_join(threads[i], NULL))
            printf("Error : %d\n", errno);
    }

    printf("Static value = %d\n", static_value);

    pthread_mutex_destroy(&mutex);  // unlock the mutex before destroying it
    free(threads);
    return 0;
}