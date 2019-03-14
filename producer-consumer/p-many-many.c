#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
/*
pthread_t producers[5];
pthread_t consumers[5];

sem_t mutex,empty,full;
*/
int ind=-1,prod = 5,con = 5,buf_len = 4;
int buf[4];

int produce(){
	int p = 1 + rand()%40;
	while(){
		i++;
	}
	printf("Producer [%d] produced %d \n",i+1,p);
	return p;
}


void consume(){
	while(){
		i++;
	}

	printf("Consumer [%d] consumed %d\n",i+1,p);
	
}


void produce(){

	while(1){
		int p = produce(pthread_self());
		//sem_wait(&empty);
		//sem_wait(&mutex);
		++ind;			// critical section
		buf[ind] = p; 
		//sem_post(&mutex);
		//sem_post(&full);
		//sleep(1 + rand()%2);
	}
	
	return NULL;
}


void consume(){
	int c;
	while(1){
		//sem_wait(&full);
		//sem_wait(&mutex);
		c = buf[ind];
		consume(c,pthread_self());
		--ind;
		//sem_post(&mutex);
		//sem_post(&empty);
		//sleep(1+rand()%2);
	}

	return NULL;
}

int main(){
	
	int i,err;

	srand(time(NULL));
	/*
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,buf_len);
	*/
	

	int f1=fork();
	if(f1 == 0)
	{
		fork();
		fork();
		fork();
		produce();
	}
	else
	{
		fork();
		fork();
		fork();
		consume();
	}

	return 0;
}
