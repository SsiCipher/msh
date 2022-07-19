CC			= cc
NAME		= msh
FLAGS		= -Wall -Wextra -Werror
SRCS		= $(wildcard src/*.c)
INCS		= -I includes
LIBS		= -Llibs -lft -lgnl -lreadline

all: libs $(NAME)

libs:
	@make -C libs/libft
	@cp libs/libft/libft.a libs
	@cp libs/libft/libft.h includes
	@make -C libs/get_next_line
	@cp libs/get_next_line/libgnl.a libs
	@cp libs/libft/libgnl.h includes

$(NAME): $(SRCS) msh.c
	$(CC) $(FLAGS) $(INCS) $(SRCS) msh.c $(LIBS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all libs $(NAME) clean fclean re
