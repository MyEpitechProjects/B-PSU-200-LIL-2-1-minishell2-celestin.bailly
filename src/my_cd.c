/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

void my_putstr(const char *str)
{
    if (str == NULL)
        return;
    write(1, str, my_strlen(str));
}

static char *fix_path(char *path, char *home)
{
    int len = 0;
    char *res = NULL;

    if (path[0] == '~' && my_strlen(path) > 1 && path[1] != '/')
        return get_specific_usr_home(path + 1);
    if (path[0] == '~')
        len = (my_strlen(path) + my_strlen(home));
    else
        len = (my_strlen(path));
    res = malloc(sizeof(char) * (len + 1));
    if (res == NULL)
        return NULL;
    if (path[0] == '~'){
        my_strcpy(res, home);
        my_strcat(res, path + 1);
    } else
        my_strcpy(res, path);
    return res;
}

void change_dir(myshell_t *shell)
{
    char str[1024];
    char *old_env = NULL;

    if (shell->piped == true && shell->redirected == false)
        return;
    old_env = my_getenv(shell, "PWD");
    if (old_env == NULL){
        free(old_env);
        return;
    }
    getcwd(str, sizeof(str));
    my_setenv(shell, "PWD", str, 1);
    my_setenv(shell, "OLDPWD", old_env, 1);
    free(old_env);
}

static int my_cd_home(myshell_t *shell, char *home)
{
    if (chdir(home) != 0){
        my_putstr(shell->splitted[1]);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putstr(".\n");
        shell->status = 1;
        return 1;
    }
    shell->status = 0;
    return 0;
}

static int my_cd_old(myshell_t *shell)
{
    char *old_env;

    old_env = my_getenv(shell, "OLDPWD");
    if (old_env != NULL && chdir(old_env) != 0){
        my_putstr(shell->splitted[1]);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putstr(".\n");
        free(old_env);
        shell->status = 1;
        return 1;
    }
    free(old_env);
    shell->status = 0;
    return 0;
}

static int user_error(myshell_t *shell)
{
    my_putstr("Unknown user: ");
    my_putstr(shell->splitted[1] + 1);
    my_putstr(".\n");
    shell->status = 1;
    return 1;
}

static int my_cd_normal(myshell_t *shell, char *home)
{
    char *path = fix_path(shell->splitted[1], home);

    if (path == NULL)
        return user_error(shell);
    if (chdir(path) != 0){
        my_putstr(path);
        free(path);
        my_putstr(": ");
        my_putstr(strerror(errno));
        my_putstr(".\n");
        shell->status = 1;
        return 1;
    }
    free(path);
    shell->status = 0;
    return 0;
}

static int my_cd_do(myshell_t *shell, char *home, int len)
{
    if (len == 1 && !(len > 1 && my_strlen(shell->splitted[0]) == 1 &&
        shell->splitted[0][0] == '-'))
        return my_cd_home(shell, home);
    if (len == 2 && (my_strlen(shell->splitted[1]) == 1 &&
        shell->splitted[1][0] == '-'))
        return my_cd_old(shell);
    if (len == 2 && !(my_strlen(shell->splitted[1]) == 1 &&
        shell->splitted[1][0] == '-'))
        return my_cd_normal(shell, home);
    return 0;
}

int my_cd(myshell_t *shell)
{
    int len = my_list_len(shell->splitted);
    char *home = my_getenv(shell, "HOME");
    int res = 1;

    if (home == NULL)
        return -(!(isatty(1) && isatty(0)) * 2);
    if (len > 2){
        my_putstr("cd: Too many arguments.\n");
        free(home);
        shell->status = 1;
        return -(!(isatty(1) && isatty(0)) * 2);
    }
    res = my_cd_do(shell, home, len);
    if (res == 0)
        change_dir(shell);
    free(home);
    return -(res * 2);
}
