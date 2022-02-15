#include "includes/stax.h" 
#include "includes/lexer.h"
#include "includes/token.h"
#include "includes/io.h"
#include <stdlib.h>

void stax_compile(char* src)
{
    lexer_t* lexer = init_lexer(src);
    token_t* tok = 0;
    
    while(((tok = lexer_next_token(lexer))->type != TOKEN_EOF))
    {
        printf("TOKEN (%s) (%s)\n", tok->tok, token_to_string(tok->type));
    }
}

void stax_compile_file(const char* filename)
{
    char* src = stax_read_file(filename);
    stax_compile(src);
    free(src);   
}
