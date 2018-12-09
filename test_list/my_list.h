#ifndef MY_LIST_H
#define MY_LIST_H

#include "list_struct.h"
void free_list(list_node *head);
list_node *push_front(list_node *head, double value);
list_node *push_back(list_node *head, double value);
list_node *find_list_element(list_node *head, double value);
list_node *push_after(list_node *head, list_node *after, double value);
list_node *push_before(list_node *head, double before, double value);
void pop_front(list_node **head, double *pop_value);
void pop_back(list_node **head, double *pop_value);
void pop_by_value(list_node **head, double pop_value);
void print_list(list_node *head);
void sorted_insert(list_node **head, list_node *elem);
list_node *my_sort(list_node *head);
#endif // MY_LIST_H
