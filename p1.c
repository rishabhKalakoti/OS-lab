#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int a=100;
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        int b=100,c=200,d=300;
        a=a/2;
        printf("hello, I am child (pid:%d)\n  %p\n", (int) getpid(),&a);
        printf("Child:  A =%d (%p), B = %d (%p) c=%p d=%p \n",a,&a, b, &b,&c,&d);
        printf("xxx");
    } else {
        wait(NULL);
        int c=300;
        
 
        printf("hello, I am parent of %d (pid:%d)\n %p \n",
	       rc, (int) getpid(),&a);
        printf("Parent:  A =%d (%p), C = %d (%p)\n ",a,&a, c, &c);
    }
    return 0;
}

