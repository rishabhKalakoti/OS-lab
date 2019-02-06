#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int p1 = fork();
	int p2 = fork();
	int p3 = fork();
	if(p1 < 0 || p2 < 0 || p3 < 0)
	{
		printf("Some error occured.\n");
		exit(-1);
	}
	else if(p1 > 0 && p2 > 0 && p3 > 0)
	{
		printf("1\t PID:%d\t parent of %d, %d, %d\n",(int)getpid(),p1,p2,p3);
		wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);
	}
	else if(p1 > 0 && p2 > 0 && p3 ==0)
	{
		sleep(7);
		printf("1.3\t PID:%d\n",(int)getpid());
	}
	else if(p1 > 0 && p2 == 0 && p3 > 0)
	{
		sleep(5);
		printf("1.2\t PID:%d\t parent of %d\n",(int)getpid(),p3);
		wait(NULL);wait(NULL);
	}
	else if(p1 > 0 && p2 == 0 && p3 == 0)
	{
		sleep(6);
		printf("1.2.1\t PID:%d\n",(int)getpid());
		wait(NULL);
	}
	else if(p1 == 0 && p2 > 0 && p3 > 0)
	{
		sleep(1);
		printf("1.1\t PID:%d\t parent of %d, %d\n",(int)getpid(),p2,p3);
		wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);
	}
	else if(p1 == 0 && p2 > 0 && p3 == 0)
	{
		sleep(4);
		printf("1.1.2\t PID:%d\n",(int)getpid());
		wait(NULL);wait(NULL);wait(NULL);
	}
	else if(p1 ==0 && p2 == 0 && p3 > 0)
	{
		sleep(2);
		printf("1.1.1\t PID:%d\t parent of %d\n",(int)getpid(),p3);
		wait(NULL);wait(NULL);wait(NULL);wait(NULL);wait(NULL);
	}
	else if(p1 == 0 && p2 == 0 && p3 == 0)
	{
		sleep(3);
		printf("1.1.1.1\t PID:%d\n",(int)getpid());
		wait(NULL);wait(NULL);wait(NULL);wait(NULL);
	}
}
