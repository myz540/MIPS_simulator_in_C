/*
Mike Zhong
CS575 Operating Systems
Professor Yuting Zhang
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "mips_types.h"
#include "instruction_set.h"

// returns uint32_t representation of string delineated by a '\n'
static inline uint32_t my_atoi(char* c){
	uint32_t val = 0;
	while(*c != '\n'){
		val = (val << 1) + (*c == '1' ? 1 : 0);
		++c;
	}
	return val;
};

void load_program(int fd, memory* p);
void print_registers(memory* p);

int main(int argc, char* argv[]){
	
	// initialize fd and the machine's memory
	int fd;
	memory* p = malloc(sizeof(memory));
	if(!p){
		printf("Failed to allocate memory\n");
	}
	
	// set entire memory block to 0
	memset(p, 0, sizeof(memory));
	
	// open file specified by argv[1] for read only
	fd = open(argv[1], O_RDONLY);
	if(fd < 0){
		printf("Failed to open program\n");
	}

	// load program specified by fd into memory block p
	load_program(fd, p);

	// pc always points at next instruction, iterate through
	for(p->pc = 0; p->pc < MEMORY_SIZE; p->pc += 4){
		
		// copy 32-bit instruction into data portion of instruction
		instruction i;
		i.data = p->mem_32[p->pc/4];
		
		printf("Instruction is: %d\n", i.data);

		// if the instruction == 0, increment pc, print out registers, end of program
		if(i.data == 0) {
			printf("End of program detected, data == 0, exiting...\n");
			p->pc += 4;
			print_registers(p);
			return 0;
		}
		
		// get_instruction returns the RV of get_x_instruction, which returns the address
		// of the specific instruction to be executed. This address gets assigned to the
		// function pointer execute, and this gets called using the instruction and memory*
		void (*execute)(instruction, memory*) = get_instruction(i);
		
		// call execute with instruction i and memory block p
		execute(i, p);
		
		print_registers(p);
		printf("Press ENTER to execute next instruction\n");
		getchar();
	}
	return 0;
}

// loads program pointed to by fd into memory block p
void load_program(int fd, memory* p){
	
	// initialize variables
	char* c;
	size_t file_size;
	int i = 0;

	// place fd to end of the file 
	file_size = lseek(fd, 0, SEEK_END);
	// map from virtual address 0 to file_size, allow for reading only 
	c = mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);

	// get text portion of the program
	for(i = 0; *c != '\n'; ++i){
		p->text_32[i] = my_atoi(c);
		c = c + 33;
	}
	printf("Text loaded, %d lines\n", i);

	c++;

	// get data portion of program
	for(i = 0; *c != '\0'; ++i){
		p->data_32[i] = my_atoi(c);
		c = c + 33;
	}
	printf("Data loaded, %d lines\n", i);
}

void print_registers(memory* p){
	int i = 0;
	printf("%d:\t%s\t 0x%08x\n", i, "$zero", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$at", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$v0", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$v1", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$a0", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$a1", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$a2", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$a3", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t0", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t1", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t2", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t3", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t4", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t5", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t6", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t7", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s0", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s1", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s2", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s3", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s4", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s5", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s6", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$s7", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t8", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$t9", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$k0", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$k1", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$gp", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$sp", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$fp", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "$ra", p->reg[i]); ++i;
	printf("%d:\t%s\t 0x%08x\n", i, "pc", p->pc);
}
