/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Functions for && and || operators
*/

#include <string.h>
#include "functions.h"
#include "lang.h"
#include "alias.h"
#include "history.h"

static op_type_t get_op(char *str, int i)
{
    if (str[i] == '&' && str[i + 1] == '&')
        return AND;
    if (str[i] == '|' && str[i + 1] == '|')
        return OR;
    return NONE;
}

static op_type_t check_op(char *line, int i, int depth)
{
    if (depth == 0)
        return get_op(line, i);
    return NONE;
}

static flow_t *create_node(char *line, int start, int end, op_type_t op)
{
    flow_t *node = malloc(sizeof(flow_t));

    if (!node)
        return NULL;
    node->command = my_substring(line, start, end - start);
    node->next_op = op;
    return node;
}

static void found_op(flow_t ***list, char *line, int *indexes[3],
    op_type_t op)
{
    (*list)[*indexes[0]] = create_node(line, *indexes[2], *indexes[1], op);
    (*indexes[0])++;
    (*indexes[1])++;
    *indexes[2] = *indexes[1] + 1;
}

static flow_t **split_logic(char *line)
{
    flow_t **list = calloc(strlen(line) + 1, sizeof(flow_t *));
    int count = 0;
    int start = 0;
    int depth = 0;
    int single_quote = 0;
    int double_quote = 0;
    op_type_t op;

    for (int i = 0; line[i] != '\0'; i++) {
        measure_depth(line[i], &depth, &single_quote, &double_quote);
        op = check_op(line, i, depth + single_quote + double_quote);
        if (op != NONE)
            found_op(&list, line, (int *[]){&count, &i, &start}, op);
    }
    list[count] = create_node(line, start, strlen(line), NONE);
    count++;
    list[count] = NULL;
    return list;
}

static void free_nodes(flow_t **nodes)
{
    if (nodes == NULL)
        return;
    for (int i = 0; nodes[i]; i++) {
        if (nodes[i]->command)
            free(nodes[i]->command);
        free(nodes[i]);
    }
    free(nodes);
}

static void increment(flow_t **nodes, int *i, int *last_return)
{
    if (nodes[*i]->next_op == AND && *last_return != 0)
        (*i)++;
    else if (nodes[*i]->next_op == OR && *last_return == 0)
        (*i)++;
}

static int empty_command(char *cmd, int *last_return)
{
    if (!cmd || cmd[0] == '\0') {
        *last_return = 1;
        return 1;
    }
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t')
            return 0;
    *last_return = 1;
    return 1;
}

static int check_syntax(flow_t **nodes, int *last_return)
{
    for (int i = 0; nodes[i]; i++) {
        if (empty_command(nodes[i]->command, last_return)) {
            fprintf(stderr, "Invalid null command.\n");
            return 1;
        }
    }
    return 0;
}

char **handle_ops(char *command, void *array[],
    int *last_return, jobs_t **jobs)
{
    flow_t **nodes = split_logic(command);
    char **env = (char **)array[0];

    if (check_syntax(nodes, last_return)) {
        free_nodes(nodes);
        return env;
    }
    for (int i = 0; nodes[i]; i++) {
        env = parse_command(nodes[i]->command, array, last_return, jobs);
        array[0] = env;
        increment(nodes, &i, last_return);
        if (nodes[i] == NULL)
            break;
    }
    free_nodes(nodes);
    return env;
}
