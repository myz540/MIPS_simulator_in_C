CC = gcc
CFLAGS = -Wall --std=gnu11

main: main.o instruction_set.o
	$(CC) -o main main.o instruction_set.o
main.o: main.c instruction_set.h mips_types.h
	$(CC) $(CFLAGS) -c -o main.o main.c
instruction_set.o: instruction_set.c instruction_set.h mips_types.h
	$(CC) $(CFLAGS) -c -o instruction_set.o instruction_set.c
