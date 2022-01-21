#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      // errno
#include <pthread.h>    // compile with -pthread
#include <unistd.h>

// gcc -pthread -o condvar condvar.c
// ./condvar

int fuel = 0;
pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel, cond_wait_fuel;

void *filling_fuel(void *arg){

    int i;
    for(i = 0; i < 100; i++){

        sleep(1);
        pthread_mutex_lock(&mutex_fuel);
        fuel += 15;
        printf("Filling fuel... %d\n", fuel);
        fflush(stdout);
        pthread_mutex_unlock(&mutex_fuel);
        pthread_cond_broadcast(&cond_fuel);
        pthread_cond_wait(&cond_wait_fuel, )
    }
}

void *car(void *arg){

    pthread_mutex_lock(&mutex_fuel);
    while(fuel < 40){
        printf("Not enough fuel. Waiting...\n");
        fflush(stdout);
        pthread_cond_wait(&cond_fuel, &mutex_fuel);     // wait must be inside a while loop
        // unlock mutex
        // wait for signal
        // lock mutex
    }
    fuel -= 40;
    printf("Car running... Fuel left %d\n", fuel);
    pthread_mutex_unlock(&mutex_fuel);
}

#define THREAD_NUM 6

int main(void){

    pthread_t *threads;
    threads = (pthread_t *)malloc(sizeof(pthread_t ) * THREAD_NUM);
    pthread_mutex_init(&mutex_fuel, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    pthread_cond_init(&cond_wait_fuel, NULL);

    int i;
    for(i = 0; i < THREAD_NUM-1; i++){

        if(pthread_create(&threads[i], NULL, &car, NULL))
            printf("Error : %d\n", errno);
    }
    if(pthread_create(&threads[THREAD_NUM-1], NULL, &filling_fuel, NULL))
        printf("Error : %d\n", errno);

    for(i = 0; i < THREAD_NUM; i++){

        if(pthread_join(threads[i], NULL) != 0)
            printf("Error : %d\n", errno);
    }

    pthread_mutex_destroy(&mutex_fuel);  // unlock the mutex before destroying it
    pthread_cond_destroy(&cond_fuel);
    free(threads);
    return 0;
}