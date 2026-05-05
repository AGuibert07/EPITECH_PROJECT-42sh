/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Header file for editor
*/

#ifndef EDITOR_H_
    #define EDITOR_H_

    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <fcntl.h>
    #include "jobs.h"
    #include <ncurses.h>
    #include "functions.h"
    #include "lang.h"

    #define MAX_BINDINGS 256

typedef struct editor_s editor_t;

typedef void (*key_fn_t)(editor_t *editor, char **env);

typedef struct {
    int key;
    key_fn_t fn;
} binding_t;

typedef struct editor_s {
    char *buffer;
    int len;
    int cap;
    int cursor;
    int prompt_len;
    int prompt_row;
    binding_t bindings[MAX_BINDINGS];
    int b_count;
} editor_t;

// multiline.c
void init_editor(void);
void cleanup_editor(void);
void refresh_display(editor_t *editor, const char *prompt);
char *read_line(const char *prompt, char **env);
// binding.c
void add_bindkey(editor_t *editor, int key, key_fn_t fn);
key_fn_t find_bindkey(editor_t *editor, int key);
void init_bindings(editor_t *editor);
// actions.c
void move_left(editor_t *editor, char **env);
void move_right(editor_t *editor, char **env);
void delete_char(editor_t *editor, char **env);
void insert_char(editor_t *editor, char c);

#endif
