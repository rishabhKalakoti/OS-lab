#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
int buffer[100];
int indp = 0,indc = 0;
int n;
sem_t full, empty;
void* produce(){
	while(1){
		int item = rand()%50;
		sem_wait(&empty);
			buffer[indp] = item;
			indp = (indp + 1)%n;
			printf("Producer produced item = %d\n",item);
		sem_post(&full); 
		sleep(1);
	}
}
void* consume(){
	while(1){
		sem_wait(&full);
			int item = buffer[indc];
			indc = (indc + 1)%n;
			printf("Consumer consumed item = %d\n",item);
		sem_post(&empty); 
		sleep(10);
	}
}

int main(){
	printf("Enter buffer size\n");
	scanf("%d",&n);
	sem_init(&full,0,0);
	sem_init(&empty,0,n);
	pthread_t p,c;
	pthread_create(&p, NULL, &produce,NULL);
	pthread_create(&c,NULL,&consume,NULL);
	pthread_join(p,NULL);
	pthread_join(c,NULL);
	return 0;
}
