#ifndef STAKZ_PARSER_H
#define STAKZ_PARSER_H
#include "lexer.h"
#include "list.h"
#include "queue.h"
#include "token.h"

struct STAKZ_REGISTERS
{
    int W0;
    int NONE;
    int RETURN;
} STAKZ_REGISTERS;

typedef struct STAKZ_PARSER_STACKS
{
    list_t* op;
    node_t* output;  
    list_t* vars;
} stacks_t;

typedef struct STAKZ_PARSER
{
    lexer_t*  lexer;
    token_t*  token;
    stacks_t* stacks;
    struct STAKZ_REGISTERS set_registers;
    ssize_t   var_count;
    FILE*     file;
} parser_t;

parser_t* init_parser(lexer_t* lexer);
void parser_consume(parser_t* parser);
void parser_add_var(list_t* list, char* var);
#endif
