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
	while( tas( (volatile unsigned long*)&(lock->lock_state)) == 1) { //test and set while lock is locked
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
		
		if( tas( (volatile unsigned long*)&(lock->lock_state)) == 0){ //test and set if it appears unlock_state
			return 0;
		}

	}
	
	return 0;
}

// int my_spinlock_trylock(my_spinlock_t *lock)
// {
// 	if(lock == NULL || lock->tid == pthread_self()){ //lock does not exist
// 		return -1;
// 	}
	
// 	if(tas( (volatile unsigned long*)&(lock->lock_state)) == 0 ){
// 		lock->tid = pthread_self();
// 		return 0;
// 	}

// 	else if (tas( (volatile unsigned long*)&(lock->lock_state)) == 1){
// 		return -1;
// 	}

// 	return -1;
// }


/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *mutex)
{

	if(mutex == NULL ){
		return -1;
	}

	mutex->minDelay = 1;
	mutex->maxDelay = 256;
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
	// if(mutex == NULL){
	// 	return -1;
	// }

	mutex->lock_state = 0;

	return 0;

}

int my_mutex_lockTAS(my_mutex_t *mutex)
{	

	double time;
	double backoff = 0;

	// if(mutex == NULL){ //lock does not exist
	// 	return -1;
	// }

	//int delay = mutex->minDelay;
	while(1){
		
		// if (tas((volatile unsigned long*)&(mutex->lock_state)) == 0 ){
		// 	return 0;
		// }
		// printf("hiiiiiiiiiiii\n");
		// while (tas((volatile unsigned long*)&mutex->lock_state)==0){
		// 	// printf("looooooppppppp\n");
		// }
		// return 0;

		while (tas((volatile unsigned long*)&mutex->lock_state)==1){};
		return 0;

		// printf("HOW you doinnn?\n");
		// time = fmin((rand()/(double)RAND_MAX)*pow(2, backoff), mutex->maxDelay);
		// printf("random time %f\n", (rand()/(double)RAND_MAX)*pow(2, backoff));
		// printf("Sleep time: %f\n", time);
		// backoff++;
		// usleep(time);	
	}
/*	if(mutex == NULL){ //lock does not exist
		return -1;
	}
	int minDelay = 1;
	int maxDelay = 256;
	int delay = minDelay;
	//printf("mutex lockstate: %i \n", mutex->lock_state);
	
	while(1){

		if(my_mutex_trylock(mutex) == 0){
			printf("Got the lock\n");
			return 0;
		}
		usleep(rand()%delay);
		if (delay < maxDelay){
			delay = delay*2;
		}

	}
	
*/
	
}


int my_mutex_lockTTAS(my_mutex_t *mutex)
{
	if(mutex == NULL){ //lock does not exist
		return -1;
	}

	int delay = mutex->minDelay;
	printf("This is %i\n", delay);
	while (1){
		
		while(tas((volatile unsigned long*)&(mutex->lock_state)) == 1){ //test while lock is locked
			
		}
		
		printf("This is %i\n", delay);

		if (tas((volatile unsigned long*)&(mutex->lock_state)) == 0 ){
			return 0;
		}
		
		sleep(rand()%delay);
		if (delay < mutex->maxDelay){
			delay = delay*2;
		}
	}

}


/*int my_mutex_trylock(my_mutex_t *mutex)
{
	if(mutex == NULL){ //lock does not exist
		return -1;
	}
	if(tas((volatile unsigned long*)&(mutex->lock_state)) == 0 ){
	printf("state: %i\n",mutex->lock_state );
		return 0;
	}

	else if (tas( (volatile unsigned long*)&(mutex->lock_state)) == 1){
		//printf("Failed to get lock\n");
		return -1;
	}
	return -1;


}
*/

