#include "includes/stax.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("Usage:\n%s input.stx\n", argv[0]);
        return 1;
    }
    
    stax_compile_file(argv[1]);
    return 0;
}
