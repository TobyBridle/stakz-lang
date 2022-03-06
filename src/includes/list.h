#ifndef STAKZ_LIST_H
#define STAKZ_LIST_H
#include <stdlib.h>

typedef struct LIST_STRUCT
{
    size_t length;
    void** items;
    size_t item_mem_size;
} list_t;

list_t* init_list(size_t item_mem_size);
void list_push(list_t* list, void* item_pointer);
void list_pop(list_t* list);
#endif