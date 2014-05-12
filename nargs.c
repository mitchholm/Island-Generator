#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Returns the index of the argument if its present, otherwise 0
int isPresent(int argc, char** argv, char* test){
	for(int i = 1; i < argc; ++i)
		if(!strncmp(&argv[i][1], test, strlen(test)) &&
		 		(argv[i][strlen(test)+1] == '=' || argv[i][strlen(test)+1] == '\0'))
			return i;
	return 0;
}

//Returns the index of the part of the argument after the equal sign
char* argString(int argc, char** argv, char* test){
	for(int i = 1; i < argc; ++i)
		if(!strncmp(&argv[i][1], test, strlen(test)) && argv[i][strlen(test)+1] == '=')
			return &argv[i][strlen(test) + 2];
	return 0;
}

//Returns the double after the equal sign 
double argDouble(int argc, char** argv, char* test){
	for(int i = 1; i < argc; ++i)
		if(!strncmp(&argv[i][1], test, strlen(test)) &&
		 		(argv[i][strlen(test)+1] == '=' || argv[i][strlen(test)+1] == '\0')){
			char* error;
			double temp = strtod(&argv[i][strlen(test) + 2], &error);
			if(error != NULL)
				return temp;
			else
				continue;
		}	
	return 0;
}

int argInt(int argc, char** argv, char* test){
	for(int i = 1; i < argc; ++i)
		if(!strncmp(&argv[i][1], test, strlen(test)) &&
		 		(argv[i][strlen(test)+1] == '=' || argv[i][strlen(test)+1] == '\0'))
			return atoi(&argv[i][strlen(test) +2]);
	return 0;
}