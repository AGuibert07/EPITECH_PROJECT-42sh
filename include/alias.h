/*
** EPITECH PROJECT, 2026
** G2 - Shell Programming - 42sh
** File description:
** Alias structure and function prototypes
*/

#ifndef ALIAS_H_
    #define ALIAS_H_

typedef struct alias_s {
    char *name;
    char *command;
    struct alias_s *next_alias;
} alias_t;

// alias_utils.c
char *get_alias(alias_t *list, char *name);
void add_alias(alias_t **list, char *name, char *command);
void delete_alias(alias_t **list, char *name);

#endif /* ALIAS_H_ */
