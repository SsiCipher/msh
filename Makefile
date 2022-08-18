CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror
SRCS		= src/env.c src/heredoc.c src/builtins.c \
			src/error_check.c src/error_check_utils.c src/token.c \
			src/tree.c src/lexer.c src/expansions.c src/expansions_utils.c \
			src/utils.c src/debug.c
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
