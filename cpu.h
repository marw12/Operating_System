/*
 * cpu.h
 *
 *  Created on: Feb 26, 2020
 *      Author: marwankhan
 */

#ifndef CPU_H_
#define CPU_H_

typedef struct CPU {
	int IP; // points to the next instruction to execute from ram[]
	char IR[1000]; //currently executing instruction is stored
	int quanta;
	int offset;
}CPU;

CPU cpu;

int run(int quanta);
void setIP(int ip);
int getIP();



#endif /* CPU_H_ */
