#include "assembler.h"



int assemble(const char inpFileName[], const char outFileName[])
{
    assert(inpFileName != nullptr);
    assert(outFileName != nullptr);

    FILE *ptrFileInp = open_inp_file(inpFileName);
    assert (ptrFileInp != nullptr);
    FILE *ptrFileOut = open_out_file(outFileName);
    assert (ptrFileOut != nullptr);

    char str[100];
    while (fscanf(ptrFileInp, "%s", str) != EOF)
    {
        if (strcmp(str, "push") == 0)
        {
            uint8_t cmd = push;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);

            int val = 0;
            int res = fscanf(ptrFileInp, "%d", &val);
            assert(res != EOF);
            fwrite(&val, sizeof(int), 1, ptrFileOut);

        }
        else if (strcmp(str, "add") == 0)
        {
            uint8_t cmd = add;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else if (strcmp(str, "sub") == 0)
        {
            uint8_t cmd = sub;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else if (strcmp(str, "mult") == 0)
        {
            uint8_t cmd = mult;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else if (strcmp(str, "div") == 0)
        {
            uint8_t cmd = divis;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else if (strcmp(str, "out") == 0)
        {
            uint8_t cmd = out;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else if (strcmp(str, "end") == 0)
        {
            uint8_t cmd = finish;
            fwrite(&cmd, sizeof(uint8_t), 1, ptrFileOut);
        }
        else
        {
            puts("# Error: unknown command, break");
            return 1;
        }
    }
    puts("# Assembled");
    return 0;
}

int load_binary(uint8_t arr[], FILE *ptrFile)
{
    for (int i = 0; fread(&arr[i], 1, sizeof(uint8_t), ptrFile) != 0; i++);
    if (ferror(ptrFile) == 0)
        return 0;
    else
        return 1;
}

int disassemble(const char inpFileName[], const char outFileName[])
{
    assert(inpFileName != nullptr);
    assert(outFileName != nullptr);

    FILE *ptrFileInp = open_inp_file(inpFileName);
    assert (ptrFileInp != nullptr);
    FILE *ptrFileOut = open_out_file(outFileName);
    assert (ptrFileOut != nullptr);

    uint8_t prog_stack[stack_size] = {};
    int res = load_binary(prog_stack, ptrFileInp);
    assert(res == 0);

    for (int i = 0; i < stack_size; i++)
    {
        uint8_t cmd = prog_stack[i];
        switch (cmd)
        {
        case push: //push
        {
            fprintf(ptrFileOut, "push ");

            i++;
            uint8_t *valptr = &prog_stack[i];
            int val = *(int*)valptr;
            i += 3;
            fprintf(ptrFileOut, "%d\n", val);
            break;
        }
        case add: //add
        {
            fprintf(ptrFileOut, "add\n");
            break;
        }
        case sub: //sub
        {
            fprintf(ptrFileOut, "sub\n");
            break;
        }
        case mult: //mult
        {
            fprintf(ptrFileOut, "mult\n");
        }
            break;
        case divis: //div
        {
            fprintf(ptrFileOut, "div\n");
        }
            break;
        case out: //out
        {
            fprintf(ptrFileOut, "out\n");
        }
            break;
        case finish: //end
        {
            fprintf(ptrFileOut, "end\n");
            puts("# Disassembled");
            return 0;
        }
        default:
        {
            puts("# Error: unknown command");
            printf("# Command: %d\n", cmd);
            return -1;
        }
        }
    }
    puts("# Disassembled");
    return 0;
}
