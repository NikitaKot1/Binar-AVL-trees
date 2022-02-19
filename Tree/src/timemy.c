#include <inttypes.h>
#include <sys/time.h>
#include "actions.h"
#include "struct.h"
#include "print.h"
#include "hesh_table.h"
#include "input.h"

double time_of_binar(void)
{
    int64_t elapsed_time_k = 0;
    struct timeval tv_start, tv_stop;
    binar_tree *binar = NULL;
    int col;
    FILE *drevo = fopen("drevo.txt", "r");
    read_binar_tree(drevo, &binar);
    fclose(drevo);
    for (int i = 0; i < 1000; i++)
    {
        gettimeofday(&tv_start, NULL);
        find_in_binary(binar, i, &col);
        gettimeofday(&tv_stop, NULL);
        elapsed_time_k += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    return elapsed_time_k / (double)1000;
}

double time_of_avl(void)
{
    int64_t elapsed_time_k = 0;
    struct timeval tv_start, tv_stop;
    binar_tree *binar = NULL;
    int col;
    FILE *drevo = fopen("drevo.txt", "r");
    read_binar_tree(drevo, &binar);
    avl *avl_tree = NULL;
    avl_tree = create_avl_tree(binar, NULL);
    fclose(drevo);
    for (int i = 0; i < 1000; i++)
    {
        gettimeofday(&tv_start, NULL);
        find_in_avl(avl_tree, i, &col);
        gettimeofday(&tv_stop, NULL);
        elapsed_time_k += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    return elapsed_time_k / (double)1000;
}

double time_of_hash(int k)
{
    int64_t elapsed_time_k = 0;
    struct timeval tv_start, tv_stop;
    node_t *hesh_table = NULL;
    int col;
    int n;
    FILE *drevo = fopen("drevo.txt", "r");
    create_hesh_table(&hesh_table, k, &n);
    fclose(drevo);
    for (int i = 0; i < 1000; i++)
    {
        gettimeofday(&tv_start, NULL);
        find_el_in_table(i, &col, hesh_table, k);
        gettimeofday(&tv_stop, NULL);
        elapsed_time_k += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    return elapsed_time_k / (double)1000;
}

double time_of_file(void)
{
    int64_t elapsed_time_k = 0;
    struct timeval tv_start, tv_stop;
    int col = 0, x = 0;
    for (int i = 0; i < 1000; i++)
    {
        FILE *drevo = fopen("drevo.txt", "r");
        gettimeofday(&tv_start, NULL);
        while (fscanf(drevo, "%d", &x) == 1)
        {
            col++;
            if (x == i)
            {
                break;
            }
        }
        gettimeofday(&tv_stop, NULL);
        elapsed_time_k += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        fclose(drevo);
    }
    return elapsed_time_k / (double)1000;
}