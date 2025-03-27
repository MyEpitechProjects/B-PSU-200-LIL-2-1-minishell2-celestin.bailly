/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static void create_file(myshell_t *shell, char *name, int mode, bool is_write)
{
    char **temp_name = my_str_to_word_array(name);
    int fd = -1;

    if (temp_name == NULL)
        return;
    fd = open(temp_name[0], mode | O_WRONLY, 0644);
    my_free_list(temp_name);
    if (fd == -1)
        return;
    if (is_write == true)
        write(fd, shell->stdout, my_strlen(shell->stdout));
    close(fd);
}

static int print_read_error(char *name)
{
    char **temp_name = my_str_to_word_array(name);

    if (temp_name == NULL)
        return 1;
    my_putstr("mysh: ");
    my_putstr(temp_name[0]);
    my_free_list(temp_name);
    my_putstr(": ");
    my_putstr(strerror(errno));
    my_putstr(".\n");
    return 1;
}

static int read_file(myshell_t *shell, char *name)
{
    char **temp_name = my_str_to_word_array(name);
    struct stat file_data;
    int fd = -1;

    if (temp_name == NULL)
        return 1;
    fd = open(temp_name[0], O_RDONLY);
    my_free_list(temp_name);
    if (fd == -1)
        return print_read_error(name);
    if (fstat(fd, &file_data) == -1)
        return close(fd);
    free(shell->stdout);
    shell->stdout = malloc((file_data.st_size + 1));
    if (shell->stdout != NULL){
        shell->stdout[file_data.st_size] = '\0';
        read(fd, shell->stdout, file_data.st_size);
    }
    close(fd);
    return 0;
}

int handle_save_redirection(myshell_t *shell, char **splitted,
    int idx, bool is_write)
{
    int mode = 0;

    if ((splitted[idx + 1] == NULL || splitted[idx + 1][0] != '>'))
        return 0;
    if (splitted[idx + 2] == NULL || splitted[idx + 2][0] != '>')
        mode = (O_CREAT | O_TRUNC);
    else
        mode = O_APPEND;
    create_file(shell, splitted[idx + 2 + (mode == O_APPEND)], mode, is_write);
    if (mode == (O_CREAT | O_TRUNC))
        return 2;
    else
        return 3;
    return 0;
}

// mode = 1 : File | mode = 2 : EOF
int handle_get_redirection(myshell_t *shell, char **splitted, int idx)
{
    int mode = 0;

    if ((splitted[idx + 1] == NULL || splitted[idx + 1][0] != '<'))
        return 0;
    if (splitted[idx + 2] == NULL || splitted[idx + 2][0] != '<')
        mode = 1;
    else
        mode = 2;
    if (mode == 1){
        if (read_file(shell, splitted[idx + 2]) == 0)
            return 2;
        return -1;
    } else {
        parse_eof(shell, splitted[idx + 3]);
        return 3;
    }
    return 0;
}

int set_pipe_flg(myshell_t *shell, char **splitted, int i)
{
    if (splitted[i + 1] != NULL && splitted[i + 1][0] == '|'){
        shell->piped = true;
        i += (splitted[i + 1][0] != '>');
    }
    if (splitted[i + 1] != NULL && splitted[i + 1][0] == '>'){
        shell->piped = true;
        shell->redirected = true;
        i += (splitted[i + 1][0] != '>');
    }
    return i;
}

static int calc_min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

bool is_good_eof(char *str1, char *str2)
{
    char **eof = my_str_to_word_array(str1);
    int max = 0;

    if (eof == NULL)
        return false;
    if (strlen(eof[0]) != (strlen(str2) - 1)){
        my_free_list(eof);
        return false;
    }
    max = calc_min(strlen(eof[0]), (strlen(str2) - 1));
    if (!my_strncmp(eof[0], str2, max)){
        my_free_list(eof);
        return true;
    }
    my_free_list(eof);
    return false;
}
