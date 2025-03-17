/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_env(myshell_t *shell)
{
    char **env = clist_to_list(shell->env);

    if (env == NULL)
        return 84;
    for (int i = 0; env[i] != NULL; i++){
        write(1, env[i], my_strlen(env[i]));
        write(1, "\n", 1);
    }
    shell->status = 0;
    return 0;
}
