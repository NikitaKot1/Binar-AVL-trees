#include <stdio.h>

#include "errorss.h"
#include "struct.h"
#include "actions.h"

int read_binar_tree(FILE *f, binar_tree **root)
{
    int x = 0;
    while (fscanf(f, "%d", &x) == 1)
    {
        *root = append(*root, x);
    }
    return OK;
}