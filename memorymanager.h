/*
 * memorymanager.h
 *
 *  Created on: Mar 13, 2020
 *      Author: marwankhan
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_
#include "pcb.h"

int launcher(FILE *p);
int countTotalPages(FILE *f);
void loadPage(int pageNumber, FILE *f, int frameNumber);
int findFrame();
int findVictim(PCB *p);
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);
void resetInd();

#endif /* MEMORYMANAGER_H_ */
