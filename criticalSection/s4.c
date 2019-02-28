#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
//#include <sys/types.h> 
//#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/wait.h> 


#define	FIRST		1
#define	SECOND		2

int	shmID1,shmID2, 		// identifier for shared memory to store processNumber
	shrID; 		// identifier for shared memory to store shared value
key_t 	key1 = 54991, key2 = 784519,key3 = 560501;
int	*shared; 
int *p1_wantstoenter,*p2_wantstoenter;

int main() { 
    shmID1 = shmget(key1, sizeof(int), IPC_CREAT | 0660); // flag 
    if ( shmID1 < 0 ) {
        printf("Shared memory 1 could not be allocated. Quitting.\n");
        exit(1); 
    } 

    shmID2 = shmget(key2, sizeof(int), IPC_CREAT | 0660); // flag 
    if ( shmID2 < 0 ) {
        printf("Shared memory 2 could not be allocated. Quitting.\n");
        exit(1); 
    }
    shrID = shmget(key3, sizeof(int), IPC_CREAT | 0660); // flag 
    if ( shrID < 0 ) {
        printf("Shared memory 2 could not be allocated. Quitting.\n");
        exit(1); 
    } 

    // Initialization is done in parent process
    	// shmat : attach shared memory segment. Returns (void *)-1 on failure else
    	// Attaches shared segment identified with shmID to an address 
    	// processNumber in process address space

    	p1_wantstoenter = (int *)shmat(shmID1, NULL, 0); 
        if (p1_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to first process. Quitting.\n");
            exit(-1); 
        } 
        p2_wantstoenter = (int *)shmat(shmID2, NULL, 0); 
        if (p2_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to first process. Quitting.\n");
            exit(-1); 
        } 
    	shared = (int *)shmat(shrID, NULL, 0); 
        if (shared == (int *)-1 ) {
            printf("Failed to attach shared variable to first process. Quitting.\n");
            exit(-1); 
        } 
	*shared = 0;
	//*processNumber = FIRST;
	*p1_wantstoenter = 0;
	*p2_wantstoenter = 0;

    // Create First (child) process
    if (fork() == 0) { 
    	p1_wantstoenter = (int *)shmat(shmID1, NULL, 0); 
        if (p1_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to first process. Quitting.\n");
            exit(-1); 
        } 
        p2_wantstoenter = (int *)shmat(shmID2, NULL, 0); 
        if (p2_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to first process. Quitting.\n");
            exit(-1); 
        } 
    	shared = (int *)shmat(shrID, NULL, 0); 
        if (shared == (int *)-1 ) {
            printf("Failed to attach shared variable to first process. Quitting.\n");
            exit(-1); 
        } 

	// This is the code first process executes

 	for(int i=0; i < 20; i++) { 
		*shared = *shared % 5;
        	*p1_wantstoenter = 1;
        	
        	while(*p2_wantstoenter)
        	{	
        		*p1_wantstoenter=0;
			int k = (int) ((5.0*rand())/RAND_MAX);
			sleep(k);
			*p1_wantstoenter=1;
		}
		// Critical Section Begin 
		*shared = *shared+1;		

		printf("[%d] First: Critical Section (%2d).\n",i+1, *shared);
		*p1_wantstoenter = 0;
	}
    } 
    else {
    // Create second (child) process
    if (fork() == 0) { 
    	p1_wantstoenter = (int *)shmat(shmID1, NULL, 0); 
        if (p1_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to second process. Quitting.\n");
            exit(-1); 
        } 
        p2_wantstoenter = (int *)shmat(shmID2, NULL, 0); 
        if (p2_wantstoenter == (int *)-1 ) {
            printf("Failed to attach processNumber to second process. Quitting.\n");
            exit(-1); 
        } 

    	shared = (int *)shmat(shrID, NULL, 0); 
        if (shared == (int *)-1 ) {
            printf("Failed to attach shared variable to second process. Quitting.\n");
            exit(-1); 
        } 


	// This is the code second process executes

 	for(int i=0; i < 20; i++) { 
        	*p2_wantstoenter=1;
        	
        	while(*p1_wantstoenter)
		{
			*p2_wantstoenter=0;
			int k = (int) ((5.0*rand())/RAND_MAX);
			sleep(k);
			*p2_wantstoenter=1;
		}
		// Critical Section Begin 
		*shared = *shared+1;		
		printf("[%d] Second: Critical Section (%2d).\n",i+1, *shared);
		*p2_wantstoenter = 0;
	}
    } 
    else {
 	for(int i=0; i < 20; i++) { 
		*shared = *shared+12;		
		printf("[%d] Parent: Critical Section (%2d).\n",i+1, *shared);
	}
    	wait(NULL);
    	wait(NULL);
    }
    }
} 
