COMPILER	=	cc
FLAGS		=	-Wall -Wextra -Werror
NAME		=	libgnl.a

SRCS		=	get_next_line.c	get_next_line_utils.c
SRCSB		=	get_next_line_bonus.c	get_next_line_utils_bonus.c

OBJS		=	$(SRCS:.c=.o)
OBJSB		=	$(SRCSB:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf $(OBJS) $(OBJSB)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

bonus: $(OBJSB)
