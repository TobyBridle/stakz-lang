#ifndef STAKZ_QUEUE_H
#define STAKZ_QUEUE_H

typedef struct STAKZ_QUEUE_NODE
{
    void* value;
    struct STAKZ_QUEUE_NODE* next;
} node_t;

int dequeue(node_t** head);
void enqueue(node_t** head, void* value);

#endif
