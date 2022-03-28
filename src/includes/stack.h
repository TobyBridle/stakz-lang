#ifndef STAKZ_STACK_H
#define STAKZ_STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct STAKZ_SLICE
{
    void* value;
    struct STAKZ_SLICE* tail;
} slice_t;

typedef struct STAKZ_STACK
{
    slice_t* top;
    ssize_t element_size;
} stck_t;

stck_t* init_stack(ssize_t element_size);
void stack_push(stck_t* stack, void* element);
void stack_pop(stck_t* stack);

#endif 