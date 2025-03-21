/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int get_str_by_id(char **lst, char *str)
{
    int idx = 0;

    for (int i = 0; lst[i] != NULL; i++){
        if (!(my_strncmp(lst[i], str, (int) my_strlen(str))))
            return idx;
        idx++;
    }
    return idx;
}

int handle_builtins(myshell_t *shell, char **builtins)
{
    int (*builtins_function[])(myshell_t *shell) = {my_exit,
        my_env, my_cd, my_setenv_comm, my_unsetenv_comm};
    int id = get_str_by_id(builtins, shell->splitted[0]);
    int res = 0;

    if (shell->piped == true){
        free(shell->stdout);
        shell->stdout = malloc(1);
        if (shell->stdout != NULL)
            shell->stdout[0] = '\0';
    }
    res = builtins_function[id](shell);
    if (res == -2)
        shell->status = 1;
    return res;
}

static int handle_binaries(myshell_t *shell)
{
    return create_fork(shell, NULL);
}

static bool is_regular_commands(char *str)
{
    if ((my_strlen(str) > 1 && (str[0] == '.' && str[1] == '/')) &&
        (my_strlen(str) > 2 && (str[0] == '.' && str[1] == '.'
        && str[2] == '/')))
        return false;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '/')
            return false;
    }
    return true;
}

int handle_commands(myshell_t *shell, char **builtins)
{
    char *path = NULL;

    if (strlstcmp(builtins, shell->splitted[0]))
        return handle_builtins(shell, builtins);
    path = extract_commands_path(shell);
    if (path != NULL)
        return create_fork(shell, path);
    free(path);
    if (!is_regular_commands(shell->splitted[0]))
        return handle_binaries(shell);
    my_putstr(shell->splitted[0]);
    my_putstr(": Command not found.\n");
    shell->status = 1;
    return 0;
}
