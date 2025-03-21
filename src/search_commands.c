/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int is_binary_in_dir(char *str, char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL)
        return 0;
    while (1){
        entry = readdir(dir);
        if (entry == NULL)
            break;
        if ((entry->d_type == 8) &&
            !(my_strcmp(str, entry->d_name))) {
            closedir(dir);
            return 1;
        }
    }
    closedir(dir);
    return 0;
}

char **get_path_env(myshell_t *shell)
{
    char *PATH = my_getenv(shell, "PATH");
    char **res = NULL;

    if (PATH == NULL)
        return NULL;
    res = my_split(PATH, ':');
    free(PATH);
    return res;
}

char *extract_commands_path(myshell_t *shell)
{
    char **PATH = get_path_env(shell);
    char *res = NULL;

    if (PATH == NULL)
        return NULL;
    for (int i = 0; PATH[i] != NULL; i++){
        if (!(is_binary_in_dir(shell->splitted[0], PATH[i])))
            continue;
        res = malloc(sizeof(char) * (my_strlen(PATH[i]) +
            my_strlen(shell->splitted[0]) + 2));
        if (res != NULL){
            my_strcpy(res, PATH[i]);
            my_strcat(res, "/");
            my_strcat(res, shell->splitted[0]);
            break;
        }
    }
    my_free_list(PATH);
    return res;
}
