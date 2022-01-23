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

    JOB_SCHEDULER = (JobScheduler )malloc(sizeof(jobscheduler));
    if(JOB_SCHEDULER == NULL) return 1;

    JOB_SCHEDULER->max_threads = max_threads;
    JOB_SCHEDULER->active_threads_count = 0;
    JOB_SCHEDULER->queue = LL_Create(JobType, &destroyJob, NULL);
    if(JOB_SCHEDULER->queue == NULL) { free(JOB_SCHEDULER); return 1; }

    JOB_SCHEDULER->tids = (pthread_t *)malloc(sizeof(pthread_t) * JOB_SCHEDULER->max_threads);
    if(JOB_SCHEDULER->tids == NULL) { LL_Destroy(JOB_SCHEDULER->queue); free(JOB_SCHEDULER); return 1; }

    JOB_SCHEDULER->active_threads_flags = (char *)malloc(JOB_SCHEDULER->max_threads*sizeof(char));
    if(JOB_SCHEDULER->active_threads_flags == NULL){ free(JOB_SCHEDULER->tids); LL_Destroy(JOB_SCHEDULER->queue); free(JOB_SCHEDULER); return 1; }
    int i;
    for(i = 0; i < JOB_SCHEDULER->max_threads; i++)
        JOB_SCHEDULER->active_threads_flags[i] = 0;

    pthread_mutex_init(&(JOB_SCHEDULER->mutex_threads), NULL);
    pthread_cond_init(&(JOB_SCHEDULER->cond_threads), NULL);
    pthread_mutex_init(&(JOB_SCHEDULER->mutex_thread_count), NULL);

    return 0;
}

int JobScheduler_Submit(Job j){

    if(JOB_SCHEDULER == NULL || j == NULL) return 1;

    if(LL_InsertTail(JOB_SCHEDULER->queue, (Pointer )j) == NULL) return 1;

    pthread_cond_signal(&(JOB_SCHEDULER->cond_threads));

    return 0;
}

int JobScheduler_Pop(JobScheduler js){

    if(JOB_SCHEDULER == NULL) return 1;

    if(LL_DeleteHead(JOB_SCHEDULER->queue) == 1) return 1;

    return 0;
}

void *JobScheduler_Run(void *NULL_param){

    if(JOB_SCHEDULER == NULL) return NULL;

    LLNode lln;
    Job j;
    while(1){
   
        pthread_mutex_lock(&(js->mutex_threads));
        while(LL_IsEmpty(js->queue) == 1 || js->active_threads_count == js->max_threads){

            pthread_cond_wait(&(js->cond_threads), &(js->mutex_threads));
        }

        lln = LL_GetHead(js->queue);
        j = (Job )(lln->data);

        int i = 0;
        for (i = 0; i < js->max_threads; i++)
            if(!js->active_threads_flags[i]) break;

        void *arguments = j->parameters;
        *(int *)arguments = i;

        if(pthread_create(&(js->tids[i]), NULL, (j->routine), &arguments) != 0){
            printf("Error : [JobScheduler_Run] : Failed to create a thread, errno = %d\n", errno);
            return NULL;
        }

        JobScheduler_Pop(js);

        js->active_threads_count++;
        js->active_threads_flags[i] = 1;

        pthread_mutex_unlock(&(js->mutex_threads));
    }

    return js;
}

int JobScheduler_Destroy(JobScheduler js){

    if(js == NULL) return 1;

    if(LL_Destroy(js->queue) == 1) return 1;
    free(js->tids);
    free(js);

    return 0;
}