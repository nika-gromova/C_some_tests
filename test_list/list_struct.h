#ifndef LIST_STRUCT_H
#define LIST_STRUCT_H

typedef struct list_elem
{
    double data;
    struct list_elem *next;
} list_node;

#endif // LIST_STRUCT_H
