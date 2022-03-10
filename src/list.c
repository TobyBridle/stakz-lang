#include "includes/list.h"
#include <stdio.h>
#include <string.h>

list_t* init_list(size_t item_mem_size)
{
	list_t* list = calloc(1, sizeof(struct LIST_STRUCT));
	list->item_mem_size = item_mem_size;
	list->items = NULL;
	list->length = 0;
	
	return list;
}

void list_push(list_t* list, void* item_pointer)
{
	list->length += 1;
	if(list->items == NULL)
	{
		list->items = calloc(1, sizeof(list->item_mem_size));
		list->items[0] = item_pointer;
	} else {
		list->items = realloc(list->items, list->length * sizeof(list->item_mem_size));
		list->items[list->length - 1] = item_pointer;
	}
}

void list_pop(list_t* list)
{
	// list->items is of type void**
	if(list->length != 0)
	{
		list->items+=1;
		list->length -= 1;
	}
}