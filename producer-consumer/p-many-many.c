#include <stdio.h>
#include <time.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int p1[2],p2[2],p3[2];
int ind=-1,prod = 5,con = 5,buf_len = 4;
int buf[4];

int produce(){
	int i;
	char arr[100];
	//arr[0]='0';
	//arr[1]='\n';
	
	read(p1[0], arr, sizeof(char));
	while(arr[0]=='1')
		read(p1[0], arr, sizeof(char));
	arr[0]='1';
	write(p1[1], arr, sizeof(char));
	// crit
	printf("producer %d\n",(int)getpid());
	arr[0]='0';
	write(p1[1], arr, sizeof(char));
}

void consume(){
	int i;
	char arr[100];
	//arr[0]='0';
	//arr[1]='\n';
	
	read(p1[0], arr, sizeof(char));
	while(arr[0]=='1')
		read(p1[0], arr, sizeof(char));
	arr[0]='1';
	write(p1[1], arr, sizeof(char));
	// crit
	printf("consumer %d\n",(int)getpid());
	arr[0]='0';
	write(p1[1], arr, sizeof(char));
}

int main(){
	pipe(p1);
	int i=0;
	char arr[100];
	arr[0]='0';
	arr[1]='\n';
	write(p1[1], arr, sizeof(char));
	
	int f1=fork();
	if(f1 == 0)
	{
		fork();
		fork();
		fork();
		produce();
	}
	else
	{
		fork();
		fork();
		fork();
		consume();
	}

	return 0;
}
