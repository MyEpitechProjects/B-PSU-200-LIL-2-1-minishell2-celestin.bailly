/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

char *clist_get_value(env_t *env, char *name)
{
    char *res = NULL;

    while (env->nxt != NULL){
        env = env->nxt;
        if (my_strcmp(name, env->name) != 0)
            continue;
        res = malloc(sizeof(char) * (my_strlen(env->value) + 1));
        if (res == NULL)
            return NULL;
        my_strcpy(res, env->value);
    }
    return res;
}
