/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

char *merge(char **splitted)
{
    int len = 0;
    char *res;

    for (int i = 1; splitted[i] != NULL; i++)
        len += (my_strlen(splitted[i]) + 1);
    res = malloc(sizeof(char) * (len + 1));
    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 1; splitted[i] != NULL; i++){
        my_strcat(res, splitted[i]);
        if (splitted[i + 1] != NULL)
            my_strcat(res, "=");
    }
    return res;
}

void env_cpy_push(env_t *res, char **environ)
{
    char *value;
    char **splitted;

    for (int i = 0; environ[i] != NULL; i++){
        splitted = my_split(environ[i], '=');
        if (splitted == NULL)
            return;
        value = merge(splitted);
        if (value == NULL){
            my_free_list(splitted);
            return;
        }
        clist_push(res, splitted[0], value);
        my_free_list(splitted);
        free(value);
    }
}

env_t *env_cpy(char **environ)
{
    env_t *res = malloc(sizeof(env_t));

    if (res == NULL)
        return NULL;
    res->name = NULL;
    res->value = NULL;
    res->nxt = NULL;
    env_cpy_push(res, environ);
    return res;
}
