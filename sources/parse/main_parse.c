#include "minishell.h"

int	ignore_spaces(char *line, int i)
{
	while (i < (int)ft_strlen(line))
	{
		if (line[i] != ' ')
			break ;
		i++;
	}
	return (i);
}

int	len_block(char *line, int i)
{
	int		len;
	char	flag;

	len = 0;
	while (/*line[i + len]*/i + len < (int)ft_strlen(line))
	{
		if (line[i + len] == 34 || line [i + len] == 39)
		{
			if (i + len == 0 || (i + len > 0 && line[i + len - 1] != '\\'))
			{
				flag = line[i + len];
				len++;
				while (line[i + len])
				{
					if(flag == line[i + len] && line[i + len - 1] != '\\')
					{
						len++;
						while(line[i + len])
						{
							if(line[i + len] == ' '
							|| line[i + len] == '<' || line[i + len] == '>'
							|| line[i + len] == '|')
								return(len);
							len++;
						}
					}
					len++;
				}
			}
		}
		else if (line[i + len] == ' ' || line[i + len] == '<'
			|| line[i + len] == '>' || line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

int	check_next(char *line, int i, char flag)
{
	// int count;
	// int j;

	// j = -1;
	// count = 1;
// 	if (line[i] && line[i] != '<' && line[i] != '>')
// 	{
// 		if (line[i] == ' ')
// 		{
// 			i = ignore_spaces(line + i, i);
// 			if (line[i] && (line[i] == '<' || line[i] == '>'))
// 			{
// 				while(line[i] && line[i] == flag)
// 				{
// 					count++;
// 					i++;
// 				}
// 				printf("count -> %d\n", count);
// 				if(count == 1)
// 					print_redir_err_tokens(1, line[i]);
// 				else if(count == 1)
// 				{
// 				printf("HE LLEGADO AQI\n");
// 					if(line[i+count] && flag != line[i + count - 1])
// 						printf("minishell: syntax error near unexpected token '%c%c'\n", flag, line[i + count]);
// 				}
// 				else
// 					print_redir_err_tokens(count + 1, flag);
// 				printf("minishell: syntax error near unexpected token '%c'\n", line[i]);
// 				return (1);
// 			}
// 		}
// 	}
	i++;
	(void)flag;
	if (line[i] && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == ' ')
		{
			i = ignore_spaces(line + i, i);
			if (line[i] && (line[i] == '<' || line[i] == '>'))
			{
				printf("minishell: syntax error near unexpected token '%c'\n", line[i]);
				return (1);
			}
		}
	}
	return (0);
}

t_list	*split_blocks(char *line)
{
	t_list	*lst;
	int		i;
	int		len;

	i = 0;
	len = 0;
	lst = ft_lstnew(ft_strdup(line));
	while (/*line[i]*/i < (int)ft_strlen(line))
	{	
		i = ignore_spaces(line, i);
		if (line[i] && (line[i] == '<' || line[i] == '>' || line[i] == '|'))
		{
			len = 1;
			// printf("--------> %c    %c    %d\n", line[i], line[i + 1], i);
			if (check_next(line, i + 1, line[i]))
			{
				free_lst(lst);
				return (NULL);
			}
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, i, len)));
			i += len;
		}
		else if (line[i])
		{
			len = len_block(line, i);
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(line, i, len)));
			i += len;
		}
	}
	return (lst);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

void	free_lst(t_list *lst)
{
	t_list	*aux;

	while (lst)
	{
		aux = lst;
		lst = lst->next;
		aux->next = NULL;
		free(aux->content);
		free(aux);
	}
}

int	clean_redir(t_list *lst)
{
	char	*tmp;
	t_list	*aux;

	aux = NULL;
	// print_list(lst);
	while (lst)
	{
		if (!ft_strncmp(lst->content, "<", 1)
			|| !ft_strncmp(lst->content, ">", 1))
		{
			if (!lst->next)
			{
				printf("minishell: syntax error near unexpected token 'newline'\n");
				return (1);
			}
			if (!ft_strncmp(lst->next->content, "<", 1)
				|| !ft_strncmp(lst->next->content, ">", 1))
			{
				tmp = ft_strdup(lst->content);
				free(lst->content);
				lst->content = ft_strjoin(tmp, lst->next->content);
				free(tmp);
				aux = lst->next;
				lst->next = lst->next->next;
				free(aux->content);
				free(aux);
				if (!lst->next)
				{
					printf("minishell: syntax error near unexpected token 'newline'\n");
					return (1);
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}

void	main_parse(t_def **def, char *line, t_env *env)
{
	t_list	*lst;
	t_list	*aux;

	// printf("Line   %s\n", line);
	if (!line)
		def = NULL;
	lst = split_blocks(line);
	if (lst)
	{
		aux = lst;
		lst = lst->next;
		aux->next = NULL;
		free(aux->content);
		free(aux);
	}
	if(clean_redir(lst))
	{
		free_lst(lst);
		return ;
	}
	// print_list(lst);
	// printf("%d - %d - %p\n", parse_tokens(lst), parse_tokens(lst), def);
	if (!parse_tokens(lst) && !parse_com(lst))
		*def = parse_nodes(lst, env);
		// printf("aqui entro si todo está bien\n");
	// (void)env;
	// print_nodes(*def);
	free_lst(lst);
}