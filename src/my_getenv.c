/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** split
*/

#include "mysh.h"

char *my_getenv(myshell_t *shell, char *name)
{
    return clist_get_value(shell->env, name);
}
