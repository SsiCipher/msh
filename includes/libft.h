/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:23:09 by marvin            #+#    #+#             */
/*   Updated: 2021/11/04 17:23:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Libc Functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nstr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

// Additional Functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Bonus Functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *(new));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *(new));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// My functions
int		ft_isspace(int c);
int		ft_every(const char *str, int (*f)(char));
int		ft_any(const char *str, int (*f)(char));
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_abs(int n);
void	ft_bsort(int len, int *arr, int (*cmp)(int, int));
int		ft_isspace(int c);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	ft_puthex_fd(unsigned int n, int fd, int is_prefixed);
void	ft_putbin_fd(unsigned int n, int fd, int is_prefixed);
void	ft_swap(int *arr, int i, int j);
int		ft_intlen(int n);
void	ft_qsort(int *array, int size, int (*cmp)(int, int));
int		ft_countchr(char *str, char c);

#endif
