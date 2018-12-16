#ifndef IO_H
#define IO_H

#include "my_struct.h"

void delete_spaces(char *str, char *res);
int parse_line(char *line, node_car *cur);
int read_file(char *filename, node_car **head, heads_index_filter *heads_berkeley);
void print_berkeley_sort(struct list_head *head, int index);
void print_data(node_car *head);
void print_berkeley_filter(struct list_head *head, int index);
int scan_data(node_car *cur);
int save_data(char *file_name, node_car *head);

#endif // IO_H
