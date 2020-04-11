/*
 * pcb.c
 *
 *  Created on: Feb 9, 2020
 *      Author: marwankhan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct PCB {
	int PC;
	int pID;

	int pageTable[10];
	int PC_page;
	int PC_offset;
	int pages_max;

	struct PCB* next;
}PCB;

struct PCB* makePCB(int pID, int pages_max){

	PCB *newPCB = (PCB*)malloc(sizeof(PCB));

	newPCB->PC_page=0;
	newPCB->PC_offset=0;
	newPCB->next=NULL;
	newPCB->pID=pID;
	newPCB->pages_max=pages_max;

	for(int i=0; i<10; i++){
		newPCB->pageTable[i]=-1;
	}

	return newPCB;
}
