#include "includes/stakz.h" 
#include "includes/lexer.h"
#include "includes/token.h"
#include "includes/list.h"
#include "includes/parser.h"
#include "includes/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void stakz_compile(char* src, char* filename)
{
    pos_t* pos       = calloc(1, sizeof(struct STAKZ_IO_POSITION_STRUCT));
    pos->lineNumber  = 1;
    pos->filename    = filename;

    lexer_t* lexer   = init_lexer(src, pos);
    parser_t* parser = init_parser(lexer);
    void* popped     = NULL;
    
    while(parser->token->type != TOKEN_EOF)
    {
        parser_consume(parser);
        printf("[Program] TOKEN TYPE IS (%s) and TOKEN VAL IS (%s)\n", token_to_string(parser->token->type), parser->token->tok);
    }
    
    // Pop off of Stack
    if(parser->stacks->op->length < 1 && parser->stacks->output->length < 1) exit(0);
}

void stakz_compile_file(const char* filename)
{
    char* src = stakz_read_file(filename);
    printf("\033[1;4;35mSource File: %s\033[m\t\033[1;4;33mTotal File Size: %ld Bytes\n\n\033[m", filename, (sizeof(char) * (strlen(src) + 1)));
    stakz_compile(src, (char*) filename);
    free(src);
}
