#include "includes/parser.h"
#include "includes/lexer.h"
#include "includes/token.h"
#include <ctype.h>

parser_t* init_parser(lexer_t* lexer)
{
    parser_t* parser       = malloc(sizeof(struct STAKZ_PARSER));
    parser->lexer          = lexer;
    parser->token          = init_token(NULL, 0, 0);
    parser->stacks         = malloc(sizeof(struct STAKZ_PARSER_STACKS));
    parser->stacks->op     = init_list(sizeof(parser->token->tok)); // Needs to be read from like a Stack
    parser->stacks->output = init_list(sizeof(parser->token->tok)); // Needs to be read from like a Queue
    
    return parser;
}

void parser_consume(parser_t* parser)
{
    parser->token = lexer_next_token(parser->lexer);
    
    // if(parser->token->stack_type == TOKEN_OPERATOR && parser->stacks->op != NULL && parser->token->type != TOKEN_EOF)
    // {
    //         {
    //             list_push(parser->stacks->op, parser->token->tok);
    //             // printf("The current token is (%s) and the current token on the stack is (%s)\n", parser->token->tok, (char*) parser->stacks->op->items[parser->stacks->op->length - 1]);
    //             lexer_parse_operation((char) parser->stacks->op->items[parser->stacks->op->length - 1], parser->lexer->pos);
    //         }
    // }
    if(parser->token->stack_type != TOKEN_OPERATOR) list_push(parser->stacks->output, parser->token->tok);
}