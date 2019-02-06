#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int main()
{
	int i;
	char buff[100],buff1[100];
	char filename[] = "input.dat";
	int p1[2],p2[2],p3[2];
	FILE *file;
	file = fopen(filename,"r");
	if (pipe(p1) < 0 || pipe(p2) < 0 || pipe(p3) < 0) 
	{
	   perror("Can't open pipe\n");
	   exit(-1);
   	}
	int f1 = fork();
	if(f1 < 0)
	{
		printf("Error creating fork.\n");
		exit(-1);
	}
	else if(f1 == 0)
	{
		// process 2
		read(p1[0], buff, sizeof(buff));
		// manage spaces
		int j;
		j=0;
		i=0;
		// trim starting spaces
		while(buff[i]==' ') i++;
		for(;i<sizeof(buff)/sizeof(buff[0]);i++)
		{
			// multiple spaces
			if(buff[i]==' ')
			{
				if(j>0 && buff1[j-1]!=' ')
					buff1[j++]=' ';
			}
			// punctuation marks
			else if(buff[i]==',' || buff[i]=='.' || buff[i]=='?' || buff[i]=='!')
			{
				if(j>0 && buff1[j-1]==' ')
				{
					buff1[j-1]=buff[i];
					buff1[j++]=' ';
					
				}
				else
				{
					buff1[j++]=buff[i];
				}
			}
			// characters
			else
			{
				buff1[j]=buff[i];
				j++;
			}
		}
		printf("Process 2: %s", buff1);
		write(p2[1], buff1, sizeof(buff1));
	}
	else if(f1 > 0)
	{
		int f2 = fork();
		if(f2 < 0)
		{
			printf("Error creating fork.\n");
			exit(-1);
		}
		else if(f2 == 0)
		{
			// process 3
			read(p2[0], buff, sizeof(buff));
			for(i = 0;i<sizeof(buff)/sizeof(buff[0]);i++)
			{
				if(i==0)
				{
					if(buff[i]>='a' && buff[i]<='z')
					{
						buff[i]=buff[i]-'a'+'A';
					}
				}
				else
				{
					if(buff[i]>='A' && buff[i]<='Z')
					{
						buff[i]=buff[i]-'A'+'a';
					}
				}
			}
			printf("Process 3: %s",buff);
			int count = 0;
			for(i=0;i<sizeof(buff)/sizeof(buff[0]);i++)
			{
				if(buff[i]==' ')
					count++;
			}
			count++;
			write(p3[1], &count, sizeof(count));
		}
		else
		{
			// process 1
			while (fgets(buff, sizeof(buff), file) != NULL) {
				printf("Process 1: %s", buff);
				write(p1[1], buff, sizeof(buff));
			}
			int c;
			read(p3[0],&c,sizeof(c));
			printf("Process 1: Word count- %d\n",c);
		}
	}
   	return 0;
}
