#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "io.h"
#include "my_struct.h"
#include "my_list.h"



void test_delete_spaces(void)
{
    printf("Tests for deleting space in the beggining and at the end of the string:\n");
    {
        char *in = "a";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with 'a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = " a";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with ' a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = " a ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with ' a ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "  a ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with '  a ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "a  ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("%s\n", out);
        printf("Correct work with 'a  ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "a  a";
        char out[20];
        char *check = "a  a";
        delete_spaces(in, out);
        printf("Correct work with 'a  a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "    a  a  ";
        char out[20];
        char *check = "a  a";
        delete_spaces(in, out);
        printf("Correct work with '    a  a  ': %s\n\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "       ";
        char out[20];
        char *check = "";
        delete_spaces(in, out);
        printf("Correct work with '       ': %s\n\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
}

void test_parse_line(void)
{
    printf("Tests for parsing line and putting data to information fields:\n");
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;b;0.5;1";
            char *check_1 = "a";
            char *check_2 = "b";
            double check_3 = 0.5;
            int check_4 = 1;
            int rc = parse_line(str, cur);
            printf("Correct work with parsing correct line: %s\n", (rc == OK && (strcmp(cur->model, check_1) == 0) && \
                                                                    (strcmp(cur->country, check_2) == 0) &&\
                                                                    (IS_EQUAL(cur->price, check_3)) && (cur->year == check_4)) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char *str = NULL;
            int rc = parse_line(str, cur);
            printf("Correct work with parsing empty line: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = " ";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line without ';': %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 1 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;a";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12a;1";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 3 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;g";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;-5";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }

    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;0";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
}

void test_read_file(void)
{
    printf("Tests for reading data from file:\n");
    heads_index_filter heads_berkeley;
    INIT_LIST_HEAD(&(heads_berkeley.sort_model));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
    INIT_LIST_HEAD(&(heads_berkeley.filter_country));
    INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
    {
        char *file = "in.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with null file: %s\n", (rc == OPEN_FILE_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_1.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with null file: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_2.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with null file: %s\n", (rc == OK) ? "YES" : "NO");
        print_data(head);
        print_berkeley_filter(&(heads_berkeley.filter_country), 0);
        print_berkeley_filter(&(heads_berkeley.filter_guarantee), 1);
        print_berkeley_sort(&(heads_berkeley.sort_price_and_guarantee), 2);
        delete_list(head);
    }
}

int main(void)
{
    test_delete_spaces();
    test_parse_line();
    test_read_file();
    return 0;
}
