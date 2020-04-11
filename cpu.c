/*
 * cpu.c
 *
 *  Created on: Feb 9, 2020
 *      Author: marwankhan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ram.h"
#include "interpreter.h"
#include "cpu.h"
#include "kernel.h"

void setIP(int ip);
int getIP();


int run(int quanta){

	int code = 0;
	int counter=0;

	while(counter < quanta){

		int ptr = cpu.IP + cpu.offset;

		if(ram[ptr] != NULL){
			strcpy(cpu.IR, ram[ptr]);
			parseInput(cpu.IR);
		}

		cpu.offset++;
		counter++;

		//interrupt
		if(cpu.offset == 4){

			code = pageFault();
			cpu.offset=0;
			break;
		}
	}

	return code;
}

void setIP(int ip){
	cpu.IP = ip;
}

int getIP(){

	return cpu.IP;
}


