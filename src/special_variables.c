/*
** EPITECH PROJECT, 2026
** inhibitors.c
** File description:
** this file contains all functions to handle special variables
*/

#include "functions.h"
#include "alias.h"

char **run_precmd(void *array[], int *last_return, alias_t **list)
{
    char *alias = get_alias(*list, "precmd");
    char **env_new = NULL;
    char *tmp = NULL;

    if (!alias)
        return (char **)(array[0]);
    tmp = strdup(alias);
    if (!tmp)
        return (char **)(array[0]);
    return process_line((void *[]){tmp, list, array[3]}, array[0],
        array[1], array[2]);
}

char **run_preexec(void *array[], int *last_return, jobs_t **jobs,
    alias_t **list)
{
    char *alias = get_alias(*list, "preexec");
    char **env_new = NULL;
    char *tmp = NULL;

    if (!alias)
        return (char **)(array[0]);
    tmp = strdup(alias);
    if (!tmp)
        return (char **)(array[0]);
    return process_line((void *[]){tmp, list, array[3]}, array[0],
        array[1], array[2]);
}
