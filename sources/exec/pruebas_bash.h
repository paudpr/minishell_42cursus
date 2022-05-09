#ifndef PRUEBAS_BASH_H
# define PRUEBAS_BASH_H

# define T_HD	0
# define T_RIN	1
# define T_ROUT	2
# define T_APP	3
# define T_CMD	4
# define T_ARG	5
# define T_BIN	6

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_def
{
	char **argv;
	int *type;
	struct s_def *next;
}	t_def;


void print_error(char *str);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_count_strings(char const *s, char c);
size_t	ft_count_chrs(char const *s, char c);
void	ft_free_tab(char **tab, size_t n);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
t_def	*ft_lstnew(void *content, int *array);
void	ft_lstadd_back(t_def **lst, t_def *new);
t_def	*ft_lstlast(t_def *lst);
int	ft_lstsize(t_def *lst);




#endif
