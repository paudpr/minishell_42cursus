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
	while(str[i] && str[i] != flag)
	{
		count++;
		i++;
	}
	return (count);
}

int size_var(char *str)
{
	int i;

	i = 1;
	if(ft_isdigit(str[i]) || str[i] == '?')
		return(1);
	if(str[i] == 0 || (str[i] != '_' && !ft_isalnum(str[i])))
		return(0);
	while(str[i])					// revisar esto esta maaaaaaaaaaaal
	{
		i++;
		if(!ft_isalnum(str[i] || str[i] != '_'))
		{
			i--;
			break ;
		}
	}
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
	return(ft_strdup(var));
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
	if(!ft_isalnum(str[i]) || str[i] != '_')
		return (ft_strdup(""));
	while(str[i])
	{
		i++;
		if(!ft_isalnum(str[i] || str[i] != '_'))
		{
			i--;
			break ;
		}
	}
	aux = ft_substr(str, 1, i);
	var = check_expansion(aux, env);
	free(aux);
	return(var);
}

char *get_quoted(char *str, t_env *env)
{
	int i;
	char flag;
	char c;
	char *aux;

	i = 1;
	flag = str[0];
	aux = ft_strdup("");
	while(str[i])
	{
		c = str[i];
		if(str[i] == flag)
			break ;
		else if(str[i] == '$' && flag == '"')
		{
			if(str[i + 1] == flag)
				aux = build_str(aux, ft_strdup(&c), 1);		//comprobar strdup que no pete
			else
				aux = build_str(aux, get_var(&str[i], env), 1);
			i += size_var(str);
		}
		else
			aux = build_str(aux, ft_strdup(&c), 1);			//comprobar strdup que no pete
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
		(void)env;
		while(aux[i])
		{
			if(aux[i] == '\'' || aux[i] == '\"')
			{
				var = build_str(var, get_quoted(&aux[i], env), 1);			//&aux[i] sustituir por quoted	string aux[i]
				i += size_quoted(&aux[i]);
			}
			// else if(aux[i] == '$' && aux[i + 1])
			// {
			// 	printf("ENTRO AQUI\n");
			// 	var = build_str(var, &aux[i], 1);			//&aux[i] sustituir por valor variable 	string aux[i]
			// 	i += size_var(&aux[i]);
			// }
			else
				var = build_str(var, ft_substr(aux, i, 1), 1);			//caracter auxx[i]
			i++;
			free(lst->content);
			lst->content = ft_strdup(var);
		}
		free(aux);
		lst = lst->next;
	}
	return (0);
}

void	main_parse(t_def *def, char *line, t_env *env)
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
	if(!parse_tokens(lst) && !parse_com(lst, env))	//errores de tokens -> todo lo que no es | < > << >> 
		printf("todo está bien \n");
		// def = parse_nodes(def, lst);		//crear nodos con argumentos correspondientes
	print_list(lst);
	free_lst(lst);
}