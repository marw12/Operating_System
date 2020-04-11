/*
 * ram.h
 *
 *  Created on: Feb 17, 2020
 *      Author: marwankhan
 */

#ifndef RAM_H_
#define RAM_H_

int addToRAM(FILE *p, int *start, int *end);
void clearRAM(int end);
void initializeRAM();
char *ram[40];

#endif /* RAM_H_ */
