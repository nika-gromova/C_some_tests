#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "list_struct.h"

#define EPS 1e-7
#define IS_EQUAL(num1, num2) (fabs((num1) - (num2)) <= EPS)

void free_list(list_node *head)
{
    list_node *tmp = head;
    while (head)
    {
       tmp = head->next;
       free(head);
       head =  tmp;
    }
}

// добавление в начало, возвращает указатель на голову
list_node *push_front(list_node *head, double value)
{
    list_node *in;
    in = malloc(sizeof(list_node));
    if (in)
    {
        in->data = value;
        in->next = head;
        return in;
    }
    return NULL;
}

list_node *find_last(list_node *head)
{
    list_node *tmp = head;
    while (head)
    {
        tmp = head;
        head = head->next;
    }
    return tmp;
}

list_node *push_back(list_node *head, double value)
{
    list_node *last;
    list_node *in = malloc(sizeof(list_node));
    if (in)
    {
        in->data = value;
        in->next = NULL;
        last = find_last(head);
        if (last)
        {
            last->next = in;
            return head;
        }
        return in;
    }
    return NULL;
}


list_node *find_list_element(list_node *head, double value)
{
    while (head)
    {
        if (IS_EQUAL(head->data, value))
            return head;
        head = head->next;
    }
    return NULL;
}

list_node *push_after(list_node *head, list_node *after, double value)
{
    list_node *in = malloc(sizeof(list_node));
    if (in)
    {
        in->data = value;
        if (after)
        {
            in->next = after->next;
            after->next = in;
            return head;
        }
    }
    return NULL;
}

list_node *push_before(list_node *head, double before, double value)
{
    list_node *tmp = head;
    list_node *in = malloc(sizeof(list_node));
    if (in)
    {
        in->data = value;
        if (tmp->data == before || tmp->next == NULL)
        {
            in->next = tmp;
            return in;
        }
        while (tmp)
        {
            if (IS_EQUAL(tmp->next->data, before))
            {
                in->next = tmp->next;
                tmp->next = in;
                return head;
            }
            tmp = tmp->next;
        }
    }
    return NULL;
}

void pop_front(list_node **head, double *pop_value)
{
    list_node *tmp;
    if (*head)
    {
        tmp = (*head)->next;
        *pop_value = (*head)->data;
        free(*head);
        *head = tmp;
    }
}

void pop_back(list_node **head, double *pop_value)
{
    list_node *tmp = *head, *last;
    if (*head)
    {
        last = find_last(*head);
        if (last == *head)
        {
            free(*head);
            *head = NULL;
            return;
        }
        while (tmp)
        {
            if (tmp->next == last)
            {
                *pop_value = last->data;
                tmp->next = NULL;
                free(last);
                return;
            }
            tmp = tmp->next;
        }
    }
}

void pop_by_value(list_node **head, double pop_value)
{
    list_node *tmp = *head, *prev = NULL;
    while (tmp)
    {
        if (IS_EQUAL(tmp->data, pop_value))
        {
            if (prev)
                prev->next = tmp->next;
            else
                *head = tmp->next;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

void print_list(list_node *head)
{
    while (head)
    {
        printf("%2.lf ", head->data);
        head = head->next;
    }
    printf("\n");
}

void sorted_insert(list_node **head, list_node *elem)
{
    list_node *tmp = *head, *prev = NULL;
    while (tmp)
    {
        if (tmp->data > elem->data)
        {
            if (prev)
            {
                prev->next = elem;
                elem->next = tmp;
            }
            else
            {
                *head = elem;
                elem->next = tmp;
            }
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = elem;
}

list_node *my_sort(list_node *head)
{
    list_node *tmp = head, *buf, *prev = head;
    if (tmp == NULL || tmp->next == NULL)
        return head;
    tmp = tmp->next;
    while (tmp)
    {
        buf = tmp->next;
        prev->next = NULL;
        sorted_insert(&head, tmp);
        if (tmp->next == buf)
        {
            prev->next = tmp;
            prev = prev->next;
        }
        else
            prev->next = buf;
        tmp = prev->next;
    }
    return head;
}
