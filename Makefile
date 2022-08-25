CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
SRCS		= src/env.c src/error_check.c src/error_check_utils.c \
			src/token.c src/tree.c src/lexer.c src/expansions.redo.c src/expansions_utils.c \
			src/utils.c src/debug.c src/env_ops.c \
			src/builtins/cd.c src/builtins/echo.c src/builtins/env.c src/builtins/exit.c \
			src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/builtins/utils.c
INCS		= -I includes
LIBS		= -l readline -L libs -l ft

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
