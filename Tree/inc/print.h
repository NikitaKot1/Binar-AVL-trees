#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "struct.h"
void print_binar_tree(binar_tree *root);
void print_avl_tree(avl *root);
void print_hash_table(node_t *table, int k);

#endif