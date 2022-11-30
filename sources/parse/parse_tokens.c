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

int	error_redir_tokens(t_list *lst, char flag, int type)
{
	int		i;
	int		count;
	int		len;
	char	*aux;

	count = -1;
	while (lst)
	{	
		i = -1;
		aux = ft_strdup(lst->content);
		len = ft_strlen(aux);
		while (++i < len)
		{
			if (aux[i] == flag)
				count++;
			else
			{
				free(aux);
				if (type == 1)
					count++;
				print_redir_err_tokens(count, flag);
				return (1);
			}
		}
		lst = lst->next;
		free(aux);
	}
	return (1);
}

int	parse_redir_tokens(t_list *lst)
{
	char	flag;
	char	*check;
	char	*next;
	int		len;

	len = 0;
	while (lst)
	{
		check = ft_strdup(lst->content);
		if (check[0] == '<' || check[0] == '>')
		{
			len = ft_strlen(check);
			if (len == 1)
				lst = lst->next;
			else
			{
				if (check[0] != check[1])
				{
					flag = check[1];
					free(check);
					return (error_redir_tokens(lst->next, flag, 1));
				}
				else
				{
					if (lst->next)
					{
						next = ft_strdup(lst->next->content);
						if (next[0] == '<' || next[0] == '>')
						{
							flag = next[0];
							free(next);
							free(check);
							return (error_redir_tokens(lst->next, flag, 2));
						}
						else
						{
							free(next);
							lst = lst->next;
						}
					}
					else
						lst = lst->next;
				}
			}
		}
		else
			lst = lst->next;
		free(check);
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
