#include<stdio.h> 
#include<dirent.h> 
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

struct node{
	char path[1000];
	int depth;
	struct node *next;
};

void bfs(char* root)
{
	struct node *tmp;
	tmp=(struct node*)malloc(sizeof(struct node));
	tmp->depth=1;
	tmp->next=NULL;
	strcpy(tmp->path,root);
	struct node *base=tmp;
	struct node *end=tmp;
	
	while(base!=NULL)
	{
		tmp=base;
		struct dirent *de;
		//printf("%s\n",tmp->path);
		DIR *dr = opendir(tmp->path);
		if(dr==NULL){
			//printf("Directory not found!\n");
			exit(-1);
		}
		while ((de = readdir(dr)) != NULL) 
		{
			if(strcmp((de->d_name),"..")==0 || strcmp((de->d_name),".")==0) 
				continue;
			int i;
			for(i=0;i<(tmp->depth);i++) printf("----");
			if((de->d_type)==DT_DIR)
			{
				printf("%s/\n", de->d_name);
				struct node *tmp1=NULL;
				tmp1=(struct node*)malloc(sizeof(struct node));				
				strcpy(tmp1->path,tmp->path);
				strcat(strcat(tmp1->path,"/"),(de->d_name));
				tmp1->depth=tmp->depth+1;
				end->next=tmp1;
				end=tmp1;
			}
			else
				printf("%s\n", de->d_name);
		}
		closedir(dr);
		base=base->next;
		free(tmp);
	}
}

void dfs(char* root, int lvl)
{
	char next[1000];
	struct dirent *de;
	DIR *dr = opendir(root);
	if(dr==NULL){
		printf("Directory not found!\n");
		exit(-1);
	}
	while ((de = readdir(dr)) != NULL) 
	{
		if(strcmp((de->d_name),"..")==0 || strcmp((de->d_name),".")==0) 
			continue;
		int i;
		for(i=1;i<lvl;i++) printf("|   ");
		printf("|");
		printf("---");
		// folder
		if((de->d_type)==DT_DIR)
		{
			printf("%s/\n", de->d_name);
			strcpy(next,root);
			strcat(strcat(next,"/"),(de->d_name));
			dfs(next, lvl+1);
		}
		else
			printf("%s\n", de->d_name);
	}
	
	closedir(dr);
}

int main(int argc, char** argv[]) 
{
	if(argc>2)
	{
		printf("Usage: myTree [PATH]\n");
		exit(-1);
	}
	printf("DFS implementation:\n");
	//printf("%s\n",(argc==2)? (argv[1]):getcwd(0,0));
	dfs(((argc==2)? (argv[1]):getcwd(0,0)),0);
	printf("\n");
	
	printf("BFS implementation:\n");
	//printf("%s\n",(argc==2)? (argv[1]):getcwd(0,0));
	bfs(((argc==2)? (argv[1]):getcwd(0,0)));
	
	return 0; 
}
