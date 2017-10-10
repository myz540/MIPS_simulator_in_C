/*
Mike Zhong
CS575 Operating Systems
Professor Yuting Zhang
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mips_types.h"
#include "instruction_set.h"

// R type instructions
// rd = rs + rt
void add(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rs] + p->reg[i.rt];
}

// rd = rs - rt
void sub(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rs] - p->reg[i.rt];
}

// rd = rs | rt, bit-wise OR
void or(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rs] | p->reg[i.rt];
}

// rd = rs & rt, bit-wise AND
void and(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rs] & p->reg[i.rt];
}

// rs < rt => rd
void slt(instruction i, memory* p) {
	p->reg[i.rd] = (p->reg[i.rs] < p->reg[i.rt]);
}

// rd = rt << sa
void sll(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rt] << i.sa;
}

// rd = rt >> sa
void srl(instruction i, memory* p) {
	p->reg[i.rd] = p->reg[i.rt] >> i.sa;
}

// set pc := rs-4
void jr(instruction i, memory* p) {
	p->pc = p->reg[i.rs] - 4;
}

// I type instructions
// rt = mem_32[rs + imm]
void lw(instruction i, memory* p) {
	p->reg[i.rt] = p->mem_32[(p->reg[i.rs] + i.imm)/4];
}

// store mem_32[rs + imm/4] = rt
void sw(instruction i, memory* p) {
	p->mem_32[(p->reg[i.rs] + i.imm)/4] = p->reg[i.rt];
}

// rt = rs + imm
void addi(instruction i, memory* p) {
	p->reg[i.rt] = p->reg[i.rs] + i.imm;
}

// rt = rs | 0, bit-wise OR
void ori(instruction i, memory* p) {
	p->reg[i.rt] = p->reg[i.rs] | i.z_imm;
}

// rt = rs & imm, bit-wise AND
void andi(instruction i, memory* p) {
	p->reg[i.rt] = p->reg[i.rs] & i.imm;
}

// rs < imm => rt
void slti(instruction i, memory* p) {
	p->reg[i.rt] = (p->reg[i.rs] < i.imm);
}

// if(rs == rt) shift offset left two bits so there are two 0 bits and add it to pc
void beq(instruction i, memory* p) {
	if (p->reg[i.rs] == p->reg[i.rt]) {
		p->pc = p->pc + (i.imm << 2);
	}
}

// if rs != rt, shift offset left two bits so there are two 0 bits and add it to pc
void bne(instruction i, memory* p) {
	if (p->reg[i.rs] != p->reg[i.rt]) {
		p->pc = p->pc + (i.imm << 2);
	}
}

// shift immediate value left 16 bits and load value into register rt
void lui(instruction i, memory* p) {
	p->reg[i.rt] = (i.imm << 16);
}

// J type instructions
// take upper 4 bits of PC, append the 26 bit value in instruction_idx shifted over two
// to create an address that is 32-bit aligned. 
void j(instruction i, memory* p) {
	p->pc = ((p->pc >> 28) | (i.instruction_idx << 2)) - 4;
}

// save next instruction at reg[31] or ra and set pc to the address of the next instruction
void jal(instruction i, memory* p) {
	p->reg[31] = p->pc + 4;
	p->pc = ((p->pc >> 28) | (i.instruction_idx << 2)) - 4;
}
