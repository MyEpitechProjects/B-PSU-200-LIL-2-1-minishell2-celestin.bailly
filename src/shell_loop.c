/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static void put_str_eof(myshell_t *shell, char *str)
{
    int buff_size = 0;
    int new_str_size = my_strlen(str);
    char *tmpbuffer = NULL;

    if (shell->stdout != NULL){
        buff_size = my_strlen(shell->stdout);
        tmpbuffer = shell->stdout;
    }
    shell->stdout = malloc(buff_size + new_str_size + 1);
    if (shell->stdout == NULL){
        shell->stdout = tmpbuffer;
        return;
    }
    if (tmpbuffer != NULL)
        my_strcpy(shell->stdout, tmpbuffer);
    if (tmpbuffer != NULL)
        my_strcat(shell->stdout, str);
    else
        my_strcpy(shell->stdout, str);
    free(tmpbuffer);
}

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

int getlines_sub(char **buffer, bool nline)
{
    size_t len = 0;
    int size = -1;

    if (*buffer != NULL){
        free(*buffer);
        *buffer = NULL;
    }
    if ((is_stdin_non_empty()) || (isatty(1) && isatty(0)))
        size = getline(buffer, &len, stdin);
    if (size > 0 && nline == false)
        (*buffer)[size - 1] = '\0';
    return size;
}

void parse_eof(myshell_t *shell, char *eof)
{
    int reads = 0;
    char *buffer = NULL;

    free(shell->stdout);
    shell->stdout = NULL;
    if (eof == NULL)
        return;
    while (reads != -1){
        if (isatty(0) && isatty(1))
            write(1, "? ", 2);
        reads = getlines_sub(&buffer, true);
        if (reads == -1 || reads < 1)
            continue;
        if (is_good_eof(eof, buffer) == true)
            break;
        put_str_eof(shell, buffer);
    }
    if (reads > 0)
        free(buffer);
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

static void set_default_red_pipe(myshell_t *shell)
{
    shell->piped = false;
    shell->redirected = false;
}

static int handle_sub_commands(myshell_t *shell, char **splitted)
{
    int l = 0;
    int d = 0;

    for (int i = 0; splitted[i] != NULL; i++){
        set_default_red_pipe(shell);
        shell->splitted = my_str_to_word_array(splitted[i]);
        d = handle_get_redirection(shell, splitted, i);
        if (d == -1)
            return 1;
        i += d;
        i = set_pipe_flg(shell, splitted, i);
        handle_save_redirection(shell, splitted, i, false);
        l = commands(shell);
        i += handle_save_redirection(shell, splitted, i, true);
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
        my_free_list(sub_splitted);
        sub_splitted = my_strsplit(splitted[i], "|<>", '\0');
        if (sub_splitted == NULL)
            continue;
        l = handle_sub_commands(shell, sub_splitted);
        free(shell->stdout);
        shell->stdout = NULL;
        if (l == -1){
            my_free_list(sub_splitted);
            return -1;
        }
    }
    my_free_list(sub_splitted);
    return l;
}

static int shell_loop_iteration(myshell_t *shell, int l,
    int reads, char **split)
{
    if (isatty(0) && isatty(1))
        print_current_dir(shell);
    reads = getlines_sub(&shell->commands, false);
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
        l = 1;
    my_free_list(split);
    if (l == -1 || l == -2)
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
