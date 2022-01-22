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

JobScheduler JobScheduler_Create(int max_threads){

    JobSceduler js = (JobSceduler )malloc(sizeof(jobscheduler));
    if(js == NULL) return NULL;

    js->max_threads = max_threads;
    js->active_threads_count = 0;
    js->queue = LL_Create(JobType, &destoryJob, NULL);
    if(js->queue == NULL) { free(js); return NULL; }

    js->tids = (pthread_t *)malloc(sizeof(pthread_t) * js->max_threads);
    if(js->tids == NULL) { LL_Destroy(js->queue); free(js); return NULL; }
    js->active_thread_flags = (char *)malloc(js->max_threads*sizeof(char));
    if (!(js->active_thread_flags)){ LL_Destroy(js->queue); free(js->tids); free(js); return NULL; }
    int i;
    for(i = 0; i < js->max_threads; i++){
        js->tids[i] = 0;
        js->active_thread_flags[i] = 0;
    }

    pthread_mutex_init(&(js->mutex_threads)), NULL);
    pthread_cond_init(&(js->cond_threads)), NULL);

    return js;
}

int JobSceduler_Submit(JobSceduler js, Job j){

    if(js == NULL || j == NULL) return 1;

    if(LL_InsertTail(js->queue, (Pointer )j) == NULL) return 1;
    // pthread_mutex_lock(&(js->mutex_threads));
    // js->active_threads_count++;
    // pthread_mutex_unlock(&(js->mutex_threads));

    return 0;
}

int JobScheduler_Pop(JobScheduler js){

    if(js == NULL) return 1;

    if(LL_DeleteHead(js->queue, (Pointer )j) == NULL) return 1;

    return 0;
}

int JobScheduler_Run(JobSceduler js){

    if(js == NULL) return 1;

    LLNode lln = LL_GetHead(js->queue);
    Job first_job = (Job )(lln->data);

    while(1){
   
        pthread_mutex_lock(&(js->mutex_threads));
        while(js->active_threads_count == js->max_threads){

            pthread_cond_wait(&(js->cond_threads), &(js->mutex_threads));
        }

        lln = LL_GetHead(js->queue);
        first_job = (Job )(lln->data);

        int i = 0;
        for (i = 0; i < js->max_threads; i++)
            if (!active_thread_flags[i]) break;

        //In case no thread is available - should be impossible
        //if (i == js->max_threads) pthread_join()

        void **arguments = malloc(2*sizeof(void *));
        if (!arguments) return 1;
        arguments[0] = js->parameters;
        arguments[1] = (void *)malloc(sizeof(int));
        if (!arguments[1]) { free(arguments); return 1; }
        *(int *)arguments[1] = i;

        if(pthread_create(&(js->tids[i]), NULL, (first_job->routine), &arguments))
            printf("Error : [JobScheduler_Run] : Failed to create a thread, errno = %d\n", errno);

        JobScheduler_Pop(js);

        js->active_threads_count++;

        pthread_mutex_unlock(&(js->mutex_threads));
    }
}

int JobSceduler_Destroy(JobScheduler js){

    if(js == NULL) return 1;

    if(LL_Destroy(js->queue) == 1) return 1;
    free(js->tids);
    free(js);

    return 0;
}