#ifndef STAKZ_PARSER_H
#define STAKZ_PARSER_H
#include "lexer.h"
#include "list.h"
#include "token.h"

typedef struct STAKZ_PARSER_STACKS
{
    list_t* op;
    list_t* output;  
} stacks_t;

typedef struct STAKZ_PARSER
{
    lexer_t* lexer;
    token_t* token;
    stacks_t* stacks;
} parser_t;

parser_t* init_parser(lexer_t* lexer);
void parser_consume(parser_t* parser);
#endif
