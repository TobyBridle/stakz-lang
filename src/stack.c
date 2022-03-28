#include "includes/stack.h"

stck_t* init_stack(ssize_t element_size)
{
    stck_t* stack = (stck_t*) calloc(1, sizeof(struct STAKZ_STACK));
    stack->element_size = element_size;
    stack->top = NULL;

    return stack;
}

void stack_push(stck_t* stack, void* element)
{
    slice_t* slice = (slice_t*) calloc(1, sizeof(struct STAKZ_SLICE));
    slice = stack->top;

    if(stack->top == NULL)
        stack->top = (slice_t*) calloc(1, sizeof(struct STAKZ_SLICE));
    stack->top->value = element;
    stack->top->tail = slice;
} 

void stack_pop(stck_t* stack)
{
    slice_t* new_top = stack->top->tail;
    free(stack->top);
    
    stack->top = new_top;
}