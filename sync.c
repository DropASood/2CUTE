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

	lock->lock_state = 0; 
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

	lock->lock_state = 0;
	return 0;
}

int my_spinlock_lockTAS(my_spinlock_t *lock)
{
	if(lock == NULL){ //lock does not exist
		return -1;
	}
	while( my_spinlock_trylock(lock) == -1){ //test and set while lock is lock_state
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
		
		while(lock->lock_state == 1){ //test while lock is lock_state
		}
		
		if(my_spinlock_trylock(lock)== 0 ){ //test and set if it appears unlock_state
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
	
	if(tas( (volatile unsigned long*)&(lock->lock_state)) == 0 ){
		return 0;
	}

	else if (tas( (volatile unsigned long*)&(lock->lock_state)) == 1){
		return -1;
	}

	return -1;
}


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *mutex)
{

	if(mutex == NULL ){
		return -1;
	}

	mutex->minDelay = 1;
	mutex->maxDelay = 100;
	mutex->lock_state = 0;

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

	mutex->lock_state = 0;

	return 0;

}

int my_mutex_lockTAS(my_mutex_t *mutex)
{	
	if(mutex == NULL){ //lock does not exist
		return -1;
	}
	//mutex->minDelay =1;
	printf("mutex delay: %i\n", mutex->minDelay );
	int delay = mutex->minDelay;
	
	while(my_mutex_trylock(mutex) == -1){
		usleep(rand());

		if (delay < mutex->maxDelay){
			delay = delay*2;
			printf("delay: %i\n", delay );

		}
	}

	return 0;
}


int my_mutex_lockTTAS(my_mutex_t *mutex)
{
	if(mutex == NULL){ //lock does not exist
		return -1;
	}

	int delay = mutex->minDelay;
	
	while (1){
		
		while(mutex->lock_state == 1){ //test while lock is locked
			
		}
		
		if (my_mutex_trylock(mutex) == 0){
			return 0;
		}
		usleep(rand()%delay);
		if (delay < mutex->maxDelay){
			delay = delay*2;
		}
	}

}

int my_mutex_trylock(my_mutex_t *mutex)
{

	if(mutex == NULL){ //lock does not exist
		return -1;
	}
	
	if(tas((volatile unsigned long*)&(mutex->lock_state)) == 0 ){
		return 0;
	}

	else if (tas( (volatile unsigned long*)&(mutex->lock_state)) == 1){
		return -1;
	}

	return -1;

}


