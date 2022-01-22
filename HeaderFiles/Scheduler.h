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

#include "common_types.h"
#include "core.h"

//////////////////////////////////////////////

JobScheduler JobScheduler_Create(int );
int JobSceduler_Submit(JobScheduler , Job );
int JobSceduler_Destroy(JobScheduler );