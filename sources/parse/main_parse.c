#include "minishell.h"

int	ignore_spaces(char *line, int i)
{
	while (line[i])
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
	while (line[i + len])
	{
		if (line[i + len] == 34 || line [i + len] == 39)
		{
			if (i + len == 0 || (i + len > 0 && line[i + len - 1] != '\\'))
			{
				flag = line[i + len];
				while (line[i + len])
				{
					len++;
					if (flag == line[i + len] && line[i + len - 1] != '\\')
						return (len + 1);
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

int	check_next(char *line, int i)
{
	i++;
	if (line[i] && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == ' ')
		{
			i = ignore_spaces(line, i);
			if (line[i] && (line[i] == '<' || line[i] == '>'))
			{
				printf("minishell: syntax error near unexpected token `%c`\n", line[i]);
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
	while (line[i])
	{	
		i = ignore_spaces(line, i);
		if ((line[i] == '<' || line[i] == '>' || line[i] == '|') && line[i])
		{
			len = 1;
			if (check_next(line, i))
				return (lst);
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

void	main_parse(t_def **def, char *line, t_env *env)
{
	t_list	*lst;
	t_list	*aux;

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
	if (!parse_tokens(lst) && !parse_com(lst, env))
		*def = parse_nodes(lst);
		// printf("aqui entro si todo está bien\n");
	// // print_list(lst);
	free_lst(lst);
	// (void)env;
}