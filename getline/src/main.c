/*
** EPITECH PROJECT, 2025
** Bonus
** File description:
** main
*/

#include "my_getline.h"
#include "gpt.h"
#include <unistd.h>

int main(void)
{
    char path[140];
    char *line = NULL;

    if (getcwd(path, sizeof(path)) == NULL)
        return 84;
    line = my_getline(path);
    printf("|%s|\n", line);
    if (line == NULL)
        return EXIT_ERROR;
    if (line[0] == '#')
        gpt_demand(line);
    free(line);
    return SUCCESS;
}
