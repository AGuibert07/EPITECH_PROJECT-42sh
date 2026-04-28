/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Minishell 2 project
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void nfree(size_t n, ...)
{
    va_list list;
    void *ptr = NULL;

    va_start(list, n);
    for (size_t i = 0; i < n; ++i) {
        ptr = va_arg(list, void *);
        if (ptr != NULL)
            free(ptr);
    }
    va_end(list);
}

void free_array(char **arg)
{
    if (arg == NULL)
        return;
    for (int i = 0; arg[i] != NULL; i++) {
        free(arg[i]);
    }
    free(arg);
}

void nfree_array(size_t n, ...)
{
    va_list list;
    char **ptr = NULL;

    va_start(list, n);
    for (size_t i = 0; i < n; ++i) {
        ptr = va_arg(list, char **);
        if (ptr != NULL)
            free_array(ptr);
    }
    va_end(list);
}
