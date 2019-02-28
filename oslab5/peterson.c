#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
#include <sys/shm.h> 
#include <sys/wait.h> 

int	shmID, shrID, shrID2, fav;		
key_t 	key1 = 54991, key2 = 784519, key3 = 882363, key4 = 23456;
int	*p1_wants_to_enter,*p2_wants_to_enter, *shared,*favored; 

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
	*p1_wants_to_enter = 0;
        *p2_wants_to_enter = 0;
	*favored=1;
	if (fork() == 0) { 
	 	srand(time(0)); 
	    	p1_wants_to_enter = (int *)shmat(shmID, NULL, 0); 
		p2_wants_to_enter = (int *)shmat(shrID2, NULL, 0); 
		favored=(int *)shmat(fav, NULL, 0); 
	    	shared = (int *)shmat(shrID, NULL, 0); 
		if (p1_wants_to_enter == (int *)-1 ){
		    printf("Failed to attach p1_wants_to_enter to first process\n");
		    exit(-1); 
		} 
	 	if (p2_wants_to_enter == (int *)-1 ){
		    printf("Failed to attach p2_wants_to_enter to first process\n");
		    exit(-1); 
		} 
	 	if (favored == (int *)-1 ){
		    printf("Failed to attach favored to first process\n");
		    exit(-1); 
		} 

		if (shared == (int *)-1 ){
		    printf("Failed to attach shared variable to first process\n");
		    exit(-1); 
        	} 
		int done=0;
		for(done=0;done<=15;done++){
			*p1_wants_to_enter=1;
			*favored=1;
			while(*p2_wants_to_enter && (*favored==2));
			*shared+=10;
			printf("Process 1: %d\n",*shared);
			*p1_wants_to_enter=0;
	    	}

    	}
    	else {    
		if (fork() == 0){ 
		 	srand(time(0)); 
		 	p1_wants_to_enter = (int *)shmat(shmID, NULL, 0); 
			p2_wants_to_enter = (int *)shmat(shrID2, NULL, 0); 
			favored=(int *)shmat(fav, NULL, 0); 
			shared = (int *)shmat(shrID, NULL, 0); 
			if (p1_wants_to_enter == (int *)-1 ){
				printf("Failed to attach p1_wants_to_enter to first process\n");
				exit(-1); 
			} 
		 	if (p2_wants_to_enter == (int *)-1 ){
				printf("Failed to attach p2_wants_to_enter to first process\n");
				exit(-1); 
			} 
		 	if (favored == (int *)-1 ){
				printf("Failed to attach favored to first process\n");
				exit(-1); 
			} 

			if (shared == (int *)-1 ){
				printf("Failed to attach shared variable to first process\n");
				exit(-1); 
			} 
			int done=0;
			for(done=0;done<=15;done++){
				*p2_wants_to_enter=1;
				*favored=2;
				while(*p2_wants_to_enter && (*favored==1));
				*shared+=15;
				printf("Process 2: %d\n",*shared);
				*p2_wants_to_enter=0;
			}
   	    	} 
		else{
			sleep(1);		 	
			wait(NULL);
			wait(NULL);
		}
    	}

}
