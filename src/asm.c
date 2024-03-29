#include "includes/asm.h"
#include <stdlib.h>
#include <string.h>

asm_t* init_asm(char* cmd, int format)
{
    asm_t* line  = calloc(1, sizeof(struct STAKZ_ASM_T));
    line->cmd    = calloc(strlen(cmd), sizeof(char));
    line->cmd    = cmd;
    line->format = format;
    
    return line;
}

char* format_to_string(int format)
{
    switch(format)
    {
        case STDOUT:
            return "STDOUT";
        default:
            return "NOT FOUND";
    }
}