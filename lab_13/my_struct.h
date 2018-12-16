#ifndef MY_STRUCT_H
#define MY_STRUCT_H

#include "list.h"

#define MAX_LENGTH 20
#define MAX_SORT_INDX 3
#define MAX_FILTER_INDX 2

typedef struct car
{
    char model[MAX_LENGTH + 1];
    char country[MAX_LENGTH + 1];
    double price;
    int year;
    int id;
    struct list_head sort[MAX_SORT_INDX];
    struct list_head filter[MAX_FILTER_INDX];
    struct car *next;
} node_car;

typedef struct head_l
{
    struct list_head sort_model;
    struct list_head sort_price;
    struct list_head sort_price_and_guarantee;
    struct list_head filter_country;
    struct list_head filter_guarantee;
} heads_index_filter;

#endif // MY_STRUCT_H
