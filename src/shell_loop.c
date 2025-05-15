/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** main loop
*/

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *handle_exit(char *command)
{
    char **array = my_str_to_word_arr(command, "|");
    size_t len = 0;

    if (my_array_len(array) <= 0)
        return command;
    if (!strncmp(array[0], "exit", 4) && my_array_len(array) > 1) {
        delete_element_array(array, 0);
        len = get_full_len_command(array);
        command = malloc(len + 1);
        if (!command)
            return NULL;
        memset(command, '\0', len);
        for (size_t i = 0; array[i]; i++) {
            strcat(command, array[i]);
            command = (array[i + 1]) ?
                strcat(command, "|") : strcat(command, "'\0'");
        }
    }
    return command;
}

static int handle_command(char *command, char ***env)
{
    int status = 0;

    command = handle_exit(command);
    if (!command)
        return status;
    if (command[0] == '#') {
        return gpt_demand(command);
    }
    if (!strcmp(command, "exit"))
        return -1;
    status = exec_all_commands(command, env);
    return status;
}

int shell_loop(char ***env, int is_tty)
{
    char *command = NULL;
    int status = 0;
    job_t **jobs = get_jobs_list();
    char path[140];

    if (getcwd(path, sizeof(path)) == NULL)
        return 84;
    while (1) {
        command = my_getline(path);
        update_job_status(jobs);
        status = handle_command(command, env);
        if (status == -1 || (!is_tty && !my_strcmp(command, "")))
            break;
        free(command);
        command = NULL;
    }
    free_list_alias();
    free(command);
    return status;
}
