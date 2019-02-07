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
				s[strlen(s)-1]=s[strlen(s)];
				int i=0;
				for(;i<strlen(s);i++)
				{
					if(s[i]==' ')
					{
						break;
					}
				}
				char s1[100];
				char s2[100];
				memcpy(s1, &s[0], i );
				s1[i] = '\0';
				s2[0]=0;
				i++;
				if(i<strlen(s))
				{
					memcpy(s2, &s[i],strlen(s)-i);
					s2[strlen(s)-i]='\0';
				}
				char *myargs[3];
				myargs[0] = strdup(s1);
				if(s2[0]!=0)
					myargs[1] = strdup(s2);
				else
					myargs[1] = NULL;
				myargs[2] = NULL;
				execvp(myargs[0], myargs);
				exit(0);
			}
			else if(f>0)
			{
				wait(NULL);
				printf(">> ");
				fgets(s,100,stdin);
			}
		}
	}
	return 0;
}
