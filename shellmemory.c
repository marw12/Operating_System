#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shellMemory{
	char *variable;
	char *string;
};

struct shellMemory shellmemory[1000];

int i=0;

int write(char *var, char *str){

	int errCode=0;

	shellmemory[i].variable = strdup(var);
	shellmemory[i].string = strdup(str);

	printf("%s = %s", shellmemory[i].variable, shellmemory[i].string);

	i++;

	return errCode;
}

int check(char *var){

	int output=0; //if variable not present

	for(int j=0;j<i;j++){
		if( strcspn(shellmemory[j].variable, var) == 0){
			output=1; //if variable already present
		}
	}

	return output;
}

int read(char *var){

	int errCode=0;

	for(int j=0; j<i ; j++){
			if( strcspn(shellmemory[j].variable, var) == 0){

				printf("%s", shellmemory[j].string);
			}
	}

	return errCode;
}

int setval(char *var, char *str){

	int errCode=0;

	for(int j=0;j<i;j++){
			if( strcspn(shellmemory[j].variable, var) == 0){
				shellmemory[j].string = strdup(str);
				printf("%s = %s", shellmemory[j].variable, shellmemory[j].string);
			}
		}

	return errCode;
}



