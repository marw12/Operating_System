/*
 * pcb.h
 *
 *  Created on: Feb 20, 2020
 *      Author: marwankhan
 */

#ifndef PCB_H_
#define PCB_H_

typedef struct PCB {
	int PC;
	int pID;

	int pageTable[10];
	int PC_page;
	int PC_offset;
	int pages_max;

	struct PCB* next;
}PCB;

struct PCB* makePCB(int pID, int pages_max);

#endif /* PCB_H_ */
