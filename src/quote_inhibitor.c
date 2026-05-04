/*
** EPITECH PROJECT, 2026
** quote_inhibitor.c
** File description:
** manage the quote of 42sh
*/

#include <stdbool.h>
#include "functions.h"
#include "lang.h"

static char **create_part_tmp_without_separator(char **tmp, size_t **indexes,
    const char **new_arg, char quote)
{
    size_t *current = indexes[0];
    size_t *y = indexes[1];
    char *part_tmp = malloc(sizeof(char) * (strlen(new_arg[*y]) - 1));
    size_t pos = 0;

    for (size_t x = 0; new_arg[*y][x] != '\0'; x++)
        if (new_arg[*y][x] != quote) {
            part_tmp[pos] = new_arg[*y][x];
            pos++;
        }
    part_tmp[pos] = '\0';
    tmp[*current] = strdup(part_tmp);
    free(part_tmp);
    *current += 1;
    tmp = realloc(tmp, sizeof(char *) * (*current + 1));
    tmp[*current] = NULL;
    return tmp;
}

static char *create_part_before_quote(const char **new_arg, size_t **indexes,
    char quote)
{
    size_t *y = indexes[0];
    size_t *nb_char_part_tmp = indexes[1];
    size_t *y_copy = indexes[2];
    size_t *tmp_x = indexes[3];
    char *part_tmp = NULL;

    if (new_arg[*y][0] != quote) {
        for (size_t x = 0; new_arg[*y][x] != quote; x++)
            *nb_char_part_tmp += 1;
        part_tmp = malloc(sizeof(char) * (*nb_char_part_tmp + 1));
        for (size_t x = 0; x != *nb_char_part_tmp; x++)
            part_tmp[x] = new_arg[*y][x];
    }
    if (new_arg[*y_copy][*nb_char_part_tmp + 1] == '\0') {
        *y_copy += 1;
        *tmp_x = 0;
    } else
        *tmp_x = *nb_char_part_tmp + 1;
    return part_tmp;
}

static char **quote_containing_only_separator(size_t **indexes, char *part_tmp,
    const char *separator, char **tmp)
{
    size_t *current = indexes[0];
    size_t *y = indexes[1];
    size_t *nb_char_part_tmp = indexes[2];

    *y += 1;
    part_tmp = realloc(part_tmp, sizeof(char) * (*nb_char_part_tmp + 2));
    part_tmp[*nb_char_part_tmp] = separator[0];
    part_tmp[*nb_char_part_tmp + 1] = '\0';
    tmp[*current] = strdup(part_tmp);
    free(part_tmp);
    *current += 1;
    tmp = realloc(tmp, sizeof(char *) * (*current + 1));
    tmp[*current] = NULL;
    return tmp;
}

static char *realloc_part_tmp(size_t **indexes, const char **new_arg,
    char *part_tmp, char quote)
{
    size_t tmp_x = indexes[0][0];
    size_t y_copy = indexes[0][1];
    size_t nb_char_part_tmp = indexes[0][2];
    size_t *y = indexes[1];
    size_t nb_char_quote_part = 0;

    for (size_t x = tmp_x; new_arg[y_copy][x] != quote; x++) {
        if (new_arg[y_copy][x] == '\0') {
            y_copy += 1;
            x = 0;
        }
        nb_char_quote_part++;
    }
    nb_char_quote_part += y_copy - *y;
    part_tmp = realloc(part_tmp, sizeof(char) * (nb_char_part_tmp +
            nb_char_quote_part + 1));
    return part_tmp;
}

static char *create_part_inside_quote(size_t **indexes, const char **new_arg,
    char *part_tmp, const char **utils)
{
    size_t nb_char_part_tmp = indexes[0][2];
    size_t *y = indexes[1];
    const char *separator = utils[0];
    char quote = *utils[1];
    int pos = nb_char_part_tmp;

    part_tmp = realloc_part_tmp(indexes, new_arg, part_tmp, quote);
    if (new_arg[*y][nb_char_part_tmp + 1] == '\0')
        part_tmp[nb_char_part_tmp] = separator[0];
    for (int x = nb_char_part_tmp + 1; new_arg[*y][x] != quote; x++) {
        if (new_arg[*y][x] == '\0') {
            part_tmp[pos] = separator[0];
            *y += 1;
            x = -1;
        } else
            part_tmp[pos] = new_arg[*y][x];
        pos++;
    }
    part_tmp[pos] = '\0';
    return part_tmp;
}

static char **add_part_to_tmp(char **tmp, size_t *current, char *part_tmp)
{
    tmp[*current] = strdup(part_tmp);
    free(part_tmp);
    *current += 1;
    tmp = realloc(tmp, sizeof(char *) * (*current + 1));
    tmp[*current] = NULL;
    return tmp;
}

char **create_part(char **tmp, const char **new_arg, size_t **indexes,
    const char **utils)
{
    size_t *current = indexes[0];
    size_t *y = indexes[1];
    const char *separator = utils[0];
    char quote = *utils[1];
    char *part_tmp = NULL;
    size_t nb_char_part_tmp = 0;
    size_t y_copy = *y;
    size_t tmp_x = 0;

    if (my_word_array_len((const char **)new_arg) == 1)
        return create_part_tmp_without_separator(tmp, indexes, new_arg, quote);
    part_tmp = create_part_before_quote(new_arg,
        (size_t *[]){y, &nb_char_part_tmp, &y_copy, &tmp_x}, quote);
    if (new_arg[y_copy][tmp_x] == quote)
        return quote_containing_only_separator((size_t *[]){y, current,
                &nb_char_part_tmp}, part_tmp, separator, tmp);
    part_tmp = create_part_inside_quote((size_t *[]){(size_t []){tmp_x,
                y_copy, nb_char_part_tmp}, y}, new_arg, part_tmp, utils);
    tmp = add_part_to_tmp(tmp, current, part_tmp);
    return tmp;
}

static void replace_backslash_by_quote(char **tmp, size_t y, char quote)
{
    for (size_t x = 0; tmp[y][x] != '\0'; x++)
        if (tmp[y][x] == BACKSLASH)
            tmp[y][x] = quote;
}

bool char_cmp_quote(bool containing_quote, char character, char quote)
{
    if (character == quote)
        return true;
    return containing_quote;
}

void remove_backslash(const char **new_arg, char **tmp, char quote)
{
    free_array((char **)new_arg);
    for (size_t y = 0; tmp[y] != NULL; y++)
        replace_backslash_by_quote(tmp, y, quote);
}
