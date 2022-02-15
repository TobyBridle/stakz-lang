#include "includes/lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "includes/macros.h"

lexer_t* init_lexer(char* src)
{
    lexer_t* lexer = malloc(sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;
}

char lexer_peek(lexer_t* lexer, int offset)
{
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

void lexer_advance(lexer_t* lexer)
{
    if(lexer->i < lexer->src_size && lexer->c != '\0')
    {
        lexer->i += 1; 
        lexer->c = lexer->src[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_t* lexer)
{
    while(lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
    {
        lexer_advance(lexer);
    }
}

token_t* lexer_advance_with(lexer_t* lexer, token_t* token)
{
    lexer_advance(lexer);
    return token;
}

token_t* lexer_next_token(lexer_t* lexer) 
{
    while(lexer->c != '\0')
    {
        lexer_skip_whitespace(lexer);
        
        if(lexer->c == '"')
        {
            return lexer_advance_with(lexer, lexer_parse_string(lexer));
        }
        
        if(isalpha(lexer->c))
        {
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        }

        if(isdigit(lexer->c))
        {
            return lexer_advance_with(lexer, lexer_parse_number(lexer));
        }
        
        switch(lexer->c)
        {
            case '\0': break;
            default:
                printf("[Lexer]: Unexpected Character `%c`\n", lexer->c);
                exit(1);
                break;
        }
    }
    return init_token(0, TOKEN_EOF);
}

token_t* lexer_parse_id(lexer_t* lexer)
{
    char* tok = malloc(sizeof(char));

    while(isalpha(lexer->c))
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    
    return init_token(tok, TOKEN_ID);
}

token_t* lexer_parse_string(lexer_t* lexer)
{
    char* tok = malloc(sizeof(char));
    lexer_advance(lexer);

    while(isalpha(lexer->c) || isspace(lexer->c))
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    
    lexer_advance(lexer);
    return init_token(tok, TOKEN_STRING);
}

token_t* lexer_parse_number(lexer_t* lexer)
{
    char* tok = malloc(sizeof(char));

    while(isdigit(lexer->c))
    {
        tok = realloc(tok, (strlen(tok) + 2) * sizeof(char));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    }
    
    return init_token(tok, TOKEN_INT);
}
