#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

int shellUI(){


	char prompt[100] = {'$','\0'};
	char userInput[1000];
	int errorCode = 0;

    printf("Kernal 3.0 loaded!\nWelcome to the Marwan shell! \nVersion 3.0 Updated February 2020\n");


    while(1){

    	printf("%s ",prompt);
    	fgets(userInput, 999, stdin);
    	fflush(stdout);

    	errorCode = parseInput(userInput);

    	if (errorCode == -1){
    		exit(99); // ignore all other errors
    	}else if(errorCode == 1){
    		printf("Unknown Command\n");
    	}else if(errorCode == 5){
    		return 0;
    	}else if(errorCode == 2){
    		printf("Variable does not exist\n");
    	}else if(errorCode == 3){
    		printf("Script not found\n");
    	}else if(errorCode == 6){
    		printf("RAM full\n");
    	}

	}


}

