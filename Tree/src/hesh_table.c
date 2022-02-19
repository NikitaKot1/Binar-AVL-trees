#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.h"
#include "actions.h"
#include "errorss.h"

void free_table(node_t **table, int n)
{
    for (int i = 0; i < n; i++)
    {
        node_t *cur = (*table)[i].next;
        while (cur)
        {
            node_t *new = cur->next;
            free(cur);
            cur = new;
        }
    }
    free(*table);
}

node_t *create_cell(int data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->el = data;
        node->next = NULL;
    }
    return node;
}

node_t *append_to_table(node_t *root, node_t *node)
{
    node_t *cur = root;
    if (!root)
        return node;
    for (; cur->next; cur = cur->next);
    cur->next = node;
    return root;
}

int hesh_func(int el, int del)
{
    return abs(el % del);
}

bool prof(node_t *table, int k, int n)
{
    for (int i = 0; i < n; i++)
    {
        int col = 0;
        node_t *cur = table[i].next;
        for (; cur; cur = cur->next)
            col++;
        if (col > k)
            return false;
    }
    return true;
}

void create_new_table(FILE *f, node_t **table, int k)
{
    *table = malloc(k * sizeof(node_t));
    for (int i = 0; i < k; i++)
        (*table)[i].next = NULL;
    int x = 0;
    while (fscanf(f, "%d", &x) == 1)
        append_to_table(&(*table)[hesh_func(x, k)], create_cell(x));
}

void create_hesh_table(node_t **table, int k, int *new_n)
{
    int n = 5, x, col = 0;
    FILE *f = fopen("drevo.txt", "r");
    while (fscanf(f, "%d", &x) == 1)
        col++;
    fclose(f);
    f = fopen("drevo.txt", "r");
    n = col / 4;
    create_new_table(f, table, n);
    fclose(f);
    while (!prof(*table, k, n))
    {
        free_table(table, n);
        n++;
        f = fopen("drevo.txt", "r");
        create_new_table(f, table, n);
        fclose(f);
    }
    *new_n = n;
}

int find_el_in_table(int el, int *col, node_t *table, int k)
{
    node_t *er = table[hesh_func(el, k)].next;
    (*col) = 1;
    while (er)
    {
        if (er->el == el)
            return FINDED;
        (*col)++;
        er = er->next;
    }
    return NOT_FINDED;
}
