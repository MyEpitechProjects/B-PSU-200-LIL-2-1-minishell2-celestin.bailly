/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_free(void *data, int value)
{
    free(data);
    return value;
}

void my_free_list(char **lst)
{
    if (lst == NULL)
        return;
    for (int i = 0; lst[i] != NULL; i++)
        free(lst[i]);
    free(lst);
}

static void free_env_idx(env_t *tmp, int i)
{
    env_t *old_tmp = NULL;

    for (int i2 = 0; i2 < i; i2++){
        old_tmp = tmp;
        tmp = tmp->nxt;
    }
    free(tmp->name);
    free(tmp->value);
    free(tmp);
    if (old_tmp != NULL)
        old_tmp->nxt = NULL;
}

void free_env(env_t *temp)
{
    int len = 0;

    if (temp == NULL)
        return;
    len = my_env_len(temp);
    for (int i = len - 1; i > 0; i--)
        free_env_idx(temp, i);
}

int free_struct(myshell_t *shell, int value)
{
    if (shell->splitted != NULL)
        my_free_list(shell->splitted);
    shell->splitted = NULL;
    if (shell->commands != NULL)
        free(shell->commands);
    shell->commands = NULL;
    if (shell->hostname != NULL)
        free(shell->hostname);
    if (shell->env != NULL){
        free_env(shell->env);
        free(shell->env);
    }
    if (shell->stdout != NULL)
        free(shell->stdout);
    free(shell);
    return value;
}
