#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // sleep
#include <errno.h>      // errno
#include <pthread.h>    // compile with -pthread
#include <time.h>

pthread_barrier_t barrier_startLine;

void *car(void *car_number){

    printf("Car %d is fueling...\n", *(int *)car_number);
    sleep(rand() % 10);
    printf("Car %d is fulled! Waiting for others...\n", *(int *)car_number);
    pthread_barrier_wait(&barrier_startLine);
}

#define CAR_NUM 10

int main(void){

    srand(time(NULL));

    pthread_barrier_init(&barrier_startLine, NULL, CAR_NUM);

    pthread_t thread_cars[CAR_NUM];
    int i;
    int *car_numbers = (int *)malloc(sizeof(int ) * CAR_NUM);
    for(i = 0; i < CAR_NUM; i++)
        car_numbers[i] = i;
    for(i = 0; i < CAR_NUM; i++)
        if(pthread_create(&thread_cars[i], NULL, &car, (void *)&car_numbers[i]))
            printf("Error : %d\n", errno);

    for(i = 0; i < CAR_NUM; i++)
        if(pthread_join(thread_cars[i], NULL))
            printf("Error : %d\n", errno);

    printf("All %d cars have been fuelled! Start the race!\n", CAR_NUM);

    return 0;
}