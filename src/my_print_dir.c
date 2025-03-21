/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static int to_number(char *s)
{
    int number = 0;

    if (s == NULL || strlen(s) == 0){
        return -1;
    }
    for (int i = 0; s[i] != '\0'; i++){
        if (s[i] < '0' || s[i] > '9')
            return -1;
    }
    for (int i = 0; s[i] != '\0'; i++){
        number += (s[i] - 48);
        if (s[i + 1] != '\0')
            number *= 10;
    }
    return number;
}

bool is_root(void)
{
    char **status = files_to_list("/proc/self/status");
    char **splitted = NULL;
    int r = -1;

    if (status == NULL)
        return false;
    for (int i = 0; status[i] != NULL; i++){
        splitted = my_split(status[i], '\t');
        if (splitted == NULL)
            continue;
        if (!(my_strcmp(splitted[0], "Uid:"))){
            r = to_number(splitted[2]);
            break;
        }
        my_free_list(splitted);
    }
    my_free_list(splitted);
    my_free_list(status);
    return (r == 0);
    return 0;
}

static void print_path(char *path, char *home)
{
    int len = 0;

    if (my_strncmp(path, home, my_strlen(home) - 1) == 0){
        len = my_strlen(home);
        my_putstr("~");
    }
    my_putstr(path + len);
    return;
}

void print_current_dir(myshell_t *shell)
{
    char *dir = my_getenv(shell, "PWD");
    char *home = my_getenv(shell, "HOME");

    if (dir == NULL || home == NULL){
        free(dir);
        free(home);
        return;
    }
    write(1, shell->hostname, my_strlen(shell->hostname));
    write(1, ":", 1);
    print_path(dir, home);
    free(home);
    free(dir);
    if (shell->root == true)
        write(1, "# ", 2);
    else
        write(1, "> ", 2);
}
