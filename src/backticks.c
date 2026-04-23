/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Backticks handling
*/

#include "functions.h"

char *handle_backticks(char *line, int *last_return, jobs_t *jobs,
    char **copy_env)
{
    char *start_ptr = strchr(line, '`');
    char *end_ptr = NULL;
    int start_pos = 0;
    int end_pos = 0;
    char *cmd_to_exec;
    int pipe_fds[2];

    if (start_ptr)
        end_ptr = strchr(start_ptr + 1, '`');
    if (!start_ptr || !end_ptr)
        return line;
    start_pos = start_ptr - line;
    end_pos = end_ptr - line;
    cmd_to_exec = my_substring(line, start_pos + 1, end_pos - start_pos - 1);
    if (pipe(pipe_fds) == -1)
        return line;
}
