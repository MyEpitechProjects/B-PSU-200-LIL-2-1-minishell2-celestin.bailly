##
## EPITECH PROJECT, 2025
## fozzbazz
## File description:
## Makefile
##

NAME	= mysh

SRC	=	src/mysh.c\
		src/my_str_to_word_array.c\
		src/my_env.c\
		src/my_exit.c\
		src/my_getenv.c\
		src/my_strcat.c\
		src/my_split.c\
		src/my_free.c\
		src/my_cd.c\
		src/my_setenv.c\
		src/my_clist.c\
		src/my_strcpy.c\
		src/my_list_to_clist.c\
		src/my_clist_get_value.c\
		src/execute_commands.c\
		src/my_clist_len.c\
		src/shell_loop.c\
		src/my_print_dir.c\
		src/my_commands.c\
		src/my_strcmp.c\
		src/search_commands.c\
		src/file_reader.c\
		src/clist_delete.c\
		src/my_unsetenv.c\
		src/my_stdfd.c\
		src/my_strsplit.c\
		src/commands_scanner.c\
		src/redirection.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

CFLAGS  = -Wall -Wextra -fanalyzer

LFLAGS	= -I include

all:
	$(CC) -c $(SRC) $(CFLAGS) $(LFLAGS)
	@mv $(notdir $(OBJ)) src
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LFLAGS)

debug:
	$(CC) -c $(SRC) $(CFLAGS) $(LFLAGS) -g
	@mv $(notdir $(OBJ)) src
	$(CC) -o $(NAME)_debug $(OBJ) $(CFLAGS) $(LFLAGS) -g

clean:
	@rm -f $(NAME)
	@rm -f $(NAME)_debug
	@rm -f $(OBJ)

fclean: clean
	@rm -rf *.o
	@rm -rf *.a

re: fclean all

run: all
	./$(NAME)
