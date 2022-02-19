#include <stdlib.h>
#include <stdio.h>
#include "errorss.h"
#include "struct.h"

binar_tree *create_node(int data)
{
    binar_tree *node = malloc(sizeof(binar_tree));
    if (node)
    {
        node->el = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

binar_tree *append(binar_tree *root, int el)
{
    if (root)
    {
        if (root->el > el)
            root->left = append(root->left, el);
        if (root->el < el)
            root->right = append(root->right,  el);
        return root;
    }
    return create_node(el);
}

avl *create_avl(int data)
{
    avl *node = malloc(sizeof(avl));
    if (node)
    {
        node->el = data;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }
    return node;
}

void find_height(avl* p)
{
    if (p)
    {
        if (p->left) find_height(p->left);
        if (p->right) find_height(p->right);
        int hl = p->left ? p->left->height : 0;
        int hr = p->right ? p->right->height : 0;
        p->height = (hl > hr ? hl : hr) + 1;
    }
}

avl* rotate_right(avl* node)
{
	avl* new_node = node->left;
    if (new_node)
    {
        node->left = new_node->right;
        new_node->right = node;
        find_height(node);
        find_height(new_node);
        return new_node;
    }
    return node;
}

avl* rotate_left(avl* node)
{
	avl* new_node = node->right;
    if (new_node)
    {
        node->right = new_node->left;
        new_node->left = node;
        find_height(node);
        find_height(new_node);
        return new_node;
    }
	return node;
}

int height(avl *node)
{
    return node ? node->height : 0;
}

int find_balance(avl *root)
{
    return root ? height(root->left) - height(root->right) : 0;
}

avl *append_avl(avl *root, int el)
{
    if (root)
    {
        if (root->el > el)
            root->left = append_avl(root->left, el);
        if (root->el < el)
            root->right = append_avl(root->right,  el);

        
        find_height(root);

        if (find_balance(root) > 1)
        {
            if (find_balance(root->left) < 0)
                root->left = rotate_left(root->left);
            return rotate_right(root);
        }

        if (find_balance(root) < -1)
        {
            if (find_balance(root->right) > 0)
                root->right = rotate_right(root->right);
            return rotate_left(root);
        }

        return root;
    }
    return create_avl(el);
}

avl *create_avl_tree(binar_tree *root, avl *parent)
{
    if (!root)
        return OK;
    parent = append_avl(parent, root->el);
    if (root->left)
        parent = create_avl_tree(root->left, parent);
    if (root->right)
        parent = create_avl_tree(root->right, parent);
    find_height(parent);
    return parent;
}

int find_in_binary(binar_tree *root, int el, int *col)
{
    (*col)++;
    if (root->el == el)
        return FINDED;
    if (root->el > el)
    {
        if (root->left)
            return find_in_binary(root->left, el, col);
        return NOT_FINDED;
    }
    if (root->el < el)
    {
        if (root->right)
            return find_in_binary(root->right, el, col);
        return NOT_FINDED;
    }
    return FINDED;
}

int find_in_avl(avl *root, int el, int *col)
{
    (*col)++;
    if (root->el == el)
        return FINDED;
    if (root->el > el)
    {
        if (root->left)
            return find_in_avl(root->left, el, col);
        return NOT_FINDED;
    }
    if (root->el < el)
    {
        if (root->right)
            return find_in_avl(root->right, el, col);
        return NOT_FINDED;
    }
    return FINDED;
}