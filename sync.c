/***************************
 * CMPT-300 Assignment 2.2 *
 * Tony Dinh 	301142069  *
 * Archit Sood	301188293  *
 ***************************/
 
/*===========
    sync.c
=============*/

#define _REENTRANT

#include "sync.h"


/*
 * Spinlock routines
 */

int my_spinlock_init(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}

	lock->locked = 0; 
	return 0;
}

int my_spinlock_destroy(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}

	free(lock);
	return 0;
}

int my_spinlock_unlock(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}

	lock->locked = 0;
	return 0;
}

int my_spinlock_lockTAS(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}
	while(tas( (unsigned long*)&(lock->locked) ) == 1){ //test and set while lock is locked
		//spin...
	}

	return 0;
}


int my_spinlock_lockTTAS(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}

	while(1){
		
		while(lock->locked == 1){ //test while lock is locked
		}
		
		if(tas( (unsigned long*)&(lock->locked)) == 0 ){ //test and set if it appears unlocked
			return 0;
		}

	}
	
	return 0;
}

int my_spinlock_trylock(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}
	
	if(tas( (unsigned long*)&(lock->locked)) == 0 ){

	}
}


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *mutex)
{
	return 0;
}

int my_mutex_destroy(my_mutex_t *mutex)
{
	if(mutex == NULL){ //lock does not exist
		return -1;
	}

	free(mutex);
	return 0;
}

int my_mutex_unlock(my_mutex_t *mutex)
{
	if(mutex == NULL){
		return -1;
	}

	mutex->locked=0;
	return 0;

}

int my_mutex_lockTAS(my_mutex_t *mutex)
{	
	if(mutex == NULL){ //lock does not exist
		return -1;
	}

	int delay = mutex->minDelay;
	
	while (1){
		
		if (tas( (unsigned long*)&(mutex->locked) ) == 0){
			return 0;
		}
		sleep(rand()%delay);
		if (delay < mutex->maxDelay){
			delay = delay*2;
		}
	}
}


int my_mutex_lockTTAS(my_mutex_t *mutex)
{
	if(mutex == NULL){ //lock does not exist
		return -1;
	}

	int delay = mutex->minDelay;
	
	while (1){
		
		while(mutex->locked == 1){ //test while lock is locked
		}
		
		if (tas( (unsigned long*)&(mutex->locked) ) == 0){
			return 0;
		}
		sleep(rand()%delay);
		if (delay < mutex->maxDelay){
			delay = delay*2;
		}
	}

}

int my_mutex_trylock(my_mutex_t *mutex)
{
	return 0;

}


