/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** jobs.h
*/

#ifndef JOBS_H_
    #define JOBS_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <sys/types.h>
    #define START_BG "&"
    #define JOBS_CMD "jobs"
    #define JOBS_BG_CMD "bg"
    #define JOBS_FG_CMD "fg"

typedef enum jobs_state {
    STOPPED,
    BG_STOP_OUT,
    BG_STOP_IN,
    FOREGROUND,
    DONE,
    RUNNING,
    NULL_STATE,
    EXITED
} states_t;

typedef struct jobs_control {
    size_t pos;
    pid_t pid;
    states_t state;
    char *name;
} jobs_t;

typedef struct jobs_builtins_s {
    char *name;
    void (*ptr)(char **, jobs_t **, int *, void *[]);
} jobs_builtins_t;

jobs_t *init_jobs_struct(void);
void free_jobs_struct(jobs_t *jobs);
size_t jobs_struct_len(jobs_t *jobs);
void add_elements(jobs_t **jobs, const char *name, pid_t pid, states_t state);
void remove_element(jobs_t **jobs, size_t pos);
void jobs_command(char **args, jobs_t **jobs_ptr, int *last_return,
    void *array[]);
void fg_command(char **args, jobs_t **jobs, int *last_return, void *array[]);
void bg_command(char **args, jobs_t **jobs, int *last_return, void *array[]);
void job_control_synonym(char **args, jobs_t **jobs, int *last_return,
    void *array[]);
jobs_t *get_jobs(const char *arg, jobs_t *jobs, char **args, size_t *pos);
size_t get_jobs_by_pid(jobs_t *jobs, pid_t pid);
void check_background_jobs(jobs_t **jobs);
bool check_background_start(const char *command);
void manage_background_jobs(pid_t pid, const char **command, jobs_t **jobs);
void remove_start_bg(char **arg);

static const jobs_builtins_t jobs_builtins[] = {
    {JOBS_FG_CMD, fg_command},
    {JOBS_BG_CMD, bg_command},
    {JOBS_CMD, jobs_command},
    {NULL, NULL}
};

#endif /* JOBS_H_ */
