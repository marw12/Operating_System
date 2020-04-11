/*
 *
 * memorymanager.c
 *
 *  Created on: Mar 12, 2020
 *      Author: marwankhan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "ram.h"
#include "kernel.h"

//Prototypes
int launcher(FILE *p);
int countTotalPages(FILE *f);
void loadPage(int pageNumber, FILE *f, int frameNumber);
int findFrame();
int findVictim(PCB *p);
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);
void resetInd();
int isVictim(PCB *p, int frameNum);
int updateVictim(int victimFrame);


int pageNo;
int frameNo;
int ind = 0;
int start;
int end;

int launcher(FILE *p) {

	int errCode = 0;

	char mv[100];
	char file[100];
	char dir[100];
	char touch[100];
	char filename[100];
	char c;
	FILE *p2;

	if(ind == 0){
		strcpy(filename, "1.txt");
		ind++;
	}else if(ind == 1){
		strcpy(filename, "2.txt");
		ind++;
	}else if(ind ==2){
		strcpy(filename, "3.txt");
		ind++;
	}else if(ind >3){
		printf("ERROR: too many files");
		exit(99);
	}

	strcpy(touch, "touch ");
	strcat(touch, filename);
	system(touch);

	//ptr to write to new file that will go in backing store
	p2 = fopen(filename, "w");
	if( p2 == NULL ) {
		printf("Error: write not found\n");
	}

	c = fgetc(p);
	while (!feof(p))
	{
		fputc(c, p2);
		c = fgetc(p);
	}

	fclose(p2);
	fclose(p);
	p = fopen(filename,"r"); //p points to file open in backing store

	//move new file to backing store directory
	strcpy(mv, "mv ");
	strcpy(file, filename);
	strcpy(dir, " BackingStore");

	strcat(mv, filename);
	strcat(mv, dir);
	system(mv);

	int  numOfPages = countTotalPages(p);
	int pid = ind;

	PCB* pcb = myinit(pid, numOfPages);

	if(numOfPages == 1){

		frameNo = findFrame();
		loadPage(0, p, frameNo);
		pcb->pageTable[0]=frameNo;

	}else if(numOfPages >= 2){

		frameNo = findFrame();
		loadPage(0,p,frameNo);
		pcb->pageTable[0]=frameNo;

		frameNo = findFrame();
		loadPage(1,p,frameNo);
		pcb->pageTable[1]=frameNo;
	}

	return errCode;
}


int countTotalPages(FILE *f){

	int output = 0;

	int count_lines = 0;
	char chr;

	//extract character from file and store in chr
	chr = getc(f);
	while (!feof(f))
	{
		//Count whenever new line is encountered
		if (chr == '\n')
		{
			count_lines = count_lines + 1;
		}
		//take next character from file.
		chr = getc(f);
	}

	count_lines++; //increment to take into account the last line

	if(count_lines <= 4){
		output = 1;
	}else if(count_lines > 4 && count_lines <= 8){
		output = 2;
	}else if(count_lines > 8 && count_lines <= 12){
		output = 3;
	}else if(count_lines > 12 && count_lines <= 16){
		output = 4;
	}else if(count_lines > 16 && count_lines <= 20){
		output = 5;
	}else if(count_lines > 20 && count_lines <= 24){
		output = 6;
	}else if(count_lines > 24 && count_lines <= 28){
		output = 7;
	}else if(count_lines > 28 && count_lines <= 32){
		output = 8;
	}else if(count_lines > 32 && count_lines <= 36){
		output = 9;
	}else if(count_lines > 36 && count_lines <= 40){
		output = 10;
	}

	return output;

}

void loadPage(int pageNumber, FILE *f, int frameNumber){

	rewind(f);

	char *line_buf = NULL;
	size_t line_buf_size = 0;
	int iter=0;
	int page = pageNumber * 4;

	for(int i=0; i<page; i++){
		getline(&line_buf, &line_buf_size, f);
	}

	while(iter<4 && getline(&line_buf, &line_buf_size, f) != -1){

		ram[frameNumber++]= strdup(line_buf);
		iter++;
	}

	free(line_buf);
	line_buf = NULL;

}

int findFrame(){

	int found = -1;
	int find=0;

	while(find<40){

		if(ram[find]==NULL){
			found = find;
			break;
		}

		find=find+4;
	}

	return found;
}

int findVictim(PCB *p){

	int output = -1;

	int frameNum = (rand() % 9 - 0 + 1)*4;

	while( output == -1){

		if(isVictim(p,frameNum)==1){
			output = frameNum;
			break;
		}else{
			if(frameNum==40){
				frameNum=0;
			}
			frameNum=frameNum+4;
		}
	}


	return output;

}

int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame){

	int errCode = 0;

	updateVictim(victimFrame);
	p->pageTable[pageNumber]=frameNumber;

	return errCode;
}


void resetInd(){
	ind = 0;
}

int isVictim(PCB *p, int frameNum){

	int output = 0;

	for(int i=0; i<10; i++){

		if(p->pageTable[i] != frameNum){
			output=1;
			break;
		}
	}

	return output;
}

int updateVictim(int victimFrame){

	int errCode = 0;
	PCB *check = head;

	while(check != NULL){

		for(int i=0; i<10; i++){
			if(check->pageTable[i]==victimFrame){

				check->pageTable[i]=-1;
				return 0;
			}
		}

		check = head->next;
		break;
	}

	return errCode;
}

