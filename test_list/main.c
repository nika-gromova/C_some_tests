#include <stdio.h>
#include <stdlib.h>
#include "list_struct.h"
#include "my_list.h"

int main(void)
{
    list_node *head = NULL;
    list_node *add = malloc(sizeof(list_node));
    if (add)
    {
        add->data = 12;
        add->next = NULL;
    }
    else
        return -1;

    for (int i = 0; i < 10; i++)
        head = push_front(head, i);
    print_list(head);
    head = my_sort(head);
    print_list(head);
    free_list(head);
    free(add);
    return 0;
}
