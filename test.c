#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include "sync.h"

unsigned long long timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

struct timespec start;
struct timespec stop;
unsigned long long result; //64 bit integer

int main(){
	my_spinlock_t *my_spinlock;
	my_mutex_t *my_mutex;
	my_spinlock = (my_spinlock_t*)malloc(sizeof(my_spinlock_t));
	my_mutex = (my_mutex_t*)malloc(sizeof(my_mutex_t));

	my_spinlock_init(my_spinlock);
	my_mutex_init(my_mutex);
	int i = 0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	while(i++ < 10)
	if(my_spinlock->lock_state==1){
		
	}
	//tas((volatile unsigned long*)&(my_spinlock->lock_state));
	clock_gettime(CLOCK_MONOTONIC, &stop);

	result=timespecDiff(&stop,&start);

	printf("time(ns): %llu\n",result);

	return 0;

}
