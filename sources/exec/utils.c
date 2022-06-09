
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
	if (!def)
		return (0);
	while (def->next)
	{
		def = def->next;
		i++;
	}
	return (i);
}

void free_list(t_def **def)
{
	int i;
	t_def *copy;
	
	i = mini_lstsize(*def);
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
	free(vals->cmds_argv);
	free(vals->cmds_path);
}

// void	printMat(t_cmds *cmds)
// {
// 	printf("entre\n");
// 	for (int i = 0; i < cmds->num; i++)
// 	{
// 		printf("cmd[i]: %d\n", cmds->pipe_fd[i][0]);
// 	}
	
// }

void free_pipe(t_cmds *cmds)
{
	while(cmds->num)
	{
		free(cmds->pipe_fd[cmds->num - 1]);
		cmds->num--;
	}
	free(cmds->pipe_fd);
	system("leaks -q minishell");
}
