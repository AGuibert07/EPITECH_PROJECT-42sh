/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** background
*/

#include "functions.h"
#include "lang.h"

bool check_background_start(const char *command)
{
    char *str = strstr(command, START_BG);

    if (!str)
        return false;
    if (!str[strlen(START_BG)])
        return true;
    return false;
}

void remove_start_bg(char **arg)
{
    int len = my_word_array_len((const char **)(arg));

    if (len > 0 && !strcmp(arg[len - 1], START_BG)) {
        free(arg[len - 1]);
        arg[len - 1] = NULL;
    }
}

void manage_background_jobs(pid_t pid, const char **command, jobs_t **jobs)
{
    jobs_t *tmp = NULL;
    char *tmp_cmd = strdup(*command);
    char *str = NULL;

    if (tmp_cmd)
        str = strstr(tmp_cmd, START_BG);
    if (!tmp_cmd || !str)
        add_elements(jobs, *command, pid, RUNNING);
    else {
        str[0] = '\0';
        add_elements(jobs, tmp_cmd, pid, RUNNING);
    }
    free(tmp_cmd);
    tmp = *jobs;
    printf("[%zu] %d\n", tmp[get_jobs_by_pid(tmp, pid)].pos, pid);
}
