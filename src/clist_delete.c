/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

void delete_idx(env_t *tmp)
{
    env_t *to_free;

    if (tmp == NULL)
        return;
    free(tmp->nxt->name);
    free(tmp->nxt->value);
    to_free = tmp->nxt;
    tmp->nxt = to_free->nxt;
    free(to_free);
}

void free_last(env_t *tmp, env_t *old_tmp)
{
    free(tmp->name);
    free(tmp->value);
    free(tmp);
    tmp = old_tmp;
    if (tmp != NULL)
        tmp->nxt = NULL;
}

int delete(env_t *tmp, char *name)
{
    env_t *old_tmp = NULL;
    int len = my_env_len(tmp);

    while ((tmp->name == NULL || my_strcmp(tmp->name, name) != 0)
        && tmp->nxt != NULL){
        old_tmp = tmp;
        tmp = tmp->nxt;
    }
    if (!(my_strcmp(tmp->name, name)) && len > 1){
        if (tmp->nxt != NULL){
            delete_idx(old_tmp);
        } else
            free_last(tmp, old_tmp);
        return 0;
    }
    return 84;
}
