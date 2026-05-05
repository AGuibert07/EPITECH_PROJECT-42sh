/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Dynamic rebinding functions
*/

#include "editor.h"

void add_bindkey(editor_t *editor, int key, key_fn_t fn)
{
    for (int i = 0; i < editor->b_count; i++)
        if (editor->bindings[i].key == key) {
            editor->bindings[i].fn = fn;
            return;
        }
    if (editor->b_count < MAX_BINDINGS) {
        editor->bindings[editor->b_count] = (binding_t){key, fn};
        editor->b_count++;
    }
}

key_fn_t find_bindkey(editor_t *editor, int key)
{
    for (int i = 0; i < editor->b_count; i++)
        if (editor->bindings[i].key == key)
            return editor->bindings[i].fn;
    return NULL;
}

void init_bindings(editor_t *editor)
{
    add_bindkey(editor, KEY_LEFT, move_left);
    add_bindkey(editor, KEY_RIGHT, move_right);
    add_bindkey(editor, KEY_BACKSPACE, delete_char);
    add_bindkey(editor, 127, delete_char);
}
