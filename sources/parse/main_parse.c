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
			if(i + len == 0 || (i + len > 0 && line[i + len - 1] != '\\'))
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

	if(!lst)
		return(0);		// revisar
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
	int count;

	count = 0;
	printf("minishell: syntax error near unexpected token '%c'", type);
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
				if(!lst)
					return(1);
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
				&& (!ft_strncmp(lst->content, "|", 1)
					|| !ft_strncmp(lst->content, "<", 1)
					|| !ft_strncmp(lst->content, ">", 1)))
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

int size_quoted(char *str)
{
	int i;
	int count;
	char flag;

	i = 1;
	count = 0;
	if(str[0] == '"' || str[0] == '\'')
		flag = str[0];
	while(str[i])
	{
		if(str[i] == flag && i != 0 && str[i - 1] == '\\')
			i++;
		else if (str[i] == flag)
			break ;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int size_var(char *str)
{
	int i;

	i = 1;
	if(ft_isdigit(str[i]) || str[i] == '?')
		return(1);
	while(str[i])					// revisar esto esta maaaaaaaaaaaal
		i++;
	if(str[i] == 0)
		i--;
	return(i);
}

char *check_expansion(char *var, t_env *env)
{
	int len;
	int aux;
	char *name_var;

	if(!var)
		return(ft_strdup(""));
	len = ft_double_len(env->env);
	while(--len >= 0)
	{
		name_var = ft_substr(env->env[len], 0, ft_strlen(var));
		aux = ft_strlen(ft_strchr(env->env[len], '=')) - ft_strlen(env->env[len]);
		if(aux < 0)
			aux *= -1;
		if(!ft_strncmp(name_var, var, ft_strlen(var)) && aux == (int)ft_strlen(var))
			return(ft_strdup(ft_strchr(env->env[len], '=') + 1));
	}
	return(ft_strdup(""));
}

char *get_var(char *str, t_env *env)
{
	int i;
	char *var;
	char *aux;

	i = 1;
	if(ft_isdigit(str[i]))
		return (ft_strdup(""));
	// if(str[i] = '?')			// cosa de señales
	// 	return (señales);
	while(str[i])
		i++;
	aux = ft_substr(str, 1, i);
	var = check_expansion(aux, env);
	free(aux);
	return(var);
}

char *get_quoted(char *str, t_env *env)
{
	int i;
	char flag;
	char *aux;

	i = 1;
	flag = str[0];
	aux = ft_strdup("");
	while(str[i])
	{
		if(str[i] == '\\' && str[++i])
			aux = build_str(aux, ft_chrdup(str[i]), 1);
		else if(str[i] == flag)
			break ;
		else if(str[i] == '$' && flag == '"')
		{
			if(str[i + 1] == flag)
				aux = build_str(aux, ft_chrdup(str[i]), 1);
			else
				aux = build_str(aux, get_var(&str[i], env), 1);
			i += size_var(aux);
		}
		else if (str[i])
			aux = build_str(aux, ft_chrdup(str[i]), 1);			//comprobar strdup que no pete
		i++;
	}
	return(aux);
}

char *build_str(char *str_1, char *str_2, int type)
{
	char *aux;

	if(type == 1)
		aux = ft_strjoin(str_1, str_2);
	else
		aux = ft_strdup("Error parsing\n");
	free(str_1);
	free(str_2);
	return(aux);
}

int check_closed_coms(char *str)
{
	int		i;
	int		num;
	char	flag;
	// char	*line;

	i = -1;
	flag = 0;
	while(str[++i])
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			if(i == 0 || (i > 0 && str[i - 1] != '\\'))
			{
				flag = str[i];
				break;
			}
		}
	}
	i = -1;
	num = 0;
	while(str[++i] && flag != 0)
	{
		if(str[i] == flag)
			num++;
		if(str[i] == flag && (i > 0 && str[i - 1] == '\\'))
			num--;
	}
	if(num % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token %c\n", flag);
		return (1);
	}
	// line = NULL;									// para que funcione como en bash y siga recogiendo hasta encontrar la comilla de cierre
	// if(num % 2 != 0)
	// 	line = get_next_line(0);
	// while(line)
	// {
	// 	free(str);
	// 	str = ft_strjoin(aux, line);
	// 	check_closed_coms(str);
	// 	// free(line);								// peta aqui
	// }
	return(0);
}

int parse_com(t_list *lst, t_env *env)
{
	int i;
	char *aux;
	char *var;

	while(lst)
	{
		var = ft_strdup("");
		i = 0;
		aux = ft_strdup(lst->content);
		if (check_closed_coms(aux))
			return (1);
		while(aux[i])
		{
			if(((aux[i] == '\'' || aux[i] == '"') && aux[i + 1])
				&& (i == 0 || (i > 0 && aux[i - 1] != '\\')))
			{
				var = build_str(var, get_quoted(&(aux[i]), env), 1);
				i += size_quoted(&aux[i]) + 1;
			}
			else if ((aux[i] == '"' || aux[i] == '\'') && i == (int)ft_strlen(aux) - 1)
				break ;
			else if(aux[i] == '$' && aux[i + 1])
			{
				var = build_str(var, get_var(&aux[i], env), 1);
				i += size_var(&aux[i]);
			}
			else
				var = build_str(var, ft_chrdup(aux[i]), 1);
			i++;
			free(lst->content);
			lst->content = ft_strdup(var);
		}
		free(var);
		free(aux);
		lst = lst->next;
	}
	return (0);
}

void	main_parse(t_def **def, char *line, t_env *env)
{
	t_def	*nodes;
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
	nodes = NULL;
	if(!parse_tokens(lst) && !parse_com(lst, env))	//errores de tokens -> todo lo que no es | < > << >> 
		nodes = parse_nodes(lst);		//crear nodos con argumentos correspondientes
		// printf("aqui entro si todo está bien\n");
	// print_list(lst);
	def = &nodes;
	free_lst(lst);
}