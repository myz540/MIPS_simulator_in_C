/*
Mike Zhong
CS575 Operating Systems
Professor Yuting Zhang
*/

#ifndef _INSTRUCTION_SET_H
#define _INSTRUCTION_SET_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "mips_types.h"

// MIPS instruction set
// R-type instructions
void add(instruction i, memory* p);
void sub(instruction i, memory* p);
void or(instruction i, memory* p);
void and(instruction i, memory* p);
void slt(instruction i, memory* p);
void sll(instruction i, memory* p);
void srl(instruction i, memory* p);
void jr(instruction i, memory* p);

// I-type instructions
void lw(instruction i, memory* p);
void sw(instruction i, memory* p);
void addi(instruction i, memory* p);
void ori(instruction i, memory* p);
void andi(instruction i, memory* p);
void slti(instruction i, memory* p);
void beq(instruction i, memory* p);
void bne(instruction i, memory* p);
void lui(instruction i, memory* p);

// J-type instructions
void j(instruction i, memory* p);
void jal(instruction i, memory* p);

static inline void (*get_j_instruction(uint32_t opcode))(instruction, memory*) {
	// if opcode type is for J instruction
	switch (opcode) {
		case 0x2:
			return &j;
		case 0x3:
			return &jal;
		default:
			printf("Invalid opcode value in instruction: %d\n", opcode);
			exit(-1);
	}
}

static inline void (*get_r_instruction(uint32_t function))(instruction, memory*) {
	// if opcode type is for R instruction
	switch (function) {
		case 0x20:
			return &add;
		case 0x22:
			return &sub;
		case 0x25:
			return &or;
		case 0x24:
			return &and;
		case 0x2a:
			return &slt;
		case 0x0:
			return &sll;
		case 0x2:
			return &srl;
		case 0x8:
			return &jr;
		default:
			printf("Invalid function value in instruction: %d\n", function);
			exit(-1);
	}
}

// function pointer for I-type instructions, takes in opcode 
static inline void (*get_i_instruction(uint32_t opcode))(instruction, memory*) {
	// if opcode type is for I instruction
	switch(opcode){
		case 0x23:
			return &lw;
		case 0x2b:
			return &sw;
		case 0x8:
			return &addi;
		case 0xd:
			return &ori;
		case 0xc:
			return &andi;
		case 0xa:
			return &slti;
		case 0x4:
			return &beq;
		case 0x5:
			return &bne;
		case 0xf:
			return &lui;
		default:
			printf("Invalid opcode value in instruction: %d\n", opcode);
			exit(-1);
	}
}

static inline void (*get_instruction(instruction i))(instruction, memory*) {
	
	switch(i.opcode){
			// opcode 0x00 is for R-type instructions
			// pass i.function to the get_r_instruction function
			case 0:
				printf("Get R instruction with function: %d, sa: %d, rd: %d, rs: %d, rt: %d\n", i.function, i.sa, i.rd, i.rs, i.rt);
				return get_r_instruction(i.function);
			// opcode 0x02 and 0x03 are for J-type instructions
			// pass i.opcode to get_j_instruction function
			case 2:
			case 3:
				printf("Get J instruction with opcode: %d, instruction_idx: %d\n", i.opcode, i.instruction_idx);
				return get_j_instruction(i.opcode);
			// all other opcodes for I-type instructions
			// pass i.opcode to get_i_instruction function
			default:
				printf("Get I instruction with opcode: %d, rs: %d, rt: %d, imm: %d\n", i.opcode, i.rs, i.rt, i.imm);
				return get_i_instruction(i.opcode);
	}
}

#endif
