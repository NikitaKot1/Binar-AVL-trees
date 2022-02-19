#ifndef ACTIONS_H
#define ACTIONS_H

#include "struct.h"

binar_tree *create_node(int data);
binar_tree *append(binar_tree *root, int el);
avl *create_avl_tree(binar_tree *root, avl *parent);
avl *append_avl(avl *root, int el);
int find_in_binary(binar_tree *root, int el, int *col);
int find_in_avl(avl *root, int el, int *col);

#endif