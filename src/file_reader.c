/*
** EPITECH PROJECT, 2025
** my_sudo
** File description:
** Put lines in a list
*/

#include "mysh.h"

long get_file_size(const char *filename)
{
    char dest[1024];
    int fd = open(filename, O_RDONLY);
    int byte_reads = 1;
    long size = 0;

    if (fd == -1)
        return -1;
    while (byte_reads != 0){
        byte_reads = read(fd, dest, sizeof(dest));
        if (byte_reads == -1){
            close(fd);
            return -1;
        }
        size += byte_reads;
    }
    close(fd);
    return size;
}

char **files_to_list(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    int len = get_file_size(file_name);
    char *file;
    char **result;

    if (len == -1 && fd != -1)
        close(fd);
    if (len == -1 || fd == -1)
        return NULL;
    file = malloc(sizeof(char) * (len + 1));
    if (file == NULL){
        close(fd);
        return NULL;
    }
    file[len] = '\0';
    len = read(fd, file, len);
    result = my_split(file, '\n');
    free(file);
    close(fd);
    return result;
}

char *usr_loop(char *user, char **line)
{
    char *res = NULL;

    if (line == NULL || my_strlen(line[0]) == 0)
        return NULL;
    if (my_strcmp(user, line[0]) != 0 || my_strlen(line[5]) == 0)
        return NULL;
    res = malloc(sizeof(char) * (my_strlen(line[5]) + 1));
    if (res == NULL)
        return NULL;
    my_strcpy(res, line[5]);
    return res;
}

char *get_specific_usr_home(char *user)
{
    char **passwd = files_to_list("/etc/passwd");
    char **line = NULL;
    char *res = NULL;

    if (passwd == NULL)
        return NULL;
    for (int i = 0; passwd[i] != NULL; i++){
        line = my_split(passwd[i], ':');
        res = usr_loop(user, line);
        my_free_list(line);
        if (res != NULL){
            my_free_list(passwd);
            return res;
        }
    }
    my_free_list(passwd);
    return NULL;
}
