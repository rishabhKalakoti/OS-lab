#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/shm.h> 
#include <sys/wait.h> 
#include <pthread.h>

int shmVar,shmPtr;
int *var,*ptr;
key_t k1=61231,k2=34512,k3=23411,k4=657232;
int n=0;
int *ticketMem,*chooseMem;
/*
int ticket[100];
int choose[100];
*/
int **ticket;
int **choose;
void func(int num){
	ptr = (int *)shmat(shmPtr, NULL, 0); 
    if (ptr == (int *)-1 ) {
        printf("Error.\n");
        exit(-1); 
    } 
    var = (int *)shmat(shmVar, NULL, 0); 
    if (var == (int *)-1 ) {
        printf("Error.\n");
        exit(-1); 
    } 
	int x = (num);
	
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
		*var = *var + 10;
		printf("Thread [%d] in Critical Section (%d).\n", x,*var);
	}
	ticket[x] = 0;
	
}
int main(){
	shmVar = shmget(k1, sizeof(int), IPC_CREAT | 0660); // flag 
    if ( shmVar < 0 ) {
		printf("Error.\n");
		exit(1); 
    }
    shmPtr = shmget(k2, sizeof(int), IPC_CREAT | 0660); // flag 
    if ( shmPtr < 0 ) {
		printf("Error.\n");
		exit(1); 
    }
    ticketMem = shmget(k3, sizeof(int)*100, IPC_CREAT | 0660); // flag 
    if ( shmVar < 0 ) {
		printf("Error.\n");
		exit(1); 
    }
    chooseMem = shmget(k4, sizeof(int)*100, IPC_CREAT | 0660); // flag 
    if ( shmPtr < 0 ) {
		printf("Error.\n");
		exit(1); 
    }
    ptr = (int *)shmat(shmPtr, NULL, 0); 
    if (ptr == (int *)-1 ) {
        printf("Error.\n");
        exit(-1); 
    } 
    var = (int *)shmat(shmVar, NULL, 0); 
    if (var == (int *)-1 ) {
        printf("Error.\n");
        exit(-1); 
    }
    ticket = (int **)shmat(shmPtr, NULL, 0); 
    if (ptr == (int **)-1 ) {
        printf("Error.\n");
        exit(-1); 
    } 
    choose = (int **)shmat(shmVar, NULL, 0); 
    if (var == (int **)-1 ) {
        printf("Error.\n");
        exit(-1); 
    } 
    *ptr=-1;
    *var=0;
	
	n=8;
    
    for(int i=0;i<n;i++){
    	ticket[i] = 0;
    	choose[i] = 0;
    }
    
	int f1 = fork();
	int f2 = fork();
	int f2 = fork();
	
	func((int)getpid());
	
	if(f1>0 && f2>0 && f3>0)
	{
		int i;
		for(i=0;i<7;i++)
			wait(NULL);
	}
	
}
