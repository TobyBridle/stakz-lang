#include "includes/lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "includes/macros.h"
#include "includes/io.h"

lexer_t* init_lexer(char* src, pos_t* pos)
{
    lexer_t* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;                   // The Bytes of the Source File
    lexer->src_size = strlen(src);      // The size of the Source File (used for boundary checking)
    lexer->i = 0;                       // The index of the Source File that the Lexer is on
    lexer->c = src[lexer->i];           // The current character of the index
    
    lexer->pos = pos;

    return lexer;
}

/**
 * Returns the character a certain offset from the current location `lexer->i`
 * @param lexer_t* lexer
 * @param int offset
 * @return char
 */
char lexer_peek(lexer_t* lexer, int offset)
{
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}

/**
 * moves one position from the current location `lexer->i`
 * @param lexer_t* lexer
 */
void lexer_advance(lexer_t* lexer)
{
    if(lexer->i < lexer->src_size && lexer->c != '\0')
    {
        lexer->i += 1; 
        lexer->c = lexer->src[lexer->i];
        lexer->pos->charNumber += 1;
    }
}

/**
 * detects if the character is whitespace and if so advances
 * @param lexer_t* lexer
 */
void lexer_skip_whitespace(lexer_t* lexer)
{
    while(isblank(lexer->c) != 0)
    {
        lexer_advance(lexer);
    }
}

/**
 * Returns the token and advances from the current location `lexer->i`
 * @param lexer_t* lexer
 * @param token_t* token
 * @return token_t*
 */
token_t* lexer_advance_with(lexer_t* lexer, token_t* token)
{
    lexer_advance(lexer);
    return token;
}

/**
* Returns a token based on the current position of the lexer
* @param lexer_t* lexer
* @returns token_t* token
*/
token_t* lexer_next_token(lexer_t* lexer) 
{
    while(lexer->c != '\0')
    {
        lexer_skip_whitespace(lexer);
        
        if(lexer->c == '\n')
        {
            lexer->pos->lineNumber += 1;
            lexer->pos->charNumber = 0;
            lexer_advance(lexer);
        }
        
        // Add Lexer for Comments
        // if(lexer->c == '#')
        // {
            // return lexer_advance_with(lexer, lexer_parse_comment(lexer));
        // }
        
        if(lexer->c == '"')
        {
            return lexer_advance_with(lexer, lexer_parse_string(lexer));
        }
        
        if(isalpha(lexer->c) != 0)
        {
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        }

        if(isdigit(lexer->c) != 0)
        {
            return lexer_advance_with(lexer, lexer_parse_number(lexer));
        }
        return lexer_advance_with(lexer, lexer_parse_operation(lexer->c, lexer->pos));
    }
    return init_token("-1", TOKEN_EOF, TOKEN_OPERATOR);
}

/**
* Parses an ID by moving continuously until whitespace is met
* @param lexer_t* lexer
* @return token_t* token
*/
token_t* lexer_parse_id(lexer_t* lexer)
{
    char* tok = calloc(1, sizeof(char));
    while(isalpha(lexer->c))
    {
        tok = realloc(tok, sizeof(char) * (strlen(tok) + 2));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer); 
    }
    
    // Check for Keywords (e.g IF)
    return init_token(tok, TOKEN_ID, TOKEN_OPERATOR);
}

// TODO:
// An endless loop is entered if there is no closing quotation.
// Potentially use regex or detect if there is no match by end of line to break this loop and
// raise an error

/**
* Parses a string by moving until the next quotation mark is found
* @param lexer_t* lexer
* @return token_t* token
*/
token_t* lexer_parse_string(lexer_t* lexer)
{
    char* tok = calloc(1, sizeof(char));
    lexer_advance(lexer);

    do {
        tok = realloc(tok, sizeof(char) * (strlen(tok) + 2));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer);
    } while(lexer->c != '"' || (lexer->c == '"' && lexer_peek(lexer, -1) == '\\'));

    return init_token(tok, TOKEN_STRING, TOKEN_OUTPUT);
}

/**
* Parses a number by advancing continuously until the next non-digit
* @param lexer_t* lexer
* @return token_t* token
*/
token_t* lexer_parse_number(lexer_t* lexer)
{
    char* tok = calloc(1, sizeof(char));
    while(isdigit(lexer->c))
    {
        tok = realloc(tok, sizeof(char) * (strlen(tok) + 2));
        strcat(tok, (char[]){lexer->c, 0});
        lexer_advance(lexer); 
    }
    
    return init_token(tok, TOKEN_INT, TOKEN_OUTPUT);
}

/**
* Parses an operation by matching against a case
* @param char tok
* @return token_t* token
*/
token_t* lexer_parse_operation(char tok, pos_t* pos)
{
    switch(tok)
    {
        case '\0': break;
        case '+': return init_token("+", TOKEN_PLUS, TOKEN_OPERATOR);
        case '-': return init_token("-", TOKEN_MINUS, TOKEN_OPERATOR);
        case '*': return init_token("*", TOKEN_MULT, TOKEN_OPERATOR);
        case '/': return init_token("/", TOKEN_DIV, TOKEN_OPERATOR);
        case '=': return init_token("=", TOKEN_EQUAL, TOKEN_OPERATOR);
        default:
            fprintf(stderr, "\033[1;31m[Lexer] %s:%ld:%ld: Unexpected Character `%c` (ASCII: %d)\n\033[m", pos->filename, pos->lineNumber, pos->charNumber, tok, tok);
            exit(1);
    }
    fprintf(stderr, "\033[1;31m[Lexer] Something went wrong when parsing the operation `%d`\n", tok);
    exit(1);
}
