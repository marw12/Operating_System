/*
 * ram.c
 *
 *  Created on: Feb 9, 2020
 *      Author: marwankhan
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"

//void clearRAM(int end);
//int addToRAM(FILE *p, int *start, int *end);
void initializeRAM();

char *ram[40];

void initializeRAM(){

	for(int i = 0; i<40; i++){

		ram[i]=NULL;
	}

}

