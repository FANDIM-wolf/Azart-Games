#include <stdio.h>
#include <stdlib.h>

// function for print critics errors
void fatal(char * message) {

	char error_message[100];

	strcpy(error_message, "Critics error!");
    strncat(error_message , message, 83);
    perror(error_message);
    exit(-1);
}

//function with malloc
void *ec_malloc(unsigned int size){

	void *ptr;
	ptr = malloc(size);
	if(ptr == NULL)
	{
		fatal("there is error here");
	}
	return ptr;
}