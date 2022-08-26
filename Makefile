CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror
INCS		= -I includes
LIBS		= -lreadline -Llibs -lft
SRCS		= src/env.c src/env_ops.c \
			src/token.c src/lexer.c \
			src/error_check.c src/error_check_utils.c \
			src/expansions.c src/expansions_utils.c \
			src/ast_tree.c src/ast_tree_utils.c \
			src/heredoc.c src/utils.c src/debug.c \
			src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c \
			src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/builtins/utils.c

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
