#ifndef STAX_TOKEN_H
#define STAX_TOKEN_H
#include <stdlib.h>
#include <stdio.h>

typedef struct TOKEN_STRUCT
{
    char* tok;
    enum
    {
	TOKEN_ID,     	  // 0
	TOKEN_COLON,  	  // :
	TOKEN_COMMA,   	  // ,

	TOKEN_STRING, 	  // "3"
	TOKEN_INT,    	  // 3
	TOKEN_FLOAT,  	  // 3.1

	TOKEN_LPAREN, 	  // (
	TOKEN_RPAREN, 	  // )
	TOKEN_LBRACE, 	  // {
	TOKEN_RBRACE, 	  // }
	TOKEN_LCOMP,  	  // <
	TOKEN_RCOMP,  	  // >

	TOKEN_EQUAL,  	  // = 
	TOKEN_PLUS,   	  // +
	TOKEN_MINUS,  	  // -
	TOKEN_MULT,   	  // *
	TOKEN_DIV,     	  // / 
	
	TOKEN_FUNC,       // func
	TOKEN_IF,         // if
	TOKEN_END,        // end
    TOKEN_EOF         // EOF  
    } type;
} token_t;

token_t* init_token(char* tok, int type);
char* token_to_string(int type);
#endif
