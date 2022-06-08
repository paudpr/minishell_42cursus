
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

int ft_double_len(char **str)
{
	int i;

	i = 0;
	if(!str)
		return (0);
	while(str[i] != NULL)
		i++;
	return(i);
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























// static void	free_env(t_env **env_lst)
// {
// 	lstclear_env(&(*env_lst)->env, free);
// 	lstclear_env(&(*env_lst)->ex_env, free);
// 	free(*env_lst);
// }

// int	main(void)
// {
// 	char	*argv;
// 	t_lst	*nodes;
// 	t_env	*env_lst;

// 	g_output_code = 0;
// 	env_lst = init_env();
// 	while (1)
// 	{
// 		signal_main();
// 		argv = readline(BLUE"Mini"YELLOW"Shell"RESET" ");
// 		if (argv == NULL)
// 		{
// 			printf("exit\n");
// 			exit(EXIT_SUCCESS);
// 		}
// 		add_history(argv);
// 		nodes = create_nodes_rework(argv, env_lst->env);
// 		if (nodes_check_error(nodes))
// 			exec(nodes, &env_lst);
// 		free_nodes(nodes, argv);
// 	}
// 	s_mirage(env_lst->ex_env);
// 	free_env(&env_lst);
// 	return (0);
// }