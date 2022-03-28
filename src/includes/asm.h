#ifndef STAKZ_ASM_H
#define STAKZ_ASM_H

typedef struct STAKZ_ASM_T
{
    char* cmd;
    enum
    {
        STDOUT,
        VAR,
        RETURN,
        ADDITION
    } format;
} asm_t;

// int init_asm(int format);
char* format_to_string(int format);
#endif
