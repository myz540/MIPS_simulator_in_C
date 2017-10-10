/*
Mike Zhong
CS575 Operating Systems
Professor Yuting Zhang
*/

#ifndef _MIPS_TYPES_H
#define _MIPS_TYPES_H

#include <stdint.h>

#define MB (1024 * 1024) // megabyte
#define MEMORY_SIZE (8 * MB) // 8 MB memory
#define TEXT_SIZE 8192 // 8 KB memory dedicated for text
#define DATA_SIZE (MEMORY_SIZE - TEXT_SIZE) // Remaining memory is for data

typedef struct _instruction instruction; // typedef for instruction
typedef struct _memory memory; // 

struct _instruction{

	// all MIPS instructions are 32-bit
	union{
		uint32_t data; // arbitrary 32-bit field

		// struct for register type instructions
		struct{
			uint32_t function:6; // function
			uint32_t sa:5;	// shift
			uint32_t rd:5;	// dest
			uint32_t rt:5;	// source 1
			uint32_t rs:5;	// source 2
			uint32_t opcode:6;	// opcode
		};

		// struct for immediate type
		struct{
			union{
				int32_t imm:16; // immediate
				uint32_t z_imm:16; // zero
			};
			uint32_t _rt:5; // target
			uint32_t _rs:5; // source
			uint32_t _opcode:6; // opcode
		};

		// struct for J type
		struct{
			uint32_t instruction_idx:26; // encoded index of the instruction to jump to
			uint32_t __opcode:6; // opcode
		};
	};
};

struct _memory{

	// the machine's memory
	union{
		uint32_t mem_32[MEMORY_SIZE/4]; 
		struct{
			uint32_t text_32[TEXT_SIZE/4];
			uint32_t data_32[DATA_SIZE/4];
		};
	};

	// general purpose registers
	union{
		uint32_t reg[32];
		struct{
			uint32_t __unused[28];
			uint32_t gp; 
			uint32_t sp;
			uint32_t fp;
			uint32_t ra;
		};
	};
	
	uint32_t pc; // program counter
};

#endif
