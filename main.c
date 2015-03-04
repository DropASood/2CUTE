#include "main.h"


struct timespec start;
struct timespec stop;
unsigned long long result; //64 bit integer

void *fnC()
{
    int i;
    for(i=0;i<1000000;i++)
    {   
        c++;
    }   
  return 0;
}


pthread_mutex_t count_mutex;
pthread_spinlock_t count_spinlock;

//create own locks
my_spinlock_t my_spinlock;
my_mutex_t my_mutex;


void *pthreadMutexTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	pthread_mutex_lock(&count_mutex);
	c++;
	pthread_mutex_unlock(&count_mutex);    
	
    }   

	return 0;
}

	//printf("testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS\n");	

void *pthreadSpinlockTest()
{

    int i;
    for(i=0;i<numItterations;i++)
    { 
	pthread_spin_lock(&count_spinlock);
	c++;
	pthread_spin_unlock(&count_spinlock);    
	
    }   

	return 0;
}

void *mySpinlockTASTest()
{

    int i;
	//printf("lock state: %i\n", my_spinlock.lock_state);
    for(i=0;i<numItterations;i++)
    { 
		my_spinlock_lockTAS(&my_spinlock);
		//printf("lock state inside: %i\n", my_spinlock.lock_state);
		//printf("lock state: %i\n", my_spinlock.lock_state);
		printf("tid: %lu \n" ,pthread_self());
		c++;
		my_spinlock_unlock(&my_spinlock);
		//printf("outisde lock state: %i\n", my_spinlock.lock_state);
		//printf("UNLOCKED******************\n");    
    }   

	return 0;
}

void *mySpinlockTTASTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	my_spinlock_lockTTAS(&my_spinlock);
	printf("tid: %lu \n" ,pthread_self());
	c++;
	my_spinlock_unlock(&my_spinlock);    
	
    }   

	return 0;
}



void *myMutexlockTASTest()
{

    int i;
    for(i=0;i<numItterations;i++)
    { 
	my_mutex_lockTAS(&my_mutex);
 //    printf("Heyyyyyyyyyy\n");
	// printf("tid: %lu \n" ,pthread_self());
	c++;
	my_mutex_unlock(&my_mutex);    
	
    }   

	return 0;
}

void *myMutexlockTTASTest()
{

    int i;
    for(i=0;i<numItterations;i++)
    { 
	my_mutex_lockTTAS(&my_mutex);
	c++;
	my_mutex_unlock(&my_mutex);    
	
    }   

	return 0;
}




int runTest(int testID)
{

/*You must create all data structures and threads for you experiments*/

if (testID == 0 || testID == 1 ) /*Pthread Mutex*/
{
	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads+i, NULL, &pthreadMutexTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread Mutex time(ms): %llu\n",result/1000000);
	free(threads);

}

if(testID == 0 || testID == 2) /*Pthread Spinlock*/
{
	pthread_t *threads2 = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;
	pthread_spin_unlock(&count_spinlock);
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads2+i, NULL, &pthreadSpinlockTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads2[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Spin) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread Spin time(ms): %llu\n",result/1000000);
	free(threads2);

}

if(testID == 0 || testID == 3) /*MySpinlockTAS*/
{
/* mySpinlock TAS goes here*/
	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads+i, NULL, &mySpinlockTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run (My Spin TAS) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("My Spin TAS time(ms): %llu\n",result/1000000);
	free(threads);

}


if(testID == 0 || testID == 4) /*MySpinlockTTAS*/
{
/* mySpinlock TAS goes here*/
	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads+i, NULL, &mySpinlockTTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run (My Spin TTAS) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("My Spin TTAS time(ms): %llu\n",result/1000000);
	free(threads);

}

if(testID == 0 || testID == 5) /*MySpinlockTTAS*/
{
/* mySpinlock TAS goes here*/
	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads+i, NULL, &myMutexlockTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run (My Mutex TAS) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("My Mutex TAS time(ms): %llu\n",result/1000000);
	free(threads);

}

if(testID == 0 || testID == 6) /*MySpinlockTTAS*/
{
/* mySpinlock TAS goes here*/
	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;
	c=0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( (rt = pthread_create( threads+i, NULL, &myMutexlockTTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run (My Mutex TTAS) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("My Mutex TTAS time(ms): %llu\n",result/1000000);
	free(threads);
}




	return 0;
}

int testAndSetExample()
{
	volatile long test = 0; //Test is set to 0
	printf("Test before atomic OP:%ld\n",test);
	tas((unsigned long*)&test);
	printf("Test after atomic OP:%ld\n",test);
return 0;
}

int processInput(int argc, char *argv[])
{

/*testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS*/
	/*You must write how to parse input from the command line here, your software should default to the values given below if no input is given*/
	
	if(argc ==1){
		numThreads=4;
		numItterations=1000000;
		testID=0;
	}

	else if( argc > 1){
		numThreads = atoi(argv[1]);
		numItterations = atoi(argv[2]);
		testID = atoi(argv[3]);
	}
	
	
	return 0;
}


int main(int argc, char *argv[])
{
	my_spinlock_init(&my_spinlock);
	my_mutex_init(&my_mutex);


	printf("Usage of: %s -t #threads -i #itterations -d testid\n", argv[0]);
	printf("testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS\n");	
	
	//testAndSetExample(); //Uncomment this line to see how to use TAS
	processInput(argc,argv);
	runTest(testID);


	//my_spinlock_destroy(my_spinlock);
	//my_mutex_destroy(my_mutex);

	return 0;

}
