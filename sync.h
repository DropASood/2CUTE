/*
 * NAME, etc.
 *
 * sync.h
 */

#ifndef _my_SYNC_H_
#define _my_SYNC_H_

#include "atomic_ops.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>


struct my_mutex_struct {
  int lock_state; 	//locked = 1, unlocked = 0
  int minDelay; //
  int maxDelay;
};




typedef struct my_mutex_struct my_mutex_t;


int my_mutex_init(my_mutex_t *mutex);
int my_mutex_unlock(my_mutex_t *mutex);
int my_mutex_destroy(my_mutex_t *mutex);

int my_mutex_lockTAS(my_mutex_t *mutex);
int my_mutex_lockTTAS(my_mutex_t *mutex);
int my_mutex_trylock(my_mutex_t *mutex);



/*Spinlock Starts here*/

struct my_spinlock_struct {
  int lock_state; 		//locked = 1, unlocked = 0
  unsigned int count; 	//count of how many times it has been locked
  pthread_t owner; 		//which thread has a hold of the lock

};

typedef struct my_spinlock_struct my_spinlock_t;

int my_spinlock_init(my_spinlock_t *lock);
int my_spinlock_destroy(my_spinlock_t *lock);
int my_spinlock_unlock(my_spinlock_t *lock);

int my_spinlock_lockTAS(my_spinlock_t *lock);
int my_spinlock_lockTTAS(my_spinlock_t *lock);
int my_spinlock_trylock(my_spinlock_t *lock);


#endif
