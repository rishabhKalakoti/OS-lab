#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
sem_t lock,resource;
int arr[10];
int count = 0;
void* writer(void* num){

		int k = (int)num;
		sem_wait(&resource);
			printf("Writer %d is writing\n",k);
			for(int i=0;i<10;i++){
				arr[i] = rand()%50;
			}
			printf("Reader count = %d\n",count);
		sem_post(&resource);
	
}
void* reader(void* num){
		int k = (int)num;
		sem_wait(&lock);
			count++;
			if(count == 1){
				sem_wait(&resource);
			}
			printf("Reader %d is reading\n",k);
			printf("Reader count = %d\n",count);
		sem_post(&lock);
		//cs
		sem_wait(&lock);
			count--;
			if(count==0){
				sem_post(&resource);
			}
		sem_post(&lock);
	
	
}

int main(){
		sem_init(&resource,0,1);
		sem_init(&lock,0,1);
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
