#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int main()
{
	char s[100];
	printf("Shell started.\n");
	printf(">> ");
	//scanf("%[^\n]s",s);
	fgets(s,100,stdin);
	int f;
	while(1)
	{
		if(strcmp(s,"exit\n")==0)
		{
			printf("Shell terminated.\n");
			break;
		}
		else
		{
			f = fork();
			if(f<0)
			{
				printf("Fork can not be created.\n");
				break;
			}
			else if(f==0)
			{
				printf("%s",s);
				exit(0);
			}
			else if(f>0)
			{
				wait(NULL);
				printf(">> ");
				//scanf("%[^\n]s",s);
				fgets(s,100,stdin);
			}
		}
	}
	return 0;
}
