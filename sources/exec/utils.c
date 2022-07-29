#include "minishell.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

t_def	*mini_lstnew(void *content, int *array)
{
	t_def	*a;

	a = malloc(sizeof(t_def));
	if (a == 0)
		return (0);
	a->argv = ft_split(content, ' ');
	a->type = array;
	a->next = NULL;
	return (a);
}

void	mini_lstadd_back(t_def **lst, t_def *new)
{
	t_def	*p;

	if (!*lst)
		*lst = new;
	else
	{
		p = mini_lstlast(*lst);
		p -> next = new;
	}
}

t_def	*mini_lstlast(t_def *lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

int	mini_lstsize(t_def *def)
{
	int	i;

	i = 1;
	if (def == NULL)
		return (0);
	while (def->next != NULL)
	{
		def = def->next;
		i++;
	}
	return (i);
}

void	free_list(t_def **def)
{
	int		i;
	t_def	*copy;

	i = mini_lstsize(*def);
	while (i)
	{
		ft_free_double((*def)->argv);
		free((*def)->type);
		copy = *def;
		*def = (*def)->next;
		free(copy);
		i--;
	}	
}

void	free_env(t_env *env)
{
	if (env->shlvl != 1)
		ft_free_double(env->path);
	ft_free_double(env->env);
	free(env);
}

void	free_struct(t_cmds *vals)
{
	if (vals->cmds_argv != NULL)
		ft_free_double(vals->cmds_argv);
	if (vals->cmds_path != 0)
		free(vals->cmds_path);
}

void	free_pipe(t_cmds *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(cmds->pipe_fd[i]);
		i++;
	}
	free(cmds->pipe_fd);
}

void	wait_process(t_def *def)
{
	int	i;
	int	*s;

	s = NULL;
	i = mini_lstsize(def);
	while (i)
	{
		waitpid(-1, s, 0);
		i--;
	}
}

void	print_double(char **str)
{
	int i;

	if (str == NULL)
		return ;
	i = 0;
	while(str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

char **sort_double(char **str)
{
	int i;
	int j;
	int len;
	int index;
	char **sorted;

	len = ft_double_len(str);
	sorted = ft_calloc(sizeof(char *), len + 1);
	i = 0;
	while(i < len)
	{
		j = 0;
		index = 0;
		while(j < len)
		{
			if(ft_strncmp(str[i], str[j], ft_strlen(str[i])) > 0)
				index++;
			j++;
		}
		sorted[index] = ft_strdup(str[i]);
		i++;
	}
	return(sorted);
}
