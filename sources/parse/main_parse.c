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
			flag = line[i + len];
			while (line[i + len])
			{
				len++;
				if (flag == line[i + len])
					return (len + 1);
			}
		}
		else if (line[i + len] == ' ' || line[i + len] == '<'
			|| line[i + len] == '>' || line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
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
	t_list *aux;

	while (lst)
	{
		aux = lst;
		lst = lst->next;
		aux->next = NULL;
		free(aux->content);
		free(aux);
	}
}

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
	int		size;
	int		i;

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

// int	parse_redir_tokens(t_list *lst)
// {
// 	int		size;
// 	int		i;
// 	char	flag;
// 	t_list	*n_node;

// 	i = 0;
// 	flag = 0;
// 	size = ft_lstsize(lst);
// 	n_node = 0;
// 	while (lst && size > 2)
// 	{
// 		i = 0;
// 		if (!ft_stncmp(lst->content, "<", 1)
// 			|| !ft_stncmp(lst->content, ">", 1))
// 			i = 2;
// 		if (i)
// 		{
// 			flag = lst->content;
// 			if (!ft_strncmp(lst->next->content, flag, 1))
// 				n_node = lst->next->next;
// 			if (n_node && (!ft_strncmp(n_node->content, "<", 1)
// 				|| !ft_strncmp(n_node->next->content, ">", 1)))
// 				i = 3;
// 			if (n_node && (!ft_strncmp(n_node->next->content, "<", 1)
// 				|| !ft_strncmp(n_node->next->content, ">", 1)))
				
// 		}
// 	}
	

// 	return (0);
// }


int parse_redir_tokens(t_list *lst)
{
	char	flag;
	
	while(lst)
	{
		if (!ft_stncmp(lst->content, "<", 1)
			|| !ft_stncmp(lst->content, ">", 1))
		{
			flag = lst->content;
			lst = lst->next;
		}




	}


}



int	parse_tokens(t_list *lst)
{
	if (parse_pipe_tokens(lst))
		return (1);
	// if(parse_redir_tokens(lst))
	// 	return(1);
	return (0);
}

void	main_parse(t_def **def, char *line)
{
	t_list	*lst;
	t_list	*aux;

	if (!line)
		def = NULL;
	lst = split_blocks(line);
	aux = lst;
	lst = lst->next;
	aux->next = NULL;
	free(aux->content);
	free(aux);
	if(!parse_tokens(lst))			//errores de tokens | < > << >> 
		printf("lalalala\n");
		// parse_nodes(lst);		//crear nodos con argumentos correspondientes
	print_list(lst);
	free_lst(lst);

		
}
