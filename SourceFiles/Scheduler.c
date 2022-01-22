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

#include "LinkedList.h"

#include "constructors.h"
#include "common_types.h"
#include "core.h"

JobScheduler JobScheduler_Create(int execution_threads){

    JobSceduler js = (JobSceduler )malloc(sizeof(jobscheduler));
    if(js == NULL) return NULL;

    js->execution_threads = execution_threads;
    js->queue = LL_Create(JobType, &destoryJob, NULL);
    if(js->queue == NULL) { free(js); return NULL; }

    js->tids = (pthread_t *)malloc(sizeof(pthread_t) * js->execution_threads);
    if(js->tids == NULL) { LL_Destroy(js->queue); free(js); return NULL; }
    int i;
    for(i = 0; i < js->execution_threads; i++)
        js->tids[i] = 0;

    return js;
}

int JobSceduler_Submit(JobSceduler js, Job j){

    if(js == NULL || j == NULL) return 1;

    if(LL_InsertTail(js->queue, (Pointer )j) == NULL) return 1;

    return 0;
}

int JobSceduler_Destroy(JobScheduler js){

    if(js == NULL) return 1;

    if(LL_Destroy(js->queue) == 1) return 1;
    free(js->tids);

    return 0;
}