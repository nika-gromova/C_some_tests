#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "io.h"
#include "my_struct.h"
#include "list.h"
#include "my_list.h"

#define BUF_SIZE 200

/*char *my_strndup(const char *str, int length)
{
    if (str == NULL)
        return NULL;
    char *new_str = malloc((length + 1) * sizeof (char));
    if (new_str)
    {
        for (int i = 0; i < length; i++)
            new_str[i] = str[i];
        new_str[length] = '\0';
        return new_str;
    }
    else
        return NULL;
}
*/

void delete_spaces(char *str, char *res)
{
    int length = strlen(str);
    while (length > 0 && str[length - 1] == ' ')
        length--;
    while (*str && *str == ' ' && length > 0)
    {
        str++;
        length--;
    }
    for (int i = 0; i < length; i++)
    {
        res[i] = str[i];
    }
    res[length] = '\0';
}

int parse_line(char *line, node_car *cur)
{
    if (!line)
        return READ_FILE_ERROR;
    char *sep = ";";
    char *istr = '\0';
    char *end = NULL;
    double price;
    int year;
    istr = strtok(line, sep);
    if (istr)
    {
        strcpy(cur->model, istr);
        istr = strtok(NULL, sep);
        if (istr)
        {
            strcpy(cur->country, istr);
            istr = strtok(NULL, sep);
            if (istr)
            {
                price = strtod(istr, &end);
                if (*end == '\0')
                {
                    cur->price = price;
                    istr = strtok(NULL, sep);
                    if (istr)
                    {
                        year = atoi(istr);
                        if (year > 0)
                        {
                            cur->year = year;
                            return OK;
                        }
                    }
                }
            }
        }
    }
    return READ_FILE_ERROR;
}

int read_file(char *filename, node_car **head, heads_index_filter *heads_berkeley)
{
    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    char buf[BUF_SIZE];
    node_car *cur = NULL;
    int rc = OK;
    char new_str[BUF_SIZE];
    new_str[BUF_SIZE - 1] = '\0';
    while (rc == OK && fgets(buf, sizeof(buf), f))
    {
        delete_spaces(buf, new_str);
        if (strlen(new_str) > 0)
        {
            cur = malloc(sizeof(node_car));
            if (cur)
            {
                rc = parse_line(buf, cur);
                if (rc == OK)
                {
                    add_lo_list(heads_berkeley, cur, head);
                }
                else
                {
                    free(cur);
                    delete_list(*head);
                }
            }
            else
                rc = MEMORY_ERROR;
        }
        else
            rc = MEMORY_ERROR;
    }
    fclose(f);
    if (rc != OK)
        return rc;
    return OK;
}


int read_line(char *str, int n)
{
    char ch;
    int i = 0;
    int flag_overflow = 0;
    if ((ch = getchar()) != '\n')
    {
        str[i] = ch;
        i++;
    }
    while((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < n - 1)
            str[i++] = ch;
        else
            flag_overflow = 1;
    }
    if (flag_overflow == 0)
        str[i] = '\0';
    else
        i = 0;
    return i;
}

int scan_data(node_car *cur)
{
    char buf[BUF_SIZE];
    int len;
    printf("model and country not more than 20 symbols, price id a real num, period of guarantee is an integer.\n");
    printf("Input format:\nmodel of the car;country;price;period of guarantee\n");
    if ((len = read_line(buf, sizeof(buf))) > 0)
    {
        if (parse_line(buf, cur) == OK)
        {
            printf("here\n");
            return OK;
        }
    }
    printf("Incorrect input :( Try again!\n");
    return INPUT_ERROR;
}

void print_berkeley_sort(struct list_head *head, int index)
{
    printf("\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    node_car *tmp;
    struct list_head *iter;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, sort[index]);
        printf("%2d.%20s%20s%15.2lf%15d\n", tmp->id, tmp->model, tmp->country, tmp->price, tmp->year);
    }
    printf("\n");
}

void print_berkeley_filter(struct list_head *head, int index)
{
    printf("\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    node_car *tmp;
    struct list_head *iter;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, filter[index]);
        printf("%2d.%20s%20s%15.2lf%15d\n", tmp->id, tmp->model, tmp->country, tmp->price, tmp->year);
    }
    printf("\n");
}

void print_data(node_car *head)
{
    printf("\n");
    printf("Current data in database:\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    while (head)
    {
        printf("%2d.%20s%20s%15.2lf%15d\n", head->id, head->model, head->country, head->price, head->year);
        head = head->next;
    }
    printf("\n");
}

int save_data(char *file_name, node_car *head)
{
    int rc = OK;
    FILE *f = fopen(file_name, "w");
    if (f)
    {
        while(head)
        {
            fprintf(f, "%s;%s;%.2lf;%d\n", head->model, head->country, head->price, head->year);
            head = head->next;
        }
        fclose(f);
    }
    else
        rc = OPEN_FILE_ERROR;
    return rc;
}
