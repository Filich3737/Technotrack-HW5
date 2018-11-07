#include "files.h"

FILE * open_inp_file(const char *filename)
{
    assert(filename != nullptr);
    FILE * ptrFile = fopen(filename, "r");
    if (ptrFile == nullptr)
    {
        printf("# Can't open file with name %s\n", filename);
        perror("# Error: ");
    }
    return ptrFile;
}

FILE * open_out_file(const char *filename)
{
    assert(filename != nullptr);
    FILE * ptrFile = fopen(filename, "wb");
    if (ptrFile == nullptr)
    {
        printf("# Can't create file with name %s\n", filename);
        perror("# Error: ");
    }
    return ptrFile;
}
