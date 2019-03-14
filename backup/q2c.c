#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t resource,readCount,service;
int count=0;
void* writer(void* num){
		int k = (int)num;
		sem_wait(&service);
		sem_wait(&resource);
		sem_post(&service);
		printf("Writer %d is writing\n",k);
		printf("Number of readers = %d\n",count);
		sem_post(&resource);
		
	
}
void* reader(void* num){
		int k = (int)num;
		sem_wait(&service);
		sem_wait(&readCount);
		if(count==0){
			sem_wait(&resource);
		}
		count++;
		sem_post(&service);
		sem_post(&readCount);
		printf("Reader %d is reading\n",k);
		printf("Number of readers = %d\n",count);
		sem_wait(&readCount);
		count--;
		if(count==0){
			sem_post(&resource);
		}
		sem_post(&readCount);
}

int main(){
		sem_init(&resource,0,1);
		sem_init(&readCount,0,1);
		sem_init(&service,0,1);
		pthread_t w[5],r[5];
		for(int i=0;i<5;i++){
			pthread_create(&w[i],NULL,&writer,(void*)((int)(i+1)));
			pthread_create(&r[i],NULL,&reader,(void*)((int)(i+1)));
		}
		for(int i=0;i<5;i++){
			pthread_join(w[i],NULL);
			pthread_join(r[i],NULL);
		}
		
		
		return 0;
}
