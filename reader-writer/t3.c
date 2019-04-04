#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t resource,rc,service;
int c=0;
int N=5;
int data=0;
void* writer(void* num){
		int k = (int)num;
		sem_wait(&service);
		sem_wait(&resource);
		sem_post(&service);
		printf("Writer [%d]\n",k);
		data++;
		printf("Written data: %d\n",data);
		//printf("Number of readers = %d\n",c);
		sem_post(&resource);
}
void* reader(void* num){
		int k = (int)num;
		sem_wait(&service);
		sem_wait(&rc);
		if(c==0){
			sem_wait(&resource);
		}
		c++;
		sem_post(&service);
		sem_post(&rc);
		printf("Reader [%d]\n",k);
		printf("Read data: %d\n",data);
		//printf("Number of readers = %d\n",c);
		sem_wait(&rc);
		c--;
		if(c==0){
			sem_post(&resource);
		}
		sem_post(&rc);
}

int main(){
		sem_init(&resource,0,1);
		sem_init(&rc,0,1);
		sem_init(&service,0,1);
		pthread_t w[N],r[N];
		for(int i=0;i<N;i++){
			pthread_create(&w[i],NULL,&writer,(void*)((int)(i+1)));
			pthread_create(&r[i],NULL,&reader,(void*)((int)(i+1)));
		}
		for(int i=0;i<N;i++){
			pthread_join(w[i],NULL);
			pthread_join(r[i],NULL);
		}
		
		
		return 0;
}
