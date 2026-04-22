/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** This file countaines tools functions
*/

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *cut_ending_char(char *buffer, char c)
{
    int l = 0;

    if (!buffer)
        return buffer;
    l = strlen((const char *)(buffer));
    if (buffer[l - 1] == c)
        buffer[l - 1] = '\0';
    return buffer;
}

bool str_isnum(const char *str, int *val)
{
    char *tmp = NULL;
    int nbr = strtol(str, &tmp, 10);

    if (val)
        *val = nbr;
    if (!tmp || tmp[0])
        return false;
    return true;
}
