#ifndef STAKZ_ASM_H
#define STAKZ_ASM_H

typedef struct STAKZ_ASM_T
{
    char* cmd;
    enum
    {
        STDOUT,
        VAR
    } format;
} asm_t;

asm_t* init_asm(char* cmd, int format);
char* format_to_string(int format);
#endif
