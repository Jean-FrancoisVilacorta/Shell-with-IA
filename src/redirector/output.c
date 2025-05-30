/*
** EPITECH PROJECT, 2025
** shell
** File description:
** redirect output
*/

#include "shell.h"
#include <fcntl.h>
#include <wait.h>


int redirect_output(bintree_t *node, char ***env, int *status)
{
    __pid_t pid = -1;
    int file = open((char *)node->right->item,
        O_WRONLY | O_TRUNC | O_CREAT, 0664);

    if (!file)
        return FAIL;
    pid = fork();
    if (pid == 0){
        dup2(file, STDOUT_FD);
        *status = execute_tree(node->left, env, status);
        exit(84);
    }
    waitpid(pid, status, 0);
    close(file);
    return *status;
}

int redirect_output_double(bintree_t *node, char ***env, int *status)
{
    __pid_t pid = -1;
    int file = open((char *)node->right->item,
        O_WRONLY | O_CREAT | O_APPEND, 0664);

    if (!file)
        return FAIL;
    pid = fork();
    if (pid == 0){
        dup2(file, STDOUT_FD);
        *status = execute_tree(node->left, env, status);
        exit(84);
    }
    waitpid(pid, status, 0);
    close(file);
    return *status;
}
