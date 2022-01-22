#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // sleep
#include <math.h>       // pow, compile with -lm at the end 
#include <errno.h>      // errno
#include <pthread.h>    // compile with -pthread

// gcc -pthread -o createjoin createjoin.c -lm
// ./createjoin

void *routine(void *number){

    printf("Printing from thread %d\n", *(int *)number);
    sleep(3);
    printf("Exiting thread %d\n", *(int *)number);

    int *poweroftwo = (int *)malloc(sizeof(int ));      // threads return pointers so their values have to be allocated in the heap and deallocated from caller function
    *poweroftwo = (int )pow((double )(*(int *)number), 2);

    return (void *)poweroftwo;
}

#define THREAD_NUM 10

int main(void){

    pthread_t *threads;
    threads = (pthread_t *)malloc(sizeof(pthread_t ) * THREAD_NUM);

    int i, *arguments, **return_values;
    arguments = (int *)malloc(sizeof(int ) * THREAD_NUM);
    return_values = (int **)malloc(sizeof(int *) * THREAD_NUM);
    
    for(i = 0; i < THREAD_NUM; i++){

        arguments[i] = i;
        if(pthread_create(&threads[i], NULL, &routine, (void *)&arguments[i]))
            printf("Error : %d\n", errno);
        printf("pthread_t = %ld\n", threads[i]);
    }

    for(i = 0; i < THREAD_NUM; i++){

        if(pthread_join(threads[i], (void *)&return_values[i]))     // join the threads in separate loop or else they will not execute in parallel
            printf("Error : %d\n", errno);
    }

    for(i = 0; i < THREAD_NUM; i++){

        printf("Return value of thread %d : %d\n", i, *(int *)return_values[i]);
    }

    for(i = 0; i < THREAD_NUM; i++){ free(return_values[i]); }
    free(return_values);
    free(arguments);
    free(threads);
    return 0;
}