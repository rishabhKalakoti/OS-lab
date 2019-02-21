#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define		READ	0
#define		WRITE	1

int  main(void) {
	int	pipefd[2];// Read-Write descriptors for pipe
	int	r, rid;		// Return values
	char	buf;		// Read (write) buffer for child (parent)
	int	id;
	FILE	*fd;		// File descriptor for parent.

	// Create a pipe. Two descriptors attached. 
	// First for READ and second for WRITE
	pipe(pipefd);
	fd = fopen("input.txt", "r");
	if(fd == NULL) {
		printf("Unable to open file input.txt. Quitting.\n");
		exit(0);
	}
	// Create a child process. 
	// For parent process, return value is PID of child 
	// For child process, return value is -1
	rid = fork();
	if(rid == -1) {			// Fork failed
		perror("Fork failed. Exiting.\n");		
		exit(0);
	} 
	else if( rid == 0) {		// Child process
		id = 0;
		close(pipefd[WRITE]);  
		write(STDOUT_FILENO, "Child: ", 7);
		do {
			r = read(pipefd[READ], &buf, 1); 
			if( r == -1) {
				perror("Read failed\n");
				break;
			}
			write(STDOUT_FILENO, &buf, 1);
		} while(buf != '#');
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[READ]);  
		write(STDOUT_FILENO, "Child exiting ..\n", 17);
		_exit(0);
	}
	else {
		close(pipefd[READ]);  
		do {
			if(feof(fd)) 
				break;
			else 
				fscanf(fd, "%c", &buf);
			write(pipefd[WRITE], &buf, 1);
		} while(1);
		buf = '#';	// To send a termination to child
		write(pipefd[WRITE], &buf, 1);
		close(pipefd[WRITE]);  
		fclose(fd);
		// Wait for child to exit
		wait(NULL);
		write(STDOUT_FILENO, "Parent exiting ..\n", 18);
		exit(0);
	}
	return 0;
}
