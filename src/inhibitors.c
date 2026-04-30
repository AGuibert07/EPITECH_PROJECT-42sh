/*
** EPITECH PROJECT, 2026
** inhibitors.c
** File description:
** manage all the inhibitors of 42sh
*/

#include <stdbool.h>
#include "functions.h"
#include "lang.h"

static void replace_backslash_with_separator(char **arg, size_t *x,
    char *separator)
{
    char *tmp = NULL;

    arg[*x] = realloc(arg[*x], sizeof(char *) * (strlen(arg[*x]) +
            strlen(separator)));
    if (!arg[*x])
        exit(84);
    tmp = my_str_concat(arg[*x], separator);
    free(arg[*x]);
    arg[*x] = strdup(tmp);
    if (!arg[*x])
        exit(84);
    free(tmp);
}

static char *check_backslash(char **arg, size_t *x, char *separator)
{
    char *tmp = NULL;
    size_t nb_loop = 0;

    while (arg[*x][strlen(arg[*x]) - 1] == '\\') {
        if (strlen(separator) > 1)
            replace_backslash_with_separator(arg, x, separator);
        else
            arg[*x - nb_loop][strlen(arg[*x - nb_loop]) - 1] = separator[0];
        if (!arg[*x + 1])
            break;
        else {
            tmp = my_str_concat(arg[*x - nb_loop], arg[*x + 1]);
            free(arg[*x - nb_loop]);
            arg[*x - nb_loop] = strdup(tmp);
            free(tmp);
        }
        *x += 1;
        nb_loop++;
    }
    return arg[*x - nb_loop];
}

static size_t count_without_backslash(char **arg, size_t count_nb)
{
    for (size_t x = 0; arg[x] != NULL; x++)
        if (arg[x][strlen(arg[x]) - 1] == '\\' && arg[x + 1] != NULL)
            count_nb--;
    return count_nb;
}

static void find_nb_quote(char **new_arg, size_t y, size_t *nb_quote)
{
    for (size_t x = 0; new_arg[y][x] != '\0'; x++)
        if (new_arg[y][x] == '\'' &&
            (x == 0 || (x != 0 && new_arg[y][x - 1] != '\\')))
            *nb_quote += 1;
}

char **check_quotes(char **new_arg, const char *separator)
{
    size_t nb_quote = 0;

    if (strcmp(separator, ";") != 0)
        return new_arg;
    for (size_t y = 0; new_arg[y] != NULL; y++)
        find_nb_quote(new_arg, y, &nb_quote);
    if (nb_quote % 2 != 0) {
        fprintf(stderr, "Unmatched '''.\n");
        for (size_t x = 0; new_arg[x] != NULL; x++)
            free(new_arg[x]);
        free(new_arg);
        return NULL;
    } else if (nb_quote != 0)
        new_arg = assemble_quote(new_arg, separator);
    return new_arg;
}

char **check_inhibitors(char **arg, char *separator, size_t count_nb)
{
    char **new_arg = NULL;
    size_t current = 0;

    count_nb = count_without_backslash(arg, count_nb);
    new_arg = malloc(sizeof(char *) * (count_nb + 1));
    if (!new_arg)
        exit(84);
    for (size_t x = 0; arg[x] != NULL; x++) {
        if (arg[x][strlen(arg[x]) - 1] == '\\')
            new_arg[current] = strdup(check_backslash(arg, &x, separator));
        else
            new_arg[current] = strdup(arg[x]);
        if (!new_arg[current])
            exit(84);
        current++;
    }
    new_arg[current] = NULL;
    free_array(arg);
    new_arg = check_quotes(new_arg, separator);
    return new_arg;
}
