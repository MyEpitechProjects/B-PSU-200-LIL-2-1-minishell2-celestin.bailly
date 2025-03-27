/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static int sum_env(char **env)
{
    int size = 0;

    for (int i = 0; env[i] != NULL; i++)
        size += (strlen(env[i]) + 1);
    return size;
}

static void build_env(char **env, char *env_str)
{
    env_str[0] = '\0';
    for (int i = 0; env[i] != NULL; i++){
        my_strcat(env_str, env[i]);
        my_strcat(env_str, "\n");
    }
}

static void write_env_str(char *env_str)
{
    write(1, env_str, my_strlen(env_str));
    free(env_str);
}

int my_env(myshell_t *shell)
{
    char **env = clist_to_list(shell->env);
    int env_len = sum_env(env);
    char *env_str = NULL;

    if (env == NULL)
        return -2;
    env_str = malloc(env_len + 1);
    if (env_str == NULL){
        my_free_list(env);
        return -2;
    }
    build_env(env, env_str);
    my_free_list(env);
    if (shell->piped == true){
        free(shell->stdout);
        shell->stdout = env_str;
    } else
        write_env_str(env_str);
    shell->status = 0;
    return 0;
}
