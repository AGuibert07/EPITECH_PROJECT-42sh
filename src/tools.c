/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** This file countaines tools functions
*/

#include <string.h>

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
