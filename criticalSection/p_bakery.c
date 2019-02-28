#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/shm.h> 
#include <sys/wait.h> 
#include<pthread.h>
int n=0;
int var=0;
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
		var += 10;
		printf("Thread [%d] in Critical Section (%d).\n", x,var);
	}
	ticket[x] = 0;
	
}
int main(){
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
