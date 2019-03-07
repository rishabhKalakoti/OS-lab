#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t producers[5];
pthread_t consumers[5];

sem_t mutex,empty,full;

int ind=-1,prod = 1,con = 5,buf_len = 4;
int buf[4];

int produce(pthread_t self){
	int i = 0;
	int p = 1 + rand()%40;
	while(!pthread_equal(producers[i],self) && i < prod){
		i++;
	}
	printf("Producer [%d] produced %d \n",i+1,p);
	return p;
}


void consume(int p,pthread_t self){
	int i = 0;
	while(!pthread_equal(consumers[i],self) && i < con){
		i++;
	}

	//printf("Buffer:");
	/*for(i=0;i<=ind;++i)
		printf("%d ",*(buf+i));*/
	printf("Consumer [%d] consumed %d\n",i+1,p);
	
}


void* producer(void *args){

	while(1){
		int p = produce(pthread_self());
		sem_wait(&empty);
		sem_wait(&mutex);
		++ind;			// critical section
		buf[ind] = p; 
		sem_post(&mutex);
		sem_post(&full);
		//sleep(1 + rand()%2);
	}
	
	return NULL;
}


void* consumer(void *args){
	int c;
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		c = buf[ind];
		consume(c,pthread_self());
		--ind;
		sem_post(&mutex);
		sem_post(&empty);
		//sleep(1+rand()%2);
	}

	return NULL;
}

int main(){
	
	int i,err;

	srand(time(NULL));

	sem_init(&mutex,0,1);
	sem_init(&full,0,0);

	

	sem_init(&empty,0,buf_len);

	for(i=0;i<prod;i++){
		pthread_create(&producers[i],NULL,&producer,NULL);
		
	}

	for(i=0;i<con;i++){
		pthread_create(&consumers[i],NULL,&consumer,NULL);
		
	}

	for(i=0;i<prod;i++){
		pthread_join(producers[i],NULL);
	}
	for(i=0;i<con;i++){
		pthread_join(consumers[i],NULL);
	}


	return 0;
}
