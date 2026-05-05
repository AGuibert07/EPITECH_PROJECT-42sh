/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Handle line reading and completion
*/

#include "editor.h"

static editor_t *init_ed_struct(const char *prompt)
{
    editor_t *editor = malloc(sizeof(editor_t));

    if (!editor)
        return NULL;
    editor->buffer = calloc(256, 1);
    editor->len = 0;
    editor->cap = 256,
    editor->cursor = 0;
    editor->prompt_len = strlen(prompt);
    editor->b_count = 0;
    if (!editor->buffer)
        return NULL;
    return editor;
}

void init_editor(void)
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
}

void cleanup_editor(void)
{
    endwin();
}

void refresh_display(editor_t *editor, const char *prompt)
{
    int term_rows;
    int term_cols;
    int abs_cursor_pos;
    int cursor_row;
    int cursor_col;

    getmaxyx(stdscr, term_rows, term_cols);
    (void)term_rows;
    move(editor->prompt_row, 0);
    clrtobot();
    printw("%s%s", prompt, editor->buffer);
    abs_cursor_pos = editor->prompt_len + editor->cursor;
    cursor_row = editor->prompt_row + (abs_cursor_pos / term_cols);
    cursor_col = abs_cursor_pos % term_cols;
    move(cursor_row, cursor_col);
    refresh();
}

char *read_line(const char *prompt, char **env)
{
    int ch;
    key_fn_t action;
    editor_t *editor = init_ed_struct(prompt);

    init_editor();
    init_bindings(editor);
    getyx(stdscr, editor->prompt_row, ch);
    refresh_display(editor, prompt);
    ch = getch();
    while (ch != '\n' && ch != 4) {
        action = find_bindkey(editor, ch);
        if (action)
            action(editor, env);
        if (ch >= 32 && ch <= 126)
            insert_char(editor, ch);
        refresh_display(editor, prompt);
        ch = getch();
    }
    cleanup_editor();
    return editor->buffer;
}
