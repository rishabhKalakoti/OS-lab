#include <stdio.h> 
#include <dirent.h> 

int main(int argc, char** argv[]) 
{
	
	struct dirent *de;
	// opendir() returns a pointer of DIR type.  
	DIR *dr = opendir("."); 

	if (dr == NULL)  // opendir returns NULL if couldn't open directory 
	{ 
	printf("Could not open current directory" ); 
	return 0; 
	} 

	while ((de = readdir(dr)) != NULL) 
	{
		printf("%s\n", de->d_name); 
	}
	closedir(dr);
	
	return 0; 
} 

