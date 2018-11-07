#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <iostream>
#include <cassert>
#include <cstring>
#include "cpu.h"
#include "files.h"


int assemble(const char inpFileName[], const char outFileName[]);

int load_binary(uint8_t arr[], FILE *ptrFile);

int disassemble(const char inpFileName[], const char outFileName[]);


#endif // ASSEMBLER_H
