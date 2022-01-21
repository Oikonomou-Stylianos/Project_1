#include <stdio.h>
#include <stdlib.h>
#include <errno.h>      // errno
#include <pthread.h>    // compile with -pthread
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define USERS 100
#define MAX_LOGGED_USERS 4

sem_t semaphore;

void *routine(void *num){

    printf("[%2d] Waiting in the login queue\n", *(int *)num);
    sem_wait(&semaphore);
    printf("[%2d] Logged in\n", *(int *)num);
    sleep(rand() % 5 + 1);
    printf("[%2d] Logged out\n", *(int *)num);
    sem_post(&semaphore);

    int val;
    sem_getvalue(&semaphore, &val); 
    printf("Sem = %d\n", val);

    free(num);
}

int main(void){

    srand(time(NULL));
    sem_init(&semaphore, 0, MAX_LOGGED_USERS);

    pthread_t *threads;
    threads = (pthread_t *)malloc(sizeof(pthread_t ) * USERS);
    int i, *num;
    for(i = 0; i < USERS; i++){

        num = (int *)malloc(sizeof(int ));
        *num = i;
        if(pthread_create(&threads[i], NULL, &routine, (void *)num))
            printf("Error : %d\n", errno);
    }
    

    for(i = 0; i < USERS; i++){

        if(pthread_join(threads[i], NULL))
            printf("Error : %d\n", errno);
    }
    

    return 0;
}