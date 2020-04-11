#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "kernel.h"
#include "memorymanager.h"

//prototypes
int interpreter(char *words[]);
int help();
int quit();
int set(char *words[]);
int print(char *words[]);
int static run(char *words[]);
int exec(char *words[]);
char *clear(char *word);

int args=0;

int parseInput(char ui[]){

		int w=0;
		char *words[100];
		char delim[] = " ";
		char input1[50]="";
		char input2[50]="";
		char input3[50]="";
		char input4[50]="";


		char *ptr = strtok(ui, delim);

		if(ptr != NULL)
		{
			strcpy(input1,ptr);
			ptr = strtok(NULL, delim);
			words[w++] = strdup(input1);

		}else{
			printf("no input\n");
			return 0;
		}

		if(ptr!=NULL){
			strcpy(input2,ptr);
			ptr = strtok(NULL, delim);
			words[w++]=strdup(input2);

		}
		if(ptr!=NULL){
			strcpy(input3,ptr);
			ptr = strtok(NULL, delim);
			words[w++]=strdup(input3);

		}
		if(ptr!=NULL){
			strcpy(input4,ptr);
			ptr = strtok(NULL, delim);
			words[w++]=strdup(input4);

		}

		args=w;

	return interpreter(words);
}

int interpreter(char *words[]) {

	int errCode = 0;

	clear(words[0]);

	if(strcmp(words[0], "help")==0){
		errCode= help();
	}else if(strcmp(words[0], "quit")==0){
		errCode= quit();
	}else if(strcmp(words[0], "set")==0){
		errCode=set(words);
	}else if(strcmp(words[0], "print")==0){
		errCode= print(words);
	}else if(strcmp(words[0], "run")==0){
		errCode = run(words);
	}else if(strcmp(words[0], "exec")==0){
		errCode = exec(words);
	}else{
		errCode=1;
	}

	return errCode;

}

int help() {

	int errCode=0;

	printf("help: Displays all commands\n");
	printf("quit:Exits the shell with \"Bye!\"\n");
	printf("set VAR STRING: Assigns a value to shell memory\n");
	printf("print VAR: Displays the STRING assigned to VAR\n");
	printf("run SCRIPT: Executes the file SCRIPT.TXT\n");

	return errCode;

}

int quit() {

	int errCode=5;
	printf("Bye!\n");

	return errCode;

}

int set(char *words[]) {

	int errCode=0;

	clear(words[1]);


	if(check(words[1])==0){ //if variable does not exist
		write(words[1],words[2]);
	}else if(check(words[1])==1){ ////if variable exists
		setval(words[1],words[2]);
	}

	return errCode;
}

int print(char *words[]) {

	int errCode=0;


	if(check(words[1])==0){ //if variable does not exist
		errCode=2;
	}else if(check(words[1])==1){ ////if variable exists
		read(words[1]);
	}

	return errCode;
}

int static run(char *words[]) {

		int errCode = 0;

		clear(words[1]);
		FILE *p = fopen(words[1], "r");
		char line[1000];

		if( p == NULL ) {
			errCode=3;
			return errCode;
		}

		fgets(line,999,p);


		while(!feof(p)) {
			errCode = parseInput(line); // which calls interpreter()

			if (errCode != 0) {
				fclose(p);
				return errCode;
			}else if(errCode == 5){
				errCode = 0;
				break;
			}



			fgets(line,999,p);
		}

		fclose(p);
		return errCode;
}

int exec(char *words[]) {

	int errCode=0;
	int i=1;

//	if(args == 3){
//		clear(words[1]);
//		clear(words[2]);
//
//		if(strcmp(words[1],words[2]) == 0){
//			printf("Error: duplicate file %s\n", words[1]);
//			return 0;
//		}
//	}
//
//	if(args==4){
//
//		clear(words[1]);
//		clear(words[2]);
//		clear(words[3]);
//
//		if( strcmp(words[1],words[3]) == 0 ){
//			printf("Error: duplicate file %s\n", words[1]);
//			return 0;
//		}
//
//		else if(strcmp(words[2],words[3]) == 0){
//			printf("Error: duplicate file %s\n", words[2]);
//			return 0;
//		}
//	}

	while(i<args){
		char *filename = clear(words[i]);
		FILE *p = fopen(filename, "r");

		if( p == NULL ) {
			printf("Error: %s not found\n", words[i]);
			return 0;
		}else{
			errCode = launcher(p);
			//errCode=myinit(filename);
			if(errCode ==7){
				printf("Error: RAM is full!\n");
				return 0;
			}

		}
		i++;
	}

	scheduler();

	return errCode;
}

//helper used to remove \n and \r
char *clear(char *word){
	char *pos;

	if ((pos=strchr(word, '\n')) != NULL){
			*pos = '\0';
	}
	if ((pos=strchr(word, '\r')) != NULL){
			*pos = '\0';
	}

	return word;
}



