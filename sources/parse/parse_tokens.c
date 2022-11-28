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
	int count;
	int len;
	char *aux;

	// printf("!!!!!!!!!!!!   ENTRO AQUUIIIIII\n");
	count = -1;
	while(lst)
	{	
		i = -1;
		// printf("entro %d -> %s\n", count, lst->content);
		aux = ft_strdup(lst->content);
		len = ft_strlen(aux);
		while(++i < len)
		{
			if(aux[i] == flag)
				count++;
			else
			{
				free(aux);
				if(type == 1)
					count++;
				print_redir_err_tokens(count, flag);
				return(1);
			}
		}
		lst = lst->next;
		free(aux);
	}
	return(1);
}

int parse_redir_tokens(t_list *lst)
{
	char flag;
	char *check;
	char *next;
	// char *aux;
	int len;

	// printf("PARSE_REDIR_TOKENS\n");
	// print_list(lst);
	len = 0;
	while(lst)
	{
		check = ft_strdup(lst->content);
		if (check[0] == '<' || check[0] == '>')				// si es una redirección
		{
			len = ft_strlen(check);
			if(len == 1)
				lst = lst->next;							// redir simple
			else											// si es un heredoc o un append
			{
				if (check[0] != check[1])					// si mezcla distinta redirecciones
				{
					flag = check[1];
					free(check);
					return (error_redir_tokens(lst->next, flag, 1));
				}
				else										// comprueba si hay redirecciones de más
				{
					if(lst->next)
					{
						next = ft_strdup(lst->next->content);
						if (next[0] == '<' || next[0] == '>')
						{
							flag = next[0];
							free(next);
							free(check);
							return(error_redir_tokens(lst->next, flag, 2));
						}
						else								// hd o append correcto
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

// int	parse_redir_tokens(t_list *lst)
// {
// 	char	flag;
// 	char	*aux;
// 	int		i;

// 	i = 0;

// 	while (lst)
// 	{
// 		if (!ft_strncmp(lst->content, "<", 1)									//si es una redirección
// 			|| !ft_strncmp(lst->content, ">", 1))
// 		{
// 			printf("1-> %s\n", lst->content);
// 			aux = ft_strdup(lst->content);
// 			flag = aux[0];
// 			lst = lst->next;
// 			printf("2-> %s\n", lst->content);
// 			if (lst && !ft_strncmp(lst->content, &flag, 1)) 					//si es un heredoc o un append
// 			{
// 				printf("AAAAAAAAAAAAA\n");
// 				lst = lst->next;
// 				if (!lst)
// 					return (1);
// 				free(aux);
// 				aux = ft_strdup(lst->content);
// 				if (lst && !ft_strncmp(lst->content, &flag, 1))					//si es un fallo porque muchas redirecciones 
// 				{
// 					printf("11111\n");
// 					return (error_redir_tokens(&lst, aux[0]));
// 				}
// 				else if (lst && ft_strncmp(lst->content, &flag, 1)
// 					&& (!ft_strncmp(lst->content, "|", 1)
// 						|| !ft_strncmp(lst->content, "<", 1)
// 						|| !ft_strncmp(lst->content, ">", 1)))					//si es un fallo porque mezcla redirecciones
// 						{
// 							printf("222222\n");
// 							return (error_redir_tokens(&lst, aux[0]));
// 						}
// 				else
// 				{
// 					printf("333333\n");
// 					lst = lst->next;
// 				}
// 			}
// 			else if (lst && ft_strncmp(lst->content, &flag, 1)					//si mezcla redirecciones simples
// 				&& (!ft_strncmp(lst->content, "|", 1)
// 					|| !ft_strncmp(lst->content, "<", 1)
// 					|| !ft_strncmp(lst->content, ">", 1)))
// 			{
// 				printf("BBBBBBBBBBBBB\n");
// 				free(aux);
// 				aux = ft_strdup(lst->content);
// 				return (error_redir_tokens(&lst, aux[0]));
// 			}
// 			free(aux);
// 		}
// 		else
// 			lst = lst->next;
// 	}
// 	return (0);
// }

int	parse_tokens(t_list *lst)
{
	if (parse_pipe_tokens(lst))
		return (1);
	if (parse_redir_tokens(lst))
		return (1);
	return (0);
}
