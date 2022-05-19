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

typedef struct s_cmds
{
	char	**env;
	char	**cmds_path;
	char	**cmds_argv;
	int		pipe_fd[2];
	int		num;
}	t_cmds;


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
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
int ft_double_len(char **str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char **get_path(t_cmds *vals, t_def **def);
void ft_free_double(char **tab);
void	*ft_calloc(size_t count, size_t size);


void init_vals(t_cmds *vals, char **environ, t_def **def);
char **get_argv(t_def **def);



#endif
