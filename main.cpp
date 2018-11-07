#include <iostream>
#include "cpu.h"
#include "assembler.h"

using namespace std;

const char before_asm[] = "/home/filipphristolubov/Programming/Технотрек/CPU_v3/PROGRAMS/prog1.asm";
const char object_file[] = "/home/filipphristolubov/Programming/Технотрек/CPU_v3/PROGRAMS/prog1.o";
const char after_asm[] = "/home/filipphristolubov/Programming/Технотрек/CPU_v3/PROGRAMS/prog1_out.asm";

int main()
{
    int res = 0;
    //res = assemble(before_asm, object_file);
    //assert(res == 0);

    //res = disassemble(object_file, after_asm);
    //assert(res == 0);

    CPU cpu = CPU_init();

    res = load_prog_stack(object_file, &cpu);
    assert(res == 0);

    res = run_cpu(&cpu);
    assert(res == 0);

    return 0;
}
