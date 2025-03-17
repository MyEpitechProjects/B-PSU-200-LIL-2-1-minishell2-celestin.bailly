/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_env_len(env_t *tmp)
{
    int idx = 0;

    while (tmp->nxt != NULL){
        tmp = tmp->nxt;
        idx += 1;
    }
    return idx + 1;
}
