#include "includes/parser.h"
#include "includes/lexer.h"
#include "includes/queue.h"
#include "includes/token.h"
#include "includes/io.h"
#include "includes/asm.h"
#include <ctype.h>
#include <string.h>
#include <math.h>

parser_t* init_parser(lexer_t* lexer)
{
    parser_t* parser       = malloc(sizeof(struct STAKZ_PARSER));
    parser->lexer          = lexer;
    parser->token          = init_token(NULL, 0, 0);
    parser->stacks         = calloc(1, sizeof(struct STAKZ_PARSER_STACKS));
    parser->stacks->op     = init_list(sizeof(parser->token->tok)); // Needs to be read from like a Stack
    parser->stacks->output = NULL;  // Needs to be read from like a Queue
    parser->stacks->vars   = init_list(sizeof(char**));
    parser->set_registers  = STAKZ_REGISTERS;
    
    parser->var_count      = 0;
    parser->file           = stakz_open_file("stakz.s");
    
    return parser;
}

asm_t* parser_parse_keyword(char* token)
{
    if(!strcmp(token, "out"))
        return init_asm("mov    X0, #1\n\t", STDOUT);
    if(!strcmp(token, "+"))
        return init_asm("add    W0, W0, 0x%X\n\t", ADDITION);
    if(!strcmp(token, "-"))
        return init_asm("sub    W0, W0, 0x%X\n\t", SUBTRACTION);
    if(!strcmp(token, "return"))
        return init_asm("mov    X16, #1\n\tsvc    #0x80\n\n\t", RETURN);
    return init_asm(token, -1);
}

void parser_consume(parser_t* parser)
{
    parser->token = lexer_next_token(parser->lexer);
    
    if(parser->token->stack_type == TOKEN_OPERATOR && parser->stacks->op != NULL && parser->token->type != TOKEN_EOF)
    {
            if(parser->stacks->output == NULL)
            {
                printf("\033[1;4;31m[Parser] Trying to use operator `%s` when there are no elements on the stack!\033[m\n", parser->token->tok);
                exit(1);
            }
            list_push(parser->stacks->op, parser->token->tok);

            asm_t* keyword = parser_parse_keyword(parser->token->tok);
            switch(keyword->format)
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
                    ;
                    char* enqueue_value = (char*) calloc(strlen(parser->stacks->output->value) + strlen(parser->stacks->output->next->value) + 1, sizeof(char));

                    char* np;
                    long return_code = strtoll(parser->stacks->output->value, &np, 10);
                    np = NULL;
                    long return_code_next = strtoll(parser->stacks->output->next->value, &np, 10);
                    np = NULL;

                    if(parser->set_registers.W0 == 0) // There is nothing in the register
                    {
                        // Move the first value on the stack to register `W0`
                        fprintf(parser->file, "mov    W0, 0x%X\n\t", return_code);
                    
                        // Pop from the Stack
                        dequeue(&parser->stacks->output);
                        parser->set_registers.W0 = 1; // Declare register as not empty
                    
                        // Add other value
                        fprintf(parser->file, keyword->cmd, return_code_next);
                        np = NULL;
                        dequeue(&parser->stacks->output);
                        
                        sprintf(enqueue_value, "%ld", return_code + return_code_next);
                        enqueue(&parser->stacks->output, enqueue_value);
                                            
                    } else {
                        fprintf(parser->file, keyword->cmd, return_code);
                        fprintf(parser->file, keyword->cmd, return_code_next);
                    
                        char* enqueue_value = (char*) calloc(strlen(parser->stacks->output->value) + strlen(parser->stacks->output->next->value) + 1, sizeof(char));
                    
                        dequeue(&parser->stacks->output);
                        dequeue(&parser->stacks->output);
                    
                        sprintf(enqueue_value, "%ld", return_code + return_code_next);
                        enqueue(&parser->stacks->output, enqueue_value);
                    }
                    parser->set_registers.RETURN = 1;
                    break;
                case SUBTRACTION:
                    ;
                    enqueue_value = (char*) calloc(strlen(parser->stacks->output->value) + strlen(parser->stacks->output->next->value) + 1, sizeof(char));

                    return_code = strtoll(parser->stacks->output->value, &np, 10);
                    np = NULL;
                    return_code_next = strtoll(parser->stacks->output->next->value, &np, 10);
                    np = NULL;

                    if(parser->set_registers.W0 == 0) // There is nothing in the register
                    {
                        // Move the first value on the stack to register `W0`
                        fprintf(parser->file, "mov    W0, 0x%X\n\t", return_code_next);
                    
                        // Pop from the Stack
                        dequeue(&parser->stacks->output);
                        parser->set_registers.W0 = 1; // Declare register as not empty
                    
                        // Subtract other value
                        fprintf(parser->file, keyword->cmd, return_code);
                        np = NULL;
                        dequeue(&parser->stacks->output);
                        
                        sprintf(enqueue_value, "%ld", return_code_next - return_code);
                        enqueue(&parser->stacks->output, enqueue_value);
                                            
                    } else {
                        fprintf(parser->file, keyword->cmd, return_code_next);
                        fprintf(parser->file, keyword->cmd, return_code);
                    
                        char* enqueue_value = (char*) calloc(strlen(parser->stacks->output->value) + strlen(parser->stacks->output->next->value) + 1, sizeof(char));
                    
                        dequeue(&parser->stacks->output);
                        dequeue(&parser->stacks->output);
                    
                        sprintf(enqueue_value, "%ld", return_code_next - return_code );
                        enqueue(&parser->stacks->output, enqueue_value);
                    }
                    parser->set_registers.RETURN = 1;
                    break;
                case RETURN:
                    ;
                    if(parser->set_registers.RETURN == 0) fprintf(parser->file, "mov    X0, 0x%X\n\t", strtol(parser->stacks->output->value, &np, 10));
                    char* ci = (char*) calloc((strlen(keyword->cmd) + strlen(parser->stacks->output->value) + 2), sizeof(char));
                    np = NULL;
                    return_code = strtol(parser->stacks->output->value, &np, 10);

                    sprintf(ci, keyword->cmd, return_code);
                    fprintf(parser->file, "%s", ci);

                    free(ci);
                    break;
                default:
                    printf("\033[1;4;31m[Parser] Symbol `%s` not recognised!\033[m\n", keyword->cmd);
                    exit(1);
            }
            free(keyword);
    }
    if(parser->token->stack_type != TOKEN_OPERATOR) enqueue(&parser->stacks->output, parser->token->tok);
}