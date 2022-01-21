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
// File : common_types.h
///////////////////////////////////

#pragma once

#include "core.h"

#define THREAD_NUM 10

struct JobScheduler{

    int execution_thread;
    List
    p_thread_t *tids;

    //mutex, condvar...
};

JobScheduler *initialize_scheduler(int execution_threads);
int submit_job(JobScheduler *sch, Job *j);
int wait_all_tasks_finish(JobScheduler *sch);
int destroy_scheduler(JobScheduler *sch); 