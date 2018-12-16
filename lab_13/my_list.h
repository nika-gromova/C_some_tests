#ifndef MY_LIST_H
#define MY_LIST_H

#include "my_struct.h"
node_car *push_back(node_car *head, node_car *elem);
void add_element_to_berkeley(heads_index_filter *heads, node_car *elemnt);
void add_lo_list(heads_index_filter *heads_berkeley, node_car *cur, node_car **head);
void delete_list(node_car *head);
node_car *delete_element(node_car *head, int index);
node_car *find_element(node_car *head, int index);
void delete_berkeley(node_car *cur);
#endif // MY_LIST_H
