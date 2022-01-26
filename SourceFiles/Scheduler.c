///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// Assistant : Sarantis Paskalis
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// File : Scheduler.c
///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include "LinkedList.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

extern JobScheduler JOB_SCHEDULER;

int JobScheduler_Initialize(int max_threads){

    printf("Entering JobScheduler_Initialize\n");

    JOB_SCHEDULER.max_threads = max_threads;
    JOB_SCHEDULER.active_threads_count = 0;
    JOB_SCHEDULER.queue = LL_Create(JobType, &destroyJob, NULL);
    if(JOB_SCHEDULER.queue == NULL) { return 1; }

    JOB_SCHEDULER.tids = (pthread_t *)malloc(sizeof(pthread_t) * JOB_SCHEDULER.max_threads);
    if(JOB_SCHEDULER.tids == NULL) { LL_Destroy(JOB_SCHEDULER.queue); return 1; }

    JOB_SCHEDULER.active_threads_flags = (char *)malloc(JOB_SCHEDULER.max_threads*sizeof(char));
    if(JOB_SCHEDULER.active_threads_flags == NULL){ LL_Destroy(JOB_SCHEDULER.queue); return 1; }
    int i;
    for(i = 0; i < JOB_SCHEDULER.max_threads; i++)
        JOB_SCHEDULER.active_threads_flags[i] = 0;
    JOB_SCHEDULER.exit_status = 0;

    pthread_mutex_init(&(JOB_SCHEDULER.mutex_queue), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_threads), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_active_threads_count), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_query_result), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_exit), NULL);
    pthread_cond_init(&(JOB_SCHEDULER.cond_threads), NULL);
    pthread_cond_init(&(JOB_SCHEDULER.cond_query_result), NULL);
    pthread_cond_init(&(JOB_SCHEDULER.cond_exit), NULL);

    printf("Exiting JobScheduler_Initialize\n");

    return 0;
}

int JobScheduler_SubmitJob(Job j){

    printf("SubmitJob | doc_id = %u\n", *(DocID *)((void **)(j->parameters))[0]);

    if(j == NULL) return 1;

    pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
    if(LL_InsertTail(JOB_SCHEDULER.queue, (Pointer )j) == NULL) return 1;
    pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

    pthread_cond_signal(&(JOB_SCHEDULER.cond_threads));

    // printf("Exiting JobScheduler_SubmitJob\n");

    return 0;
}

// int JobScheduler_DequeueJob(){

//     if(JOB_SCHEDULER == NULL) return 1;

//     pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
    
//     pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

//     return 0;
// }
// #include <unistd.h>
// void *sleep_test(){

//     sleep(10);
// }
int JobScheduler_WaitJobs(){

    JOB_SCHEDULER.exit_status = 1;

    pthread_mutex_lock(&(JOB_SCHEDULER.mutex_exit));
    pthread_cond_wait(&(JOB_SCHEDULER.cond_exit), &(JOB_SCHEDULER.mutex_exit));
    pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_exit));

    // CHECK ACTIVE THREADS AND QUEUE

    return 0;
}

void *JobScheduler_Run(void *NULL_param){

    printf("Entering JobScheduler_Run\n");
    
    int i;
    Job j;
    LLNode lln;
    void **parameters;

    while(1){
   
        // pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
        // char empty_queue = LL_IsEmpty(JOB_SCHEDULER.queue);
        // pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_threads));
        while(LL_IsEmpty(JOB_SCHEDULER.queue) == 1 || JOB_SCHEDULER.active_threads_count == JOB_SCHEDULER.max_threads){

            pthread_cond_wait(&(JOB_SCHEDULER.cond_threads), &(JOB_SCHEDULER.mutex_threads));
        }
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_threads));
        // Exit condition
        // if(LL_IsEmpty(JOB_SCHEDULER.queue) == 1 && JOB_SCHEDULER.active_threads_count == 0 && JOB_SCHEDULER.exit_status == 1)
        //     break;

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
        lln = LL_GetHead(JOB_SCHEDULER.queue);
        j = (Job )(lln->data);
        if(LL_DeleteHead(JOB_SCHEDULER.queue) == 1) return NULL;
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

        for (i = 0; i < JOB_SCHEDULER.max_threads; i++)
            if(!JOB_SCHEDULER.active_threads_flags[i]) break;
        JOB_SCHEDULER.active_threads_flags[i] = 1;

        // Create thread parameters
        parameters = (void **)malloc(sizeof(void *) * 2);
        parameters[0] = (void *)malloc(sizeof(int ));
        *(int *)parameters[0] = i;
        parameters[1] = (void *)(j->parameters);

        printf("JobScheduler_Run | doc_id = %d\n", *(DocID *)((void **)parameters[1])[0]);

        // Call thread
        if(pthread_create(&(JOB_SCHEDULER.tids[i]), NULL, j->routine, (void *)&parameters) != 0){
            printf("Error : [JobScheduler_Run] : Failed to create a thread, errno = %d\n", errno);
            return NULL;
        }

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_active_threads_count));
        JOB_SCHEDULER.active_threads_count++;
        printf("Active threads = %d\n", JOB_SCHEDULER.active_threads_count);
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_active_threads_count));
        
        destroyJob(j);
        // pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
        // pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));
    }

    pthread_cond_signal(&(JOB_SCHEDULER.cond_exit));
    
    return NULL;
}

int JobScheduler_Destroy(){

    if(LL_Destroy(JOB_SCHEDULER.queue) == 1) return 1;
    free(JOB_SCHEDULER.tids);
    free(JOB_SCHEDULER.active_threads_flags);
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_queue)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_threads)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_active_threads_count)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_query_result)) != 0) return 1;
    if(pthread_cond_destroy(&(JOB_SCHEDULER.cond_threads)) != 0) return 1;
    if(pthread_cond_destroy(&(JOB_SCHEDULER.cond_query_result)) != 0) return 1;

    return 0;
}