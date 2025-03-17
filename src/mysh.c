/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_list_len(char **lst)
{
    int idx = 0;

    while (lst[idx] != NULL)
        idx++;
    return idx;
}

int strlstcmp(char **lst, char const *str)
{
    for (int i = 0; lst[i] != NULL; i++){
        if (!(my_strcmp(lst[i], str)))
            return 1;
    }
    return 0;
}

static void read_hostname(myshell_t *shell)
{
    int fd = open("/etc/hostname", O_RDONLY);
    char hostname[get_file_size("/etc/hostname") + 1];
    size_t bytesRead = 0;

    shell->hostname = NULL;
    if (fd == -1)
        return;
    bytesRead = read(fd, hostname, sizeof(hostname));
    if (bytesRead == 0) {
        close(fd);
        return;
    }
    hostname[bytesRead - 1] = '\0';
    shell->hostname = malloc(sizeof(char) * my_strlen(hostname) + 1);
    if (shell->hostname != NULL)
        my_strcpy(shell->hostname, hostname);
    close(fd);
}

int init_shell(myshell_t *shell, char **env)
{
    char str[1024];

    shell->stdout = NULL;
    shell->splitted = NULL;
    shell->env = NULL;
    shell->commands = NULL;
    shell->status = 0;
    shell->root = is_root();
    read_hostname(shell);
    if (shell->hostname == NULL)
        return 84;
    shell->env = env_cpy(env);
    if (shell->env == NULL)
        return 84;
    getcwd(str, sizeof(str));
    my_setenv(shell, "PWD", str, 0);
    return 0;
}

int main(int argc, char **argv, char **env)
{
    myshell_t *shell = malloc(sizeof(myshell_t));

    argc = argc;
    argv[0][0] = argv[0][0];
    if (shell == NULL)
        return 84;
    if (init_shell(shell, env) == 84)
        return free_struct(shell, 84);
    shell_loop(shell);
    return free_struct(shell, shell->status);
}
