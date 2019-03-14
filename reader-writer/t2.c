#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t rlock,wlock,readTry,resource;
int rc=0,wc=0;
int N=10;
int data=0;
void* writer(void* num){
		int k = (int)num;
		sem_wait(&wlock);
		wcount++;
		if(wc == 1){
			sem_wait(&readTry);
		}
		sem_post(&wlock);
		
		sem_wait(&resource);
		printf("Writer [%d]\n",k);
		data++;
		printf("Written data: %d\n",data);
		//printf("Readers = %d and Writers = %d\n",rc,wc);
		sem_post(&resource);
		
		sem_wait(&wlock);
		wcount--;
		if(wc==0){
			sem_post(&readTry);
		}
		sem_post(&wlock);
		
	
}
void* reader(void* num){
		int k = (int)num;
		sem_wait(&readTry);
		sem_wait(&rlock);
		rc++;
		if(rc==1){
			sem_wait(&resource);
		}
		sem_post(&rlock);
		sem_post(&readTry);
		printf("Reader [%d]\n",k);
		printf("Read data: %d\n",data);
		//printf("Readers = %d and Writers = %d\n",rc,wc);
		
		sem_wait(&rlock);
		rc--;
		if(rc==0){
			sem_post(&resource);
		}
		sem_post(&rlock);
}

int main(){
		sem_init(&rlock,0,1);
		sem_init(&wlock,0,1);
		sem_init(&resource,0,1);
		sem_init(&readTry,0,1);
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
