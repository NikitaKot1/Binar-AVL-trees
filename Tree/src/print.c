#include <stdio.h>

#include "struct.h"
#include "errorss.h"

void print_dipend(FILE *f, int x, int y)
{
    fprintf(f, "   %d -> %d\n", x, y);
}

int check_dipend(FILE *f, binar_tree *parent)
{
    if (parent->left)
        print_dipend(f, parent->el, check_dipend(f, parent->left));
    if (parent->right)
        print_dipend(f, parent->el, check_dipend(f, parent->right));
    return parent->el;
}

void print_binar_tree(binar_tree *root)
{
    FILE *f = fopen("graphs/binary.gv", "w");
    fprintf(f, "digraph BinaryTree {\n");
    check_dipend(f, root);
    fprintf(f, "}");
    fclose(f);
}

int check_dipend_avl(FILE *f, avl *parent)
{
    if (parent->left)
        print_dipend(f, parent->el, check_dipend_avl(f, parent->left));
    if (parent->right)
        print_dipend(f, parent->el, check_dipend_avl(f, parent->right));
    return parent->el;
}

void print_avl_tree(avl *root)
{
    FILE *f = fopen("graphs/avl.gv", "w");
    fprintf(f, "digraph AVLTree {\n");
    check_dipend_avl(f, root);
    fprintf(f, "}");
    fclose(f);
}

void print_hash_table(node_t *table, int k)
{
    FILE *f = fopen("graphs/hash_table.gv", "w");
    fprintf(f, "digraph HashTable {\n");
    fprintf(f, " rankdir = LR;\n");
    fprintf(f, " node [shape = record,width = .1,height = .1];\n");
    for (int i = k - 1; i >= 0; i--)
    {
        fprintf(f, "m%d [label = \"<m%d> %d\",height = 1.0];\n", i, i, i);
    }
    for (int i = 0; i < k; i++)
    {
        node_t *cur = table[i].next;
        if (cur)
        {
            int j = 0;
            while (cur)
            {
                fprintf(f, " v%d_%d [label = \"{ %d }\"];\n", i, j, cur->el);
                if (cur->next)
                {
                    fprintf(f, " v%d_%d:e -> v%d_%d:w;\n", i, j, i, j + 1);
                }
                cur = cur->next;
                ++j;
            }
            fprintf(f, " m%d:m%d -> v%d_0;\n", i, i, i);
        }
    }
    fprintf(f, "}\n");
    fclose(f);
}