/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

bool is_redr(char *str)
{
    char c = str[0];

    if (c == '|' || c == '<' || c == '>')
        return true;
    return false;
}

static bool is_valid_redirection(char **split, int i, char c)
{
    if (split[i][0] == c && (i == 0 || is_redr(split[i - 1]) ||
        ((split[i + 1] == NULL || ((is_redr(split[i + 1]) &&
        split[i + 1][0] != c))) &&
        (split[i + 1] == NULL || (split[i + 2] == NULL ||
        (is_redr(split[i + 2]))))))){
        if ((split[i + 1] == NULL || ((is_redr(split[i + 1]) &&
            split[i + 1][0] != c))) &&
            (split[i + 1] == NULL || (split[i + 2] == NULL ||
            (is_redr(split[i + 2])))))
            my_putstr("Missing name for redirect.\n");
        else
            my_putstr("Invalid null command.\n");
        return false;
    }
    return true;
}

bool is_valid(char **split)
{
    for (int i = 0; split[i] != NULL; i++){
        if (split[i][0] == '|' && ((i == 0 || is_redr(split[i - 1])) ||
            (split[i + 1] == NULL || is_redr(split[i + 1])))){
            my_putstr("Invalid null command.\n");
            return false;
        }
        if (!is_valid_redirection(split, i, '<') ||
            !is_valid_redirection(split, i, '>'))
            return false;
        if ((split[i][0] == '<' || split[i][0] == '>') && split[i + 1] != NULL)
            i++;
    }
    return true;
}

bool scan_line(myshell_t *shell, char **split)
{
    char **split_2 = NULL;
    int res = true;

    for (int i = 0; split[i] != NULL; i++){
        split_2 = my_strsplit(split[i], "<>|", '\0');
        if (split_2 == NULL){
            shell->status = 1;
            return false;
        }
        if (!(is_valid(split_2))){
            shell->status = 1;
            res = false;
        }
        my_free_list(split_2);
    }
    return res;
}
