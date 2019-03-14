#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
int buffer[100];
int indp = 0,indc = 0;
int n;
sem_t full, empty,lock;
void* produce(void* i){
	int k = (int)i;
	while(1){
		int item = rand()%50;
		sem_wait(&empty);
			sem_wait(&lock);
				buffer[indp] = item;
				indp = (indp + 1)%n;
				printf("Producer %d produced item = %d\n",k,item);
			sem_post(&lock);
		sem_post(&full); 
		sleep(1);
	}
}
void* consume(void* i){
	int k = (int)i;
	while(1){
		sem_wait(&full);
			sem_wait(&lock);
				int item = buffer[indc];
				indc = (indc + 1)%n;
				printf("Consumer %d consumed item = %d\n",k,item);
			sem_post(&lock);
		sem_post(&empty); 
		sleep(1);
	}
}

int main(){
	printf("Enter buffer size\n");
	scanf("%d",&n);
	sem_init(&full,0,0);
	sem_init(&empty,0,n);
	sem_init(&lock,0,1);
	pthread_t p[5],c[5];
	for(int i=0;i<5;i++){
		pthread_create(&c[i], NULL, &consume,(void*)((int)(i+1)));
		pthread_create(&p[i], NULL, &produce,(void*)((int)(i+1)));
	}
	for(int i=0;i<5;i++){
		pthread_join(c[i],NULL);
		pthread_join(p[i],NULL);
	}
	return 0;
}
