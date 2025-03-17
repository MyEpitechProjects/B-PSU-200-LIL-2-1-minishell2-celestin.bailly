/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static void get_stdout_cpy(char *old_buf, myshell_t *shell)
{
    if (old_buf != NULL)
        my_strcpy(shell->stdout, old_buf);
    else
        shell->stdout[0] = '\0';
}

int get_stdout_sub(myshell_t *shell, int fd, int size, int *eof)
{
    char *old_buf = NULL;
    char tmpbuff[1024 + 1];
    int byte_read = 0;

    if (shell->stdout != NULL)
        old_buf = shell->stdout;
    byte_read = read(fd, tmpbuff, 1024);
    *eof = byte_read;
    if (byte_read == 0)
        return size;
    size += byte_read;
    tmpbuff[byte_read] = '\0';
    free(shell->stdout);
    shell->stdout = malloc(size + 1);
    if (shell->stdout == NULL)
        return my_free(old_buf, -1);
    get_stdout_cpy(old_buf, shell);
    my_strcat(shell->stdout, tmpbuff);
    free(old_buf);
    return size;
}

int get_stdout(myshell_t *shell, int fd)
{
    int eof = -1;
    int size = 0;

    if (shell->stdout != NULL){
        free(shell->stdout);
        shell->stdout = NULL;
    }
    while (eof != 0){
        size = get_stdout_sub(shell, fd, size, &eof);
    }
    close(fd);
    return 0;
}
