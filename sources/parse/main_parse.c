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

void	print_redir_err_tokens(int i, char type)
{
	int count;

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
	int i;
	t_list	*aux;

	aux = *lst;
	aux = aux->next;
	i = 0;
	while(aux && !ft_strncmp(aux->content, &flag, 1))
	{
		i++;
		aux = aux->next;
	}
	print_redir_err_tokens(i, flag);
	while(aux && (!ft_strncmp(aux->content, "|", 1)
		|| !ft_strncmp(aux->content, "<", 1) || !ft_strncmp(aux->content, ">", 1)))
		aux = aux->next;
	return(1);
}

int parse_redir_tokens(t_list *lst)
{
	char	flag;
	char *aux;
	int i;
	
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
				free(aux);
				aux = ft_strdup(lst->content);
				if (lst && !ft_strncmp(lst->content, &flag, 1))					//si es un fallo porque muchas redirecciones 
					return(error_redir_tokens(&lst, aux[0]));
				else if (lst && ft_strncmp(lst->content, &flag, 1)
					&& (!ft_strncmp(lst->content, "|", 1)
						|| !ft_strncmp(lst->content, "<", 1)
						|| !ft_strncmp(lst->content, ">", 1)))					//si es un fallo porque mezcla de redirecciones
					return(error_redir_tokens(&lst, aux[0]));
				else
					lst = lst->next;
			}
			else if(lst && ft_strncmp(lst->content, &flag, 1)					//si mezcla redirecciones simples
				&& (!ft_strncmp(lst->next->content, "|", 1)	
					|| !ft_strncmp(lst->next->content, "<", 1)
					|| ft_strncmp(lst->next->content, ">", 1)))
			{
				free(aux);
				aux = ft_strdup(lst->content);
				return(error_redir_tokens(&lst, aux[0]));
			}
			free(aux);
		}
		else
			lst = lst->next;
	}
	return(0);
}

void parse_var(t_list *lst)
{
	// char aux;
	while(lst)
	{
		// aux = ft_strdup(lst->content);
		// if()
		lst = lst->next;
	}
}

// t_def	*parse_nodes(t_def *def, t_list *lst)
// {
// 	t_def *nodes;

// 	(void)def;
// 	nodes = NULL;
// 	parse_var(lst);
// 	(void)lst;




// 	return (nodes);
// }

int	parse_tokens(t_list *lst)
{
	if (parse_pipe_tokens(lst))
		return (1);
	if(parse_redir_tokens(lst))
		return(1);
	return (0);
}

int parse_com(t_list *lst)
{
	char *aux;
	char flag;

	while(lst)
	{
		aux = ft_strdup(lst->content);
		if(aux[0] == '\'' || aux[0] == '"')
		{
			flag = aux[0];
			if(aux[ft_strlen(aux) - 1] != flag)
			{
				printf("minishell: syntax error near unexpected token %c\n", flag);
				// realmente lee normal si no hay comillas. si existen comillas, lee desde la primera comilla
				// no olvidar que si hay un \comilla, ese caracter lo lee normal 
				//poner readline hasta que me metan el mismo caracter
				free(aux);
				return(1);
			}
		}
		free(aux);
		lst = lst->next;
	}
	return(0);
}

void	main_parse(t_def *def, char *line)
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
	if(!parse_tokens(lst) && !parse_com(lst))	//errores de tokens -> todo lo que no es | < > << >> 
		printf("todo está bien \n");
		// def = parse_nodes(def, lst);		//crear nodos con argumentos correspondientes
	print_list(lst);
	free_lst(lst);

		
}