#include "includes/stakz.h" 
#include "includes/lexer.h"
#include "includes/token.h"
#include "includes/list.h"
#include "includes/parser.h"
#include "includes/io.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void stakz_compile(char* src)
{
    pos_t* pos       = calloc(2, sizeof(size_t));
    lexer_t* lexer   = init_lexer(src, pos);
    parser_t* parser = init_parser(lexer);
    void* popped     = NULL;
    
    while(parser->token->type != TOKEN_EOF)
    {
        parser_consume(parser);
        printf("[Program] TOKEN TYPE IS (%s) and TOKEN VAL IS (%s)\n", token_to_string(parser->token->type), parser->token->tok);
    }
    
    // Pop off of Stack
    do
    {
        popped = parser->stacks->op->items[0];
        list_push(parser->stacks->output, popped);
        list_pop(parser->stacks->op);
    }
    while(popped != NULL);
    
    for(size_t i = 0; i < parser->stacks->output->length - 1; ++i) printf("%s ", (char*) parser->stacks->output->items[i]);
    printf("(TOKEN_EOF)\n");
}

void stakz_compile_file(const char* filename)
{
    char* src = stakz_read_file(filename);
    printf("\033[1;4;35mCompiling %s\n\033[m", filename);
    stakz_compile(src);
    free(src);
}
