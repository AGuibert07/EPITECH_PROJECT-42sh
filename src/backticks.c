/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Backticks handling
*/

#include "functions.h"

static char *read_output(int fd)
{
    char buffer[1024];
    char *res = "";
    char *tmp = NULL;
    int n;

    while ((n = read(fd, buffer, 1023)) > 0) {
        buffer[n] = '\0';
        tmp = my_str_concat(res, buffer);
        free(res);
        res = tmp;
    }
    for (int i = 0; res[i]; i++)
        if (res[i] == '\n' || res[i] == '\t')
            res[i] = ' ';
    return res;
}

static void exec_child(int *pipe_fds, char *cmd, char **env, int *last_return)
{
    dup2(pipe_fds[1], STDOUT_FILENO);
    close(pipe_fds[0]);
    parse_command(cmd, (char **[]) {env, NULL}, last_return, NULL);
    exit(*last_return);
}

static void exec_cmd(char *line, int start, int end, char **env)
{
}

char *handle_backticks(char *line, int *last_return, jobs_t *jobs,
    char **copy_env)
{
    char *start_ptr = strchr(line, '`');
    char *end_ptr = NULL;    

    if (start_ptr)
        end_ptr = strchr(start_ptr + 1, '`');
    if (!start_ptr || !end_ptr)
        return line;
    line = exec_cmd(line, start_ptr - line, end_ptr - line, copy_env);
    return handle_backticks(line, last_return, jobs, copy_env);    
}
