#ifndef STRUCT_H
#define STRUCT_H

typedef struct node_binar binar_tree;

struct node_binar
{
    int el;
    binar_tree *left;
    binar_tree *right;
};



typedef struct node_avl avl;

struct node_avl
{
    int el;
    avl *left;
    avl *right;
    int height;
};



typedef struct node node_t;

struct node
{
    int el;
    node_t *next;
};

#endif