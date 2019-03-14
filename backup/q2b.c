#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t rlock,wlock,readTry,resource;
int rcount=0,wcount=0;
void* writer(void* num){
		int k = (int)num;
		sem_wait(&wlock);
		wcount++;
		if(wcount == 1){
			sem_wait(&readTry);
		}
		sem_post(&wlock);
		
		sem_wait(&resource);
		printf("Writer %d is writing\n",k);
		printf("Readers = %d and Writers = %d\n",rcount,wcount);
		sem_post(&resource);
		
		sem_wait(&wlock);
		wcount--;
		if(wcount==0){
			sem_post(&readTry);
		}
		sem_post(&wlock);
		
	
}
void* reader(void* num){
		int k = (int)num;
		sem_wait(&readTry);
		sem_wait(&rlock);
		rcount++;
		if(rcount==1){
			sem_wait(&resource);
		}
		sem_post(&rlock);
		sem_post(&readTry);
		printf("Reader %d is reading\n",k);
		printf("Readers = %d and Writers = %d\n",rcount,wcount);
		
		sem_wait(&rlock);
		rcount--;
		if(rcount==0){
			sem_post(&resource);
		}
		sem_post(&rlock);
}

int main(){
		sem_init(&rlock,0,1);
		sem_init(&wlock,0,1);
		sem_init(&resource,0,1);
		sem_init(&readTry,0,1);
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
