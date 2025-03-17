/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_unsetenv(myshell_t *shell, char *name)
{
    int already = name_in_clist(shell->env, name);

    if (already == 1){
        delete(shell->env, name);
    }
    return 0;
}

int my_unsetenv_comm(myshell_t *shell)
{
    int len = my_list_len(shell->splitted);

    if (len == 1){
        shell->status = 1;
        my_putstr("unsetenv: Too few arguments.\n");
        return 0;
    }
    for (int i = 1; shell->splitted[i] != NULL; i++)
        my_unsetenv(shell, shell->splitted[i]);
    shell->status = 0;
    return 0;
}
