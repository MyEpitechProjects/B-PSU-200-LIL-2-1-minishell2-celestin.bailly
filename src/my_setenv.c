/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_setenv(myshell_t *shell, char *name, char *value, int overwrite)
{
    int already = name_in_clist(shell->env, name);

    if (already == 1){
        if (overwrite == 1)
            clist_edit(shell->env, name, value);
    }
    if (already == 0){
        clist_push(shell->env, name, value);
    }
    return 0;
}

int is_letter(char s)
{
    return ((s >= 65 && s <= 90) || (s >= 97 && s <= 122)
        || s == '.' || s == '_');
}

int is_correct_string(char *s)
{
    for (int i = 0; s[i] != '\0'; i++){
        if (!(is_letter(s[i])) && (s[i] < 48 || s[i] > 57)
            && s[i] != '_' && s[i] != '.')
            return 0;
    }
    return 1;
}

static int handle_error(myshell_t *shell, int len)
{
    shell->status = 1;
    if (len > 3)
        my_putstr("setenv: Too many arguments.\n");
    if (!(is_letter(shell->splitted[1][0])))
        my_putstr("setenv: Variable name must begin with a letter.\n");
    if (!(is_correct_string(shell->splitted[1])) &&
        (is_letter(shell->splitted[1][0]))){
        my_putstr("setenv: Variable name must contain alphanumeric");
        my_putstr(" characters.\n");
    }
    return -(!(isatty(1) && isatty(0)) * 2);
}

int my_setenv_comm(myshell_t *shell)
{
    int len = my_list_len(shell->splitted);

    if (len == 1)
        return my_env(shell);
    if (len > 3 || !(is_letter(shell->splitted[1][0])) ||
        !(is_correct_string(shell->splitted[1])))
        return handle_error(shell, len);
    shell->status = 0;
    if (shell->piped == true && shell->redirected == false)
        return 0;
    if (len == 2)
        return my_setenv(shell, shell->splitted[1], "", 1);
    return my_setenv(shell, shell->splitted[1], shell->splitted[2], 1);
}
