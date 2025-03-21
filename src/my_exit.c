/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static bool my_is_int(char *str)
{
    int first = (str[0] == '-');

    for (int i = first; str[i] != '\0'; i++){
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

static int my_atoi(char *str)
{
    int first = (str[0] == '-');
    int res = 0;

    for (int i = first; str[i] != '\0'; i++){
        res += (str[i] - 48);
        if (str[i + 1] != '\0')
            res = res * 10;
    }
    if (first == 1)
        return res * -1;
    return res;
}

int my_exit(myshell_t *shell)
{
    if ((my_list_len(shell->splitted) > 2) ||
        (my_list_len(shell->splitted) == 2
        && !my_is_int(shell->splitted[1]))){
        if (isatty(1) && isatty(0))
            my_putstr("exit: Expression Syntax.\n");
        shell->status = 1;
        return -(!(isatty(1) && isatty(0)) * 2);
    }
    if (my_list_len(shell->splitted) < 2)
        shell->status = 0;
    else
        shell->status = (my_atoi(shell->splitted[1]) % 256);
    if (shell->piped == true && shell->redirected == false)
        return 0;
    if (isatty(1) && isatty(0))
        my_putstr("exit\n");
    return -1;
}
