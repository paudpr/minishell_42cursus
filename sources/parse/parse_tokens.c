#include "minishell.h"

int	parse_pipe_aux(int i)
{
	if (i == 1)
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		return (1);
	}
	else if (i == 2)
	{
		printf("minishell: syntax error near unexpected token '||'\n");
		return (1);
	}
	return (0);
}

int	parse_pipe_tokens(t_list *lst)
{
	int	size;
	int	i;

	if (!lst)
		return (0);
	size = ft_lstsize(lst) + 1;
	if (!ft_strncmp(ft_lstlast(lst)->content, "|", 1)
		|| !ft_strncmp(lst->content, "|", 1))
		return (parse_pipe_aux(1));
	while (lst && --size > 2)
	{
		i = 0;
		if (!ft_strncmp(lst->content, "|", 1)
			&& (lst->next && !ft_strncmp(lst->next->content, "|", 1)))
			i = 1;
		if (!ft_strncmp(lst->content, "|", 1)
			&& (lst->next && !ft_strncmp(lst->next->content, "|", 1))
			&& (lst->next->next
				&& !ft_strncmp(lst->next->next->content, "|", 1)))
				i = 2;
		if (parse_pipe_aux(i))
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	print_redir_err_tokens(int i, char type)
{
	int	count;

	count = 0;
	printf("minishell: syntax error near unexpected token '%c", type);
	while (count < i && count < 2)
	{
		printf("%c", type);
		count++;
	}
	printf("'\n");
}

int	error_redir_tokens(t_list **lst, char flag)
{
	int		i;
	t_list	*aux;

	aux = *lst;
	aux = aux->next;
	i = 0;
	while (aux && !ft_strncmp(aux->content, &flag, 1))
	{
		i++;
		aux = aux->next;
	}
	print_redir_err_tokens(i, flag);
	while (aux && (!ft_strncmp(aux->content, "|", 1)
			|| !ft_strncmp(aux->content, "<", 1) || !ft_strncmp(aux->content, ">", 1)))
		aux = aux->next;
	return (1);
}

int	parse_redir_tokens(t_list *lst)
{
	char	flag;
	char	*aux;
	int		i;

	i = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, "<", 1)									//si es una redirección
			|| !ft_strncmp(lst->content, ">", 1))
		{
			aux = ft_strdup(lst->content);
			flag = aux[0];
			lst = lst->next;
			if (lst && !ft_strncmp(lst->content, &flag, 1)) 					//si es un heredoc o un append
			{
				lst = lst->next;
				if (!lst)
					return (1);
				free(aux);
				aux = ft_strdup(lst->content);
				if (lst && !ft_strncmp(lst->content, &flag, 1))					//si es un fallo porque muchas redirecciones 
					return (error_redir_tokens(&lst, aux[0]));
				else if (lst && ft_strncmp(lst->content, &flag, 1)
					&& (!ft_strncmp(lst->content, "|", 1)
						|| !ft_strncmp(lst->content, "<", 1)
						|| !ft_strncmp(lst->content, ">", 1)))					//si es un fallo porque mezcla de redirecciones
					return (error_redir_tokens(&lst, aux[0]));
				else
					lst = lst->next;
			}
			else if (lst && ft_strncmp(lst->content, &flag, 1)					//si mezcla redirecciones simples
				&& (!ft_strncmp(lst->content, "|", 1)
					|| !ft_strncmp(lst->content, "<", 1)
					|| !ft_strncmp(lst->content, ">", 1)))
			{
				free(aux);
				aux = ft_strdup(lst->content);
				return (error_redir_tokens(&lst, aux[0]));
			}
			free(aux);
		}
		else
			lst = lst->next;
	}
	return (0);
}

int	parse_tokens(t_list *lst)
{
	if (parse_pipe_tokens(lst))
		return (1);
	if (parse_redir_tokens(lst))
		return (1);
	return (0);
}
