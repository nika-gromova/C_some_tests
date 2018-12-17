#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "io.h"
#include "defines.h"
#include "my_list.h"
#include "my_struct.h"
void info(void)
{
    printf("Hello! This is a program for simple data base for cars.\n");
    printf("Information fields: model, country of manufacture, price, period of guarantee (in years).\n");
    printf("You can add a new elemnt, delete an element, change information about the element and save information to the .txt file.\n");
    printf("More to this you can sort information by price, model or period of guarantee.\n");
    printf("You can filter information: get all cars made in Germany or all cars with period of guarantee >= 4 years.\n");
}

void usage(void)
{
    printf("app.exe in.txt\nin.txt - file, where the initial information is located.\n");
}

void menu(void)
{
    printf("\n1 - load data from file;\n");
    printf("2 - add an element;\n");
    printf("3 - delete an element (by id);\n");
    printf("4 - change an element (by id);\n");
    printf("5 - show sorted elemnts;\n");
    printf("6 - show filtered elements;\n");
    printf("7 - save information to the file;\n");
    printf("8 - print current information in database;\n");
    printf("9 - exit;\n");
}

int main(int argc, char *argv[])
{
    int rc = OK;
    char buf[20];
    int choice = 0;
    char *end = NULL;
    char file_out[20];
    int id = 0;
    if (argc != 2)
    {
        usage();
        return USAGE_ERROR;
    }
    info();

    heads_index_filter heads_berkeley;
    INIT_LIST_HEAD(&(heads_berkeley.sort_model));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
    INIT_LIST_HEAD(&(heads_berkeley.filter_country));
    INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
    node_car *head = NULL;
    node_car *in = NULL;

    while (choice == 0)
    {
        menu();
        if (scanf("%s", buf) == 1)
        {
            choice = strtol(buf, &end, 10);
            if (*end == '\0' && choice > 0 && choice < 10)
            {
                if (choice == 1)
                {
                    rc = read_file(argv[1], &head, &heads_berkeley);
                    if (rc == OK)
                    {
                        printf("Loaded!\n");
                    }
                    else
                    {
                        printf("Error in loading data\n");
                    }
                    choice = 0;
                }
                if (choice == 2)
                {
                    in = malloc(sizeof(node_car));
                    if (in)
                    {
                        printf("Input information:\n");
                        rc = scan_data(in);
                        if (rc == OK)
                        {
                            add_lo_list(&heads_berkeley, in, &head);
                            printf("Added!\n");
                        }
                        else
                        {
                            free(in);
                        }
                    }
                    else
                        printf("Memory error.\n");
                    choice = 0;
                }
                if (choice == 3)
                {
                    printf("Input id of element that you want to delete:\n");
                    if (scanf("%s", buf) == 1)
                    {
                        id = strtol(buf, &end, 10);
                        if (*end == '\0' && id > 0)
                        {
                            head = delete_element(head, id);
                            if (head == NULL)
                                printf("List is empty\n");
                            else
                                printf("Deleted!\n");
                        }
                        else
                            printf("Incorrect id.\n");
                    }
                    else
                        rc = INPUT_ERROR;
                    choice = 0;
                }
                if (choice == 4)
                {
                    printf("Input id of element that you want to change:\n");
                    if (scanf("%s", buf) == 1)
                    {
                        id = strtol(buf, &end, 10);
                        if (*end == '\0' && id > 0)
                        {
                            in = find_element(head, id);
                            if (in == NULL)
                                printf("Not found.\n");
                            else
                            {
                                delete_berkeley(in);
                                printf("Input new information:\n");
                                rc = scan_data(in);
                                if (rc == OK)
                                {
                                    add_element_to_berkeley(&heads_berkeley, in);
                                    printf("Changed!\n");
                                }
                            }
                        }
                        else
                            printf("Incorrect id.\n");
                    }
                    choice = 0;
                }
                if (choice == 5)
                {
                    printf("1 - sort by model;\n2 - sort by price;\n3 - sort by price and guarantee:\n");
                    if (scanf("%s", buf) == 1)
                    {
                        choice = strtol(buf, &end, 10);
                        if (*end == '\0' && choice > 0 && choice < 4)
                        {
                            if (choice == 1)
                                print_berkeley_sort(&(heads_berkeley.sort_model), 0);
                            if (choice == 2)
                                print_berkeley_sort(&(heads_berkeley.sort_price), 1);
                            if (choice == 3)
                                print_berkeley_sort(&(heads_berkeley.sort_price_and_guarantee), 2);
                        }
                        else
                            printf("Wrong sort choice.\n");
                    }
                    choice = 0;
                }
                if (choice == 6)
                {
                    printf("1 - cars from Germany;\n2 - period of guarantee >= 4:\n");
                    if (scanf("%s", buf) == 1)
                    {
                        choice = strtol(buf, &end, 10);
                        if (*end == '\0' && choice > 0 && choice < 3)
                        {
                            if (choice == 1)
                                print_berkeley_filter(&(heads_berkeley.filter_country), 0);
                            if (choice == 2)
                                print_berkeley_filter(&(heads_berkeley.filter_guarantee), 1);
                        }
                        else
                            printf("Wrong filter choice.\n");
                    }
                    choice = 0;
                }
                if (choice == 7)
                {
                    printf("Input file name to save:\n");
                    if (scanf("%s", file_out) == 1)
                    {
                        rc = save_data(file_out, head);
                        if (rc != OK)
                            printf("Error in saving data\n");
                        else
                            printf("Saved!\n");
                    }
                    choice = 0;
                }
                if (choice == 8)
                {
                    print_data(head);
                    choice = 0;
                }
                if (choice == 9)
                {
                    printf("Exit.\n");
                }
            }
            else
            {
                printf("Wrong menu choice.\n");
                choice = 0;
            }
        }
    }
    delete_list(head);
    printf("rc = %d\n", rc);
    return rc;
}
