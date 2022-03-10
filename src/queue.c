#include "includes/queue.h"
#include <stdlib.h>
#include <stdio.h>

void enqueue(node_t** head, void* value)
{
    node_t* node = malloc(sizeof(node_t));
    node->value = value;
    node->next = *head;
    
    *head = node;
}

int dequeue(node_t** head) {
    node_t *current, *prev = NULL;
    if(head == NULL) return -1;
    current = *head;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    free(current);
    
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;

    return 0;
}