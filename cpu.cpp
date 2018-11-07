#include "cpu.h"

CPU CPU_init()
{
    CPU cpu;
    StackCtor(&cpu.st);
    cpu.regs[ip] = 0;
    return cpu;
}

int load_prog_stack(const char filename[], CPU *inpCpu)
{
    assert(filename != nullptr);
    assert(inpCpu != nullptr);

    FILE *ptrFileInp = open_inp_file(filename);
    for(int i = 0; fread(&(inpCpu->progStack[i]), sizeof(uint8_t), 1, ptrFileInp) == 1; i++);

    if (ferror(ptrFileInp) != 0)
        return 1;
    else return 0;
}


int run_cpu(CPU *inpCpu)
{
    assert(inpCpu != nullptr);

    for (uint8_t cmd = 0; (inpCpu->progStack[inpCpu->regs[ip]] != 0) && (inpCpu->regs[ip] < stack_size); inpCpu->regs[ip]++)
    {
        cmd = inpCpu->progStack[inpCpu->regs[ip]];
        switch (cmd)
        {
        case push: //push
        {
            inpCpu->regs[ip]++;
            uint8_t *valptr = &inpCpu->progStack[inpCpu->regs[ip]];
            int val = *(int*)valptr;
            inpCpu->regs[ip] += 3;
            Push_back(&inpCpu->st, val);
            break;
        }
        case add: //add
        {
            int val1 = Pop_back(&inpCpu->st);
            int val2 = Pop_back(&inpCpu->st);
            Push_back(&inpCpu->st, val1+val2);
            break;
        }
        case sub: //sub
        {
            int val1 = Pop_back(&inpCpu->st);
            int val2 = Pop_back(&inpCpu->st);
            Push_back(&inpCpu->st, val2-val1);
            break;
        }
        case mult: //mult
        {
            int val1 = Pop_back(&inpCpu->st);
            int val2 = Pop_back(&inpCpu->st);
            Push_back(&inpCpu->st, val1*val2);
        }
            break;
        case divis: //div
        {
            int val1 = Pop_back(&inpCpu->st);
            int val2 = Pop_back(&inpCpu->st);
            Push_back(&inpCpu->st, val1/val2);
        }
            break;
        case out: //out
        {
            int val = Pop_back(&inpCpu->st);
            printf("%d\n", val);
        }
            break;
        default:
        {
            puts("# Error: unknown command");
            printf("# Command: %d\n", cmd);
            return 1;
        }
        }
    }
    return 0;
}


