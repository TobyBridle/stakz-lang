#include "includes/stakz.h" 
#include "includes/lexer.h"
#include "includes/parser.h"
#include "includes/token.h"
#include "includes/io.h"
#include <stdlib.h>

void stakz_compile(char* src)
{
    lexer_t* lexer = init_lexer(src);
    /*parser_t* parser = init_parser(lexer);*/
    /*AST_t* root = parser_parse(parser);*/
    token_t* tok = 0;
    
    while(((tok = lexer_next_token(lexer))->type != TOKEN_EOF))
    {
        printf("TOKEN (%s) (%s)\n", tok->tok, token_to_string(tok->type));
    }
}

void stakz_compile_file(const char* filename)
{
    char* src = stakz_read_file(filename);
    stakz_compile(src);
    free(src);   
}
