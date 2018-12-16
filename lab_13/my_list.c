#include <string.h>
#include <stdlib.h>
#include "my_struct.h"
#include "my_list.h"
#include "defines.h"
#include "list.h"

void delete_list(node_car *head)
{
    node_car *tmp;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

node_car *push_back(node_car *head, node_car *elem)
{
    node_car *cur = head;
    if (!head)
    {
        elem->id = 1;
        return elem;
    }
    for (; cur->next; cur = cur->next)
        ;
    elem->id = cur->id + 1;
    cur->next = elem;
    return head;
}

int cmp_model(node_car *elem1, node_car *elem2)
{
    return strcmp(elem1->model, elem2->model);
}

int cmp_country(node_car *elem1, node_car *elem2)
{
    return strcmp(elem1->country, elem2->country);
}

int cmp_price(node_car *elem1, node_car *elem2)
{
    if (IS_EQUAL(elem1->price, elem2->price))
        return 0;
    if (elem1->price > elem2->price)
        return 1;
    return -1;
}

int cmp_price_and_guarantee(node_car *elem1, node_car *elem2)
{
    if (IS_EQUAL(elem1->price, elem2->price))
    {
        if (elem1->year == elem2->year)
            return 0;
        if (elem1->year > elem2->year)
            return 1;
        return -1;
    }
    if (elem1->price > elem2->price)
        return 1;
    return -1;
}

void insert_sorted(struct list_head *head, node_car *elem, int(*cmp)(node_car*, node_car*), int index)
{
    struct list_head *inserting = &(elem->sort[index]);
    struct list_head *tmp;
    node_car *data;
    list_for_each(tmp, head)
    {
        data = list_entry(tmp, node_car, sort[index]);
        if (cmp(data, elem) == 1)
        {
            list_add_tail(inserting, tmp);
            return;
        }
    }
    list_add_tail(inserting, head);
}

void add_element_to_berkeley(heads_index_filter *heads, node_car *elemnt)
{
    if (strcmp(elemnt->country, "Germany") == 0)
    {
        list_add_tail(&(elemnt->filter[0]), &(heads->filter_country));
    }
    if (elemnt->year >= 4)
    {
        list_add_tail(&(elemnt->filter[1]), &(heads->filter_guarantee));
    }
    insert_sorted(&(heads->sort_model), elemnt, cmp_model, 0);
    insert_sorted(&(heads->sort_price), elemnt, cmp_price, 1);
    insert_sorted(&(heads->sort_price_and_guarantee), elemnt, cmp_price_and_guarantee, 2);
}

void add_lo_list(heads_index_filter *heads_berkeley, node_car *cur, node_car **head)
{
    INIT_LIST_HEAD(&(cur->filter[0]));
    INIT_LIST_HEAD(&(cur->filter[1]));
    cur->next = NULL;
    *head = push_back(*head, cur);
    add_element_to_berkeley(heads_berkeley, cur);
}

void delete_berkeley(node_car *cur)
{
    list_del(&(cur->filter[0]));
    list_del(&(cur->filter[1]));
    list_del(&(cur->sort[0]));
    list_del(&(cur->sort[1]));
    list_del(&(cur->sort[2]));
}

node_car *delete_element(node_car *head, int index)
{
    node_car *prev = NULL, *cur = head;
    while (cur)
    {
        if (cur->id == index)
        {
            if (prev)
            {
                prev->next = cur->next;
            }
            else
            {
                head = cur->next;
            }
            delete_berkeley(cur);
            free(cur);
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    return NULL;
}


node_car *find_element(node_car *head, int index)
{
    while (head)
    {
        if (head->id == index)
            return head;
        head = head->next;
    }
    return NULL;
}
