CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror
INCS		= -I includes
LIBS		= -lreadline -Llibs -lft
SRCS		= src/parsing/env.c src/parsing/env_ops.c \
			src/parsing/token.c src/parsing/lexer.c \
			src/parsing/error_check.c src/parsing/error_check_utils.c \
			src/parsing/expansions.c src/parsing/expansions_utils.c \
			src/parsing/ast_tree.c src/parsing/ast_tree_utils.c \
			src/parsing/heredoc.c src/parsing/utils.c src/parsing/debug.c \
			src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c \
			src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/builtins/utils.c \
			src/execution/exec.c src/execution/exec_utils.c src/execution/exec_cmd.c

all: libs $(NAME)

libs:
	@make -C libs/libft
	@cp libs/libft/libft.a libs
	@cp libs/libft/libft.h includes

$(NAME): $(SRCS) main.c
	$(CC) $(FLAGS) $(INCS) $(SRCS) main.c $(LIBS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all libs clean fclean re
