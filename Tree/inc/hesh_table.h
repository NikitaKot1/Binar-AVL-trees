#ifndef HESH_TABLE_H
#define HESH_TABLE_H

#include <stdio.h>
#include "struct.h"
node_t *create_cell(int data);
node_t *append_to_table(node_t *root, node_t *node);
int hesh_func(int el, int del);
void create_hesh_table(node_t **table, int k, int *n);
int find_el_in_table(int el, int *col, node_t *table, int k);

#endif