/*
 * kernel.c
 *
 *  Created on: Feb 9, 2020
 *      Author: marwankhan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "memorymanager.h"

PCB* myinit(int pID, int pages_max);
void addToReady(PCB *newPCB);
int scheduler();
int main(void);
void boot();
int kernel();
int pageFault();

int quanta = 2;

struct PCB *head, *tail;


int main(void){

	 int errCode=0;
	 boot(); // First : actions performed by boot
	 errCode = kernel(); // Second: actions performed by kernel

	 if(errCode == 5){
		 return 0;
	 }
	 return errCode;

}

void addToReady(PCB *newPCB){

	if(head == NULL){
		head = newPCB;
		tail = newPCB;
		newPCB->next = NULL;

	}else{
		tail->next = newPCB;
		tail= newPCB;
		newPCB->next = NULL;

	}
}


int kernel(){

	int errCode=0;

	char mkdir[100];
	strcpy(mkdir, "mkdir BackingStore");


	errCode = shellUI();

	char rmdir[100];
	strcpy(rmdir, "rm -rf BackingStore");
	system(rmdir);
	system(mkdir);



	return errCode;
}

PCB* myinit(int pID, int pages_max){

	PCB* newPCB = makePCB(pID, pages_max);
	addToReady(newPCB);
 	return newPCB;
}

int scheduler(){

	int code = 0;

	while(head != NULL){

		setIP(head->pageTable[head->PC_page]);

		cpu.offset = head->PC_offset;
		code = run(quanta);
		head->PC_offset = cpu.offset;


		if(code == 1 || head->PC_page >= head->pages_max){

			//if program is ending then free the pcb
			PCB *remove = head;
			head = head->next;
			remove->next=NULL;
			free(remove);
			continue;

		}

		if(head != tail){

			//add to ready queue
			PCB *toRemove = head;
			head = head->next;
			toRemove->next = NULL;
			tail->next = toRemove;
			tail = toRemove;

		}
	}

	initializeRAM();
	resetInd();
	head = NULL;
	tail= NULL;

	return code;
}

void boot(){

	initializeRAM();

//	char command[50];
//	strcpy( command, "rm BackingStore" );
//	system(command);

	char command2[50];
	strcpy(command2, "rm -rf BackingStore" );
	system(command2);

	char mkdir[100];
	strcpy(mkdir, "mkdir BackingStore");
	system(mkdir);

}

int pageFault(){

	int code;

	head->PC_page++;
	int page = head->PC_page;

	if(head->PC_page >= head->pages_max){
		//terminate pcb code
		code = 1;
	}else{

		code = 2;
		FILE *fp;

		if(head->pageTable[head->PC_page] != -1){
			head->PC = head->pageTable[page];
			head->PC_offset = 0;
		}else if(head->pageTable[head->PC_page] == -1){
			if(head->pID==1){
				fp = fopen("BackingStore/1.txt","r");
			}else if(head->pID==2){
				fp = fopen("BackingStore/2.txt","r");
			}else if(head->pID==3){
				fp = fopen("BackingStore/3.txt","r");
			}

			int frame = findFrame();

			if(frame != -1){
				head->pageTable[page] = frame;
				loadPage(page, fp, frame);

			}else if(frame == -1){
				int victim = findVictim(head);
				frame = victim;
				updatePageTable(head, page, frame, victim);

				loadPage(page, fp, victim);
			}

			head->PC = head->pageTable[page];
			head->PC_offset = 0;

			fclose(fp);
		}
	}


	return code;

}



