/*
 * kernel.h
 *
 *  Created on: Feb 19, 2020
 *      Author: marwankhan
 */

#ifndef KERNEL_H_
#define KERNEL_H_
#include "pcb.h"

struct PCB *head, *tail;

PCB* myinit(int pID, int pages_max);
int scheduler();
int pageFault();


#endif /* KERNEL_H_ */
