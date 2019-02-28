#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/shm.h> 
#include <sys/wait.h> 
#include<pthread.h>

int	shmID, shrID, shrID2, fav;		
key_t 	key1 = 54991, key2 = 784519, key3 = 882363, key4 = 23456;
int	*p1_wants_to_enter,*p2_wants_to_enter, *shared,*favored; 
int n=0;
pthread_t threads[100];
int ticket[100];
int choose[100];
void* func(void* num){
	int x = (int)(num);
	
	for(int done = 0;done<4;done++){
		choose[x] = 1;
		int max = 0;
		for(int i=0;i<n;i++){
			if(ticket[i]>max){
				max = ticket[i];
			}
		}
		choose[x] = 0;
		ticket[x] = max + 1;
		for(int i = 0;i<n;i++){
			while(choose[i] == 1)
				;
			while(ticket[i] != 0 && ((ticket[i]<ticket[x]) || (ticket[i]==ticket[x] && i<x)));
		}
		*shared += 10;
		printf("Thread number = %d, shared memory = %d\n",x,*shared);
	}
	ticket[x] = 0;
	
}
int main(){
	shmID = shmget(key1, sizeof(int), IPC_CREAT | 0660);
	if(shmID < 0){
		printf("Shared memory 1 could not be allocated\n");
		exit(1);
	}
	shrID = shmget(key2, sizeof(int), IPC_CREAT | 0660);
	if(shrID < 0){
		printf("Shared memory 2 could not be allocated\n");
		exit(1);
	}
	shrID2 = shmget(key3, sizeof(int), IPC_CREAT | 0660);
	if(shrID < 0){
		printf("Shared memory 3 could not be allocated\n");
		exit(1);
	}
	fav = shmget(key4, sizeof(int), IPC_CREAT | 0660);
	if(fav < 0){
		printf("Shared memory 4 could not be allocated\n");
		exit(1);
	}
	p1_wants_to_enter = (int *)shmat(shmID, NULL, 0); 
	favored= (int *)shmat(fav, NULL, 0); 
        if (p1_wants_to_enter == (int *)-1 ) {
            printf("Failed to attach p1_wants_to_enter to first process\n");
            exit(-1); 
        } 
	p2_wants_to_enter = (int *)shmat(shrID2, NULL, 0); 
        if (p2_wants_to_enter== (int *)-1 ) {
            printf("Failed to attach p2_wants_to_enter to first process\n");
            exit(-1); 
        } 
    	shared = (int *)shmat(shrID, NULL, 0); 
        if (shared == (int *)-1 ) {
            printf("Failed to attach shared to first process\n");
            exit(-1); 
        } 

  	if (favored == (int *)-1 ) {
            printf("Failed to attach favoured to first process\n");
            exit(-1); 
        } 
        
        *shared = 1;
        printf("Enter number of threads\n");
        scanf("%d",&n);
        for(int i=0;i<n;i++){
        	ticket[i] = 0;
        	choose[i] = 0;
        }
        for(int i=0;i<n;i++){
        	pthread_create(&threads[i], NULL, &func, (void*)((int)(i+1)));
        }
	for(int i=0;i<n;i++){
		pthread_join(threads[i],NULL);
	}

}
