#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errorss.h"
#include "input.h"
#include "actions.h"
#include "struct.h"
#include "print.h"
#include "hesh_table.h"
#include "timemy.h"

#define PRINT 1
#define FIND 2
#define TIME 3
#define END 0


int main(void)
{
    setbuf(stdout, NULL);
    char l[1024];
    int rc = OK, find_rc = FINDED, k = 3, col = 0, rest = 0, x = 0, n = 0;
    double tm = 0;
    binar_tree *binar = NULL;
    avl *avl_tree = NULL;
    FILE *drevo = fopen("drevo.txt", "r");
    node_t *hesh_table = NULL;
    if (drevo)
    {
        if (!rc)
        {
            int tag = -1, new_el = 0;
            while (tag)
            {
                printf("Вывести ДДП, АВЛ и хеш-таблицу               - %d\n", PRINT);
                printf("Найти значение                               - %d\n", FIND);
                printf("Сравнить время поиска в различных структурах - %d\n", TIME);
                printf("Выйти                                        - %d\n", END);
                read_binar_tree(drevo, &binar);
                avl_tree = create_avl_tree(binar, NULL);
                fclose(drevo);
                create_hesh_table(&hesh_table, k, &n);
                scanf("%d", &tag);
                switch (tag)
                {
                case PRINT:
                    print_binar_tree(binar);
                    print_avl_tree(avl_tree);
                    print_hash_table(hesh_table, n);
                    system("dot -Tpng graphs/binary.gv -ographs/binary.png");
                    system("dot -Tpng graphs/avl.gv -ographs/avl.png");
                    system("dot -Tpng graphs/hash_table.gv -ographs/hash_table.png");
                    break;
                
                case FIND:
                    col = 0;
                    printf("Введите нужный элемент: ");
                    while(scanf("%d", &new_el) != 1)
                    {
                        printf("Введите целое число!\n");
                        fgets(l, sizeof(l), stdin);
                    }
                    find_rc = find_in_binary(binar, new_el, &col);
                    if (find_rc == FINDED)
                    {
                        printf("ДДП: найдено\n");
                        printf("Количество стравнений: %d\n", col);
                    }
                    else
                        printf("ДДП: не найдено\n");
                    col = 0;
                    find_rc = find_in_avl(avl_tree, new_el, &col);
                    if (find_rc == FINDED)
                    {
                        printf("АВЛ: найдено\n");
                        printf("Количество стравнений: %d\n", col);
                    }
                    else
                        printf("АВЛ: не найдено\n");
                    
                    col = 0;
                    find_rc = find_el_in_table(new_el, &col, hesh_table, n);
                    if (find_rc == FINDED)
                    {
                        printf("Таблица: найдено\n");
                        printf("Количество стравнений: %d\n", col);
                        printf("Максимальное кол-во сравнений в таблице: %d\n\n",k);
                        printf("Реструкторизировать таблицу? Да - 0; Нет - 1\n");
                        scanf("%d", &rest);
                        if (!rest)
                        {
                            printf("Введите максимальное количество сравнений новой таблице: ");
                            while(scanf("%d", &k) != 1 || k <= 0)
                            {
                                printf("Введите натуральное число!\n");
                                fgets(l, sizeof(l), stdin);
                            }
                            create_hesh_table(&hesh_table, k, &n);
                        }
                    }
                    else
                        printf("Таблица: не найдено\n\n");
                    break;

                    drevo = fopen("drevo.txt", "r");
                    col = 0;
                    while (fscanf(drevo, "%d", &x) == 1)
                    {
                        col++;
                        if (x == new_el)
                        {
                            printf("Файл: найдено\n");
                            printf("Количество стравнений: %d\n", col);
                            break;
                        }
                    }
                    if (x != col)
                        printf("Файл: не найденo\n");

                
                case TIME:
                    tm = time_of_binar();
                    printf("Время поиска в ДДП: %.3lf\n", tm);
                    tm = time_of_avl();
                    printf("Время поиска в АВЛ: %.3lf\n", tm);
                    tm = time_of_hash(k);
                    printf("Время поиска в ХЭШ: %.3lf\n", tm);
                    tm = time_of_file();
                    printf("Время поиска в файле: %.3lf\n\n", tm);
                    break;

                default:
                    fgets(l, sizeof(l), stdin);
                    break;
                }
            }

        }
        else
        {
            printf("Ошибка выделения памяти!\n");
        }
    }
    else
    {
        printf("Файл не существует!\n");
        rc = INVALID_FILE;
    }
    return rc;
}