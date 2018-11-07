#ifndef CPU_H
#define CPU_H

//commands:
//
//1: push
//2: add
//3: sub
//4: mult
//5: div
//6: out
//0: end
//
//regsistors:
//0-12 - general porpose
//13 - program counter
//
//----------------------------------------------------------------------------------------------------------------

#include "stack.h"
#include "files.h"

const int stack_size = 1024;

enum command_names
{finish, push, add, sub, mult, divis, out};

enum registors_names
{r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, ip};

struct CPU
{
    uint32_t regs[14] = {};
    Stack st;
    uint8_t progStack[stack_size] = {};
};

CPU CPU_init();

int load_prog_stack(const char filename[], CPU *inpCpu);

int run_cpu(CPU *inpCpu);



#endif // CPU_H
