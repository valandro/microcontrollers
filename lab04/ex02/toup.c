#include <stdio.h>
#include <stdlib.h>
#include <touppercase.h>

int main(int argc,char *argv[])
{	
	if(argc != 2)
	{
		printf("Usage:\n\t%s <string>\n",argv[0]);
		return -1;
	}
		
	printf("input: %s\n", argv[1]);
	to_uppercase(argv[1]);

	printf("\n");
	
	return 0;
}