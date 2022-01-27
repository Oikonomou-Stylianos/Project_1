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

    JOB_SCHEDULER.max_threads = max_threads;
    JOB_SCHEDULER.active_threads_count = 0;
    JOB_SCHEDULER.queue = LL_Create(JobType, &destroyJob, NULL);
    if(JOB_SCHEDULER.queue == NULL) { return 1; }

    JOB_SCHEDULER.tids = (pthread_t *)malloc(sizeof(pthread_t) * JOB_SCHEDULER.max_threads);
    if(JOB_SCHEDULER.tids == NULL) { LL_Destroy(JOB_SCHEDULER.queue); return 1; }

    JOB_SCHEDULER.active_threads_flags = (char *)malloc(JOB_SCHEDULER.max_threads*sizeof(char));
    if(JOB_SCHEDULER.active_threads_flags == NULL){ free(JOB_SCHEDULER.tids); LL_Destroy(JOB_SCHEDULER.queue); return 1; }
    int i;
    for(i = 0; i < JOB_SCHEDULER.max_threads; i++)
        JOB_SCHEDULER.active_threads_flags[i] = 0;
    JOB_SCHEDULER.exit_status = 0;

    // Initialize the mutexes and the conditional variables
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_queue), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_threads), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_active_threads_count), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_query_result), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER.mutex_wait), NULL);
    
    pthread_cond_init(&(JOB_SCHEDULER.cond_threads), NULL);
    pthread_cond_init(&(JOB_SCHEDULER.cond_query_result), NULL);
    pthread_cond_init(&(JOB_SCHEDULER.cond_wait), NULL);

    return 0;
}

int JobScheduler_SubmitJob(Job j){

    if(j == NULL) return 1;

    pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
    if(LL_InsertTail(JOB_SCHEDULER.queue, (Pointer )j) == NULL) return 1;
    pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

    pthread_cond_signal(&(JOB_SCHEDULER.cond_threads));     // Signal the Scheduler that a Job has been submitted 

    return 0;
}

void JobScheduler_WaitJobs(){

    char wait_cond;

    pthread_mutex_lock(&(JOB_SCHEDULER.mutex_active_threads_count)); pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue)); 
    if(JOB_SCHEDULER.active_threads_count != 0 || LL_IsEmpty(JOB_SCHEDULER.queue) == 0) wait_cond = 1;
    else wait_cond = 0;
    pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_active_threads_count)); pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue)); 

    pthread_mutex_lock(&(JOB_SCHEDULER.mutex_wait));
    while(wait_cond == 1){

        pthread_cond_wait(&(JOB_SCHEDULER.cond_wait), &(JOB_SCHEDULER.mutex_wait));
    
        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_active_threads_count)); pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue)); 
        if(JOB_SCHEDULER.active_threads_count != 0 || LL_IsEmpty(JOB_SCHEDULER.queue) == 0) wait_cond = 1;
        else wait_cond = 0;
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_active_threads_count)); pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue)); 
    }
    pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_wait));

    return;
}

void *JobScheduler_Run(void *NULL_param){

    int i;
    Job j;
    LLNode lln;
    void **parameters;

    while(1){

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_threads));
        while(LL_IsEmpty(JOB_SCHEDULER.queue) == 1 || JOB_SCHEDULER.active_threads_count == JOB_SCHEDULER.max_threads){

            pthread_cond_wait(&(JOB_SCHEDULER.cond_threads), &(JOB_SCHEDULER.mutex_threads));

            if(JOB_SCHEDULER.exit_status == 1)  // Exit condition. Is changed from JobScheduler_Destroy
                pthread_exit(NULL);
        }
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_threads));

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
        lln = LL_GetHead(JOB_SCHEDULER.queue);
        j = (Job )(lln->data);
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));

        // Find available pthread_tid
        for (i = 0; i < JOB_SCHEDULER.max_threads; i++)
            if(!JOB_SCHEDULER.active_threads_flags[i]) break;
        JOB_SCHEDULER.active_threads_flags[i] = 1;

        // Create thread parameters
        parameters = (void **)malloc(sizeof(void *) * 2);
        parameters[0] = (void *)malloc(sizeof(int ));
        *(int *)parameters[0] = i;  // thread flag
        parameters[1] = (void *)(j->parameters);

        if(pthread_create(&(JOB_SCHEDULER.tids[i]), NULL, j->routine, (void *)parameters) != 0){
            printf("Error : [JobScheduler_Run] : Failed to create a thread, errno = %d\n", errno);
            return NULL;
        }

        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_active_threads_count));
        JOB_SCHEDULER.active_threads_count++;
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_active_threads_count));
        
        pthread_mutex_lock(&(JOB_SCHEDULER.mutex_queue));
        if(LL_DeleteHead(JOB_SCHEDULER.queue) == 1) return NULL;
        pthread_mutex_unlock(&(JOB_SCHEDULER.mutex_queue));
        
        pthread_cond_signal(&(JOB_SCHEDULER.cond_wait));    // Signal the WaitJobs functions that a thread has been removed from the queue and activated 
    }
}

int JobScheduler_Destroy(){

    JobScheduler_WaitJobs();

    // Terminate JobScheduler_Run thread 
    JOB_SCHEDULER.exit_status = 1;
    pthread_cond_signal(&(JOB_SCHEDULER.cond_threads));

    if(LL_Destroy(JOB_SCHEDULER.queue) == 1) return 1;
    free(JOB_SCHEDULER.tids);
    free(JOB_SCHEDULER.active_threads_flags);
    
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_queue)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_threads)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_active_threads_count)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_query_result)) != 0) return 1;
    if(pthread_mutex_destroy(&(JOB_SCHEDULER.mutex_wait)) != 0) return 1;

    if(pthread_cond_destroy(&(JOB_SCHEDULER.cond_threads)) != 0) return 1;
    if(pthread_cond_destroy(&(JOB_SCHEDULER.cond_query_result)) != 0) return 1;
    if(pthread_cond_destroy(&(JOB_SCHEDULER.cond_wait)) != 0) return 1;

    return 0;
}