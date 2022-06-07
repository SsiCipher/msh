NAME = libft.a
FLAGS = -Wall -Wextra -Werror

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c  \
		ft_isprint.c ft_isspace.c ft_toupper.c ft_tolower.c \
		ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c \
		ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strcmp.c \
		ft_strncmp.c ft_strstr.c ft_strnstr.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strmapi.c ft_striteri.c \
		ft_strtrim.c ft_split.c ft_atoi.c ft_itoa.c \
		ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_puthex_fd.c ft_putbin_fd.c\
		ft_every.c ft_any.c ft_abs.c ft_realloc.c ft_bsort.c \
		ft_intlen.c ft_swap.c ft_qsort.c ft_countchr.c

OBJS = $(SRCS:.c=.o)

SRCSB =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		$(SRCS)

OBJSB = $(SRCSB:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

%.o: %.c libft.h
	cc $(FLAGS) -c $< -o $@
	ar rcs $(NAME) $@

clean:
	rm -rf $(OBJSB)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus: $(OBJSB)
