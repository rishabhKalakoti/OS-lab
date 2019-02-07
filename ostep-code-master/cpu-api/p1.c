#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int v=10;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        v+=5;
        
        printf("Child %d\n",v);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("Hello\n");
        wait(NULL);
    } else {
    	v+=2;
        // parent goes down this path (original process)
        printf("Parent %d\n",v);
        printf("hello, I am parent of %d (pid:%d)\n",
	       rc, (int) getpid());
	sleep(1);
	printf("goodbye\n");
    }
    return 0;
}
