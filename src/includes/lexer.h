#ifndef STAX_LEXER_H
#define STAX_LEXER_H
#include "token.h"
typedef struct LEXER_STRUCT
{
    char* src;
    size_t src_size;
    char c;
    unsigned int i;
} lexer_t;

lexer_t* init_lexer(char* src);

void lexer_advance(lexer_t* lexer);
void lexer_skip_whitespace(lexer_t* lexer);
void lexer_skip_with(lexer_t* lexer);
char lexer_peek(lexer_t* lexer, int offset);

token_t* lexer_advance_with(lexer_t* lexer, token_t* token);
token_t* lexer_advance_current(lexer_t* lexer, token_t* token);

token_t* lexer_parse_id(lexer_t* lexer);
token_t* lexer_parse_string(lexer_t* lexer);
token_t* lexer_parse_number(lexer_t* lexer);

token_t* lexer_next_token(lexer_t* lexer);
#endif
