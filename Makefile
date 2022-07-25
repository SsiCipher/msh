CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror
# SRCS		= $(wildcard src/*.c)
SRCS		= src/token.c src/env.c src/lexer.c src/expansions.c src/expansions_utils.c src/utils.c
INCS		= -I includes
LIBS		= -Llibs -lft -lreadline

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

.PHONY: all libs $(NAME) clean fclean re
