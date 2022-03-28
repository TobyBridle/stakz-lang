#include "includes/parser.h"
#include "includes/lexer.h"
#include "includes/queue.h"
#include "includes/stack.h"
#include "includes/token.h"
#include "includes/io.h"
#include "includes/asm.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

parser_t* init_parser(lexer_t* lexer)
{
    parser_t* parser       = malloc(sizeof(struct STAKZ_PARSER));
    parser->lexer          = lexer;
    parser->token          = init_token(NULL, 0, 0);
    parser->stacks         = calloc(1, sizeof(struct STAKZ_PARSER_STACKS));
    parser->stacks->op     = init_stack(sizeof(parser->token->tok)); // Needs to be read from like a Stack

    parser->stacks->output = NULL;  // Needs to be read from like a Queue
    parser->stacks->output_token_type = NULL;  // Needs to be read from like a Queue

    parser->stacks->vars   = init_list(sizeof(char**));

    parser->var_count      = 0;
    parser->file           = stakz_open_file("stakz.s");
    
    parser->has_return     = 0;
    
    return parser;
}

/* asm_t* parser_parse_keyword(char* token)
{
    if(!strcmp(token, "out"))
        return init_asm("mov    X0, #1\n\t", STDOUT);
    if(!strcmp(token, "+"))
        return init_asm("additino", ADDITION);
    if(!strcmp(token, "return"))
        return init_asm("mov    X0, #%d\n\tmov    X16, #1\n\tsvc    #0x80\n\n\t", RETURN);
    return init_asm(token, -1);
} */

int parser_parse_keyword(char* token)
{
    if(!strcmp(token, "return")) return RETURN;
    if(!strcmp(token, "+")) return ADDITION;

    fprintf(stderr, "\033[31m[Parser]: Could not find symbol '%s'\033[0m\n", token);
    exit(1);
}

void parser_consume(parser_t* parser)
{
    parser->token = lexer_next_token(parser->lexer);

    if(parser->token->stack_type == TOKEN_OPERATOR && parser->stacks->op != NULL && parser->token->type != TOKEN_EOF)
    {
            if(parser->stacks->output == NULL && parser->has_return == 0)
            {
                fprintf(stderr, "\033[1;4;31m[Parser] Trying to use operator `%s` when there are no elements on the stack!\033[m\n", parser->token->tok);
                exit(1);
            }
            stack_push(parser->stacks->op, parser->token->tok);

            int keyword = parser_parse_keyword(parser->token->tok);
            stack_pop(parser->stacks->op);

            switch(keyword)
            {
                case RETURN:
                    ;
                
                    if(parser->stacks->output == NULL && parser->has_return == 0)
                    {
                        fprintf(stderr, "\033[31m[Parser] No stack element to return!\033[0m\n");
                        exit(1);
                    }
                
                    /*
                    1. Pop return code from Stack
                    2. Check return code is valid
                    3. Place return code into statement
                    */
                
                    // 1. Pop return code from Stack
                    void* return_code = parser->has_return == 0 ? parser->stacks->output->value : NULL;
                
                    // 2. Check return code is Valid
                    if(parser->has_return == 0 && parser->stacks->output_token_type->value == TOKEN_STRING )
                    {
                        fprintf(stderr, "\033[31m[Parser]: Could not return string value \"%s\"!\n\033[0m", return_code);
                        exit(1);
                    }

                    // 3. Place return code into statement
                    if(return_code != NULL) fprintf(parser->file, "mov X0,    #%s\n\t", return_code);
                    fprintf(parser->file, "mov X16,    #1\n\t");
                    fprintf(parser->file, "svc 0x80\n\t");

                    if(return_code != NULL) dequeue(&parser->stacks->output);
                    if(return_code != NULL) dequeue(&parser->stacks->output_token_type);
                    break;
            
                case ADDITION:
                    ;

                    if(parser->stacks->output->next == NULL && parser->has_return == 0)
                    {
                        fprintf(stderr, "\033[31m[Parser] Not enough elements to perform the operation on!\033[0m\n");
                        exit(1);
                    }
                    
                    /*
                    1. Pop values from Stack
                    2. Check type of addition that must occur (e.g string / numeric)
                    3. Perform addition in assembly (TODO: CALCULATE STATIC ADDITIONS IN COMPILATION STAGE)
                    */
                
                    void* number_one = parser->stacks->output->value;
                    void* number_two = parser->has_return == 0 ? parser->stacks->output->next->value : NULL;
                    
                    if(parser->has_return == 0) for(int i = 0; i < 2; ++i)
                    {
                        dequeue(&parser->stacks->output);
                        dequeue(&parser->stacks->output_token_type);
                    }

                    // Perform String Addition
                    // if(parser->stacks->output_token_type->value == TOKEN_STRING || parser->stacks->output_token_type->next->value == TOKEN_STRING)
                    // {
                    //     // TODO: String Addition
                    //     fprintf(stderr, "\033[31m[Parser]: String Addition is not yet supported!\033[0m");
                    //     exit(1);
                    // } else {
                        if(parser->has_return == 0) fprintf(parser->file, "mov X0,    #%s\n\t", number_one);
                        fprintf(parser->file, "add X0, X0,    #%s\n\t", parser->has_return == 0 ? number_two : number_one);
                        parser->has_return = 1;
                    // }
                    
                    break;
            }
            /* switch(keyword->format)
            {
                case STDOUT:
                    fprintf(parser->file, "%s", keyword->cmd);
                    fprintf(parser->file, "adr    X1, var_%lu\n\t", parser->var_count + 1);

                    fprintf(parser->file, "mov    X2, #");
                    fprintf(parser->file, "%lu\n\tmov    X16, #4\n\tsvc    #0x80\n\n\t", strlen(parser->stacks->output->value));

                    ssize_t length = snprintf(NULL, 0, "var_%lu:    .ascii \"%s\"", parser->var_count++, (char*) parser->stacks->output->value);
                    char* var_name = calloc(length + 1, sizeof(char));
                    snprintf(var_name, length + 1, "var_%lu:    .ascii \"%s\"", parser->var_count, (char*) parser->stacks->output->value);

                    list_push(parser->stacks->vars, var_name);
                    break;
                case ADDITION:
                    break;
                case RETURN:
                    ;
                    char* ci = (char*) calloc((strlen(keyword->cmd) + strlen(parser->stacks->output->value) + 2), sizeof(char));
                    char* np;
                    long return_code = strtol(parser->stacks->output->value, &np, 10);

                    sprintf(ci, keyword->cmd, return_code);
                    fprintf(parser->file, "%s", ci);
                    free(ci);
                    break;
                default:
                    printf("\033[1;4;31m[Parser] Symbol `%s` not recognised!\033[m\n", keyword->cmd);
                    exit(1);
            } */
            // free(keyword);
    }
    if(parser->token->stack_type != TOKEN_OPERATOR)
    {
        enqueue(&parser->stacks->output, parser->token->tok);
        enqueue(&parser->stacks->output_token_type, parser->token->type);
    }
}
