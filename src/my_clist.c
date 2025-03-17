/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int clist_size(env_t *env)
{
    int idx = 0;

    while (env->nxt != NULL){
        env = env->nxt;
        idx++;
    }
    return idx;
}

void clist_edit(env_t *env, char *name, char *value)
{
    char *tmp = NULL;

    if (env == NULL || name == NULL || value == NULL)
        return;
    while (env->nxt != NULL){
        env = env->nxt;
        if (my_strcmp(name, env->name) != 0)
            continue;
        tmp = malloc(sizeof(char) * (my_strlen(value) + 1));
        if (tmp == NULL)
            return;
        free(env->value);
        env->value = tmp;
        my_strcpy(env->value, value);
    }
}

static void free_env_push(env_t *env)
{
    if (env->nxt == NULL)
        return;
    if (env->nxt->name != NULL)
        free(env->nxt->name);
    if (env->nxt->value != NULL)
        free(env->nxt->value);
    free(env->nxt);
    env->nxt = NULL;
}

void clist_push(env_t *env, char name[], char value[])
{
    while (env->nxt != NULL)
        env = env->nxt;
    env->nxt = (env_t *) malloc(sizeof(env_t));
    if (env->nxt != NULL){
        env->nxt->nxt = NULL;
        env->nxt->name = malloc(sizeof(char) * my_strlen(name) + 1);
        env->nxt->value = malloc(sizeof(char) * my_strlen(value) + 1);
        if (env->nxt->name == NULL || env->nxt->value == NULL){
            free_env_push(env);
            env->nxt = NULL;
            return;
        }
        my_strcpy(env->nxt->name, name);
        my_strcpy(env->nxt->value, value);
    }
}

int name_in_clist(env_t *env, char *name)
{
    while (env->nxt != NULL){
        env = env->nxt;
        if (my_strcmp(env->name, name) == 0)
            return 1;
    }
    return 0;
}

static int clist_to_list_sub(env_t *env, char **res, int idx)
{
    while (env->nxt != NULL){
        res[idx + 1] = NULL;
        env = env->nxt;
        res[idx] = malloc(sizeof(char) * (my_strlen(env->name) +
            my_strlen(env->value) + 2));
        if (res[idx] == NULL){
            my_free_list(res);
            return 84;
        }
        my_strcpy(res[idx], env->name);
        my_strcat(res[idx], "=");
        my_strcat(res[idx], env->value);
        idx++;
    }
    return 0;
}

char **clist_to_list(env_t *env)
{
    int len = clist_size(env);
    char **res = malloc(sizeof(char *) * (len + 1));
    int idx = 0;

    if (res == NULL)
        return NULL;
    res[len] = NULL;
    if (clist_to_list_sub(env, res, idx) == 84)
        return NULL;
    else
        return res;
}
