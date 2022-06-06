
#include "minishell.h"

void print_error(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
}

t_def	*ft_lstnew(void *content, int *array)
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

void	ft_lstadd_back(t_def **lst, t_def *new)
{
	t_def	*p;

	if (!*lst)
		*lst = new;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = new;
	}
}

t_def	*ft_lstlast(t_def *lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

int	ft_lstsize(t_def *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}


int ft_double_len(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}



void free_list(t_def **def)
{
	int i;
	t_def *copy;
	
	i = ft_lstsize(*def);
	while(i)
	{
		ft_free_double((*def)->argv);
		free((*def)->type);
		copy = *def;
		*def = (*def)->next;
		free(copy);
		i--;
	}	
}

void free_env(t_env *env)
{
	ft_free_double(env->path);
	ft_free_double(env->env);
	free(env);
}

void free_struct(t_cmds *vals)
{
	// free_env(vals->env);
	// ft_free_double(vals->cmds_path);
	// printf("%p    %s\n", vals->cmds_argv, vals->cmds_argv);
	// printf("%p    %s\n", vals->cmds_path, vals->cmds_path);
	free(vals->cmds_argv);
	free(vals->cmds_path);
}

void ft_free_double(char **str)
{
	int i;

	i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void free_pipe(t_cmds *cmds)
{
	while(cmds->num)
	{
		free(cmds->pipe_fd[cmds->num - 1]);
		cmds->num--;
	}
	free(cmds->pipe_fd);
}