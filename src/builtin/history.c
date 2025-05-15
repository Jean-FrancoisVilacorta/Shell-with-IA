/*
** EPITECH PROJECT, 2025
** 42zh
** File description:
** history
*/

#include "my_getline.h"
#include <stdio.h>

static int print_history(struct history_t *history,
    size_t start, size_t end)
{
    int ret = 0;

    if (history == NULL) {
        free_history(history);
        return SUCCESS;
    }
    ret = print_history(history->next, start, end);
    if (ret == 2 ||ret == -1)
        return ret;
    if (history->id < start)
        return SUCCESS;
    dprintf(0,"(%li) %s\n", history->id, history->str);
    if (history->id == end) {
        free_history(history);
        return 2;
    }
    return SUCCESS;
}

int builtin_history(char ***env, char **commands)
{
    struct history_t *history = get_history();
    size_t start = 0;
    size_t end = 0;

    if (history == NULL || env == NULL)
        return -1;
    if (commands[1] == NULL)
        return print_history(history, 0, 0);
    start = atol(commands[1]);
    if (commands[2] == NULL)
        return print_history(history, start, 0);
    end = atol(commands[2]);
    return print_history(history, start, end);
}