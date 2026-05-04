/*
** EPITECH PROJECT, 2026
** inhibitors.c
** File description:
** manage all the inhibitors of 42sh
*/

#include "functions.h"
#include "lang.h"

static char **assemble_quote(const char **new_arg, const char *sep, char quote)
{
    char **tmp = malloc(sizeof(char *) * 1);
    size_t current = 0;
    bool containing_quote = false;

    for (size_t y = 0; new_arg[y] != NULL; y++) {
        for (size_t x = 0; new_arg[y][x] != '\0'; x++)
            containing_quote = char_cmp_quote(containing_quote, new_arg[y][x],
                quote);
        if (containing_quote == false) {
            tmp[current] = strdup(new_arg[y]);
            current++;
            tmp = realloc(tmp, sizeof(char *) * (current + 1));
            tmp[current] = NULL;
        } else
            tmp = create_part(tmp, new_arg, (size_t *[]){&current, &y},
                (const char *[]){sep, &quote});
        containing_quote = false;
    }
    remove_backslash(new_arg, tmp, quote);
    return tmp;
}

static void find_nb_quote(const char **new_arg, size_t y, size_t *nb_quote,
    char quote)
{
    for (size_t x = 0; new_arg[y][x] != '\0'; x++)
        if (new_arg[y][x] == quote &&
            (x == 0 || (x != 0 && new_arg[y][x - 1] != BACKSLASH)))
            *nb_quote += 1;
}

static char **check_quotes(char **new_arg, const char *separator, char quote)
{
    size_t nb_quote = 0;

    if (strcmp(separator, SEMICOLON) != 0)
        return new_arg;
    for (size_t y = 0; new_arg[y] != NULL; y++)
        find_nb_quote((const char **)new_arg, y, &nb_quote, quote);
    if (nb_quote % 2 != 0) {
        fprintf(stderr, "Unmatched '''.\n");
        for (size_t x = 0; new_arg[x] != NULL; x++)
            free(new_arg[x]);
        free(new_arg);
        return NULL;
    } else if (nb_quote != 0)
        new_arg = assemble_quote((const char **)new_arg, separator, quote);
    return new_arg;
}

char **manage_quotes(char **new_arg, const char *separator)
{
    new_arg = check_quotes(new_arg, separator, SIMPLE_QUOTE);
    new_arg = check_quotes(new_arg, separator, DOUBLE_QUOTE);
    return new_arg;
}
