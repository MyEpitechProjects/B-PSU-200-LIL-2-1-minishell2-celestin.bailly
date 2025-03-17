/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int is_stdin_non_empty(void)
{
    struct stat st;

    if (fstat(0, &st) == 0) {
        if ((S_ISREG(st.st_mode) && st.st_size > 0)
            || (S_ISFIFO(st.st_mode))) {
            return 1;
        }
        return 0;
    }
    return 0;
}

int getlines_sub(char **buffer)
{
    size_t len = 0;
    int size = -1;

    if (*buffer != NULL){
        free(*buffer);
        *buffer = NULL;
    }
    if ((is_stdin_non_empty()) || (isatty(1) && isatty(0)))
        size = getline(buffer, &len, stdin);
    if (size > 0)
        (*buffer)[size - 1] = '\0';
    return size;
}

int commands(myshell_t *shell)
{
    char *builtins[] = {"exit", "env", "cd", "setenv",
        "unsetenv", NULL};
    int res = 0;

    res = handle_commands(shell, builtins);
    my_free_list(shell->splitted);
    shell->splitted = NULL;
    return res;
}

static int handle_sub_commands(myshell_t *shell, char **splitted)
{
    int l = 0;

    for (int i = 0; splitted[i] != NULL; i++){
        shell->piped = false;
        shell->splitted = my_str_to_word_array(splitted[i]);
        i += handle_get_redirection(shell, splitted, i);
        if (splitted[i + 1] != NULL && (splitted[i + 1][0] == '|' ||
            splitted[i + 1][0] == '>')){
            shell->piped = true;
            i += (splitted[i + 1][0] != '>');
        }
        l = commands(shell);
        i += handle_save_redirection(shell, splitted, i);
        if (l == -1 || (shell->status != 0 && l == 0 &&
            !(isatty(1) && isatty(0))))
            return -1;
    }
    return l;
}

static int handle_multiple(myshell_t *shell, char **splitted)
{
    int l = 0;
    char **sub_splitted = NULL;

    if (splitted == NULL)
        return -1;
    for (int i = 0; splitted[i] != NULL; i++){
        sub_splitted = my_strsplit(splitted[i], "|<>", '\0');
        if (sub_splitted == NULL)
            continue;
        l = handle_sub_commands(shell, sub_splitted);
        my_free_list(splitted);
        shell->stdout = NULL;
        if (l == -1){
            my_free_list(splitted);
            return -1;
        }
    }
    my_free_list(splitted);
    return l;
}

int shell_loop_iteration(myshell_t *shell, int l, int reads, char **split)
{
    if (isatty(0) && isatty(1))
        print_current_dir(shell);
    reads = getlines_sub(&shell->commands);
    if (reads == -1)
        return 0;
    if (reads < 2)
        return 1;
    split = my_split(shell->commands, ';');
    if (split == NULL)
        return 1;
    if (scan_line(shell, split))
        l = handle_multiple(shell, split);
    else
        l = -1;
    if (l == -1 || (shell->status != 0 && l == 0 &&
        !(isatty(1) && isatty(0))))
        return 0;
    return 1;
}

int shell_loop(myshell_t *shell)
{
    int l = 0;
    int reads = -1;
    char **split = NULL;

    while (1){
        if (shell_loop_iteration(shell, l, reads, split) == 0)
            return 0;
    }
}
