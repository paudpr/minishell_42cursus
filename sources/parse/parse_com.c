#include "minishell.h"


int	size_quoted(char *str)
{
	int		i;
	int		count;
	char	flag;

	i = 1;
	count = 0;
	if (str[0] == '"' || str[0] == '\'')
		flag = str[0];
	while (str[i])
	{
		if (str[i] == flag && i != 0 && str[i - 1] == '\\')
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

int	size_var(char *str)
{
	int	i;

	i = 1;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while (str[i])					// revisar esto esta maaaaaaaaaaaal
		i++;
	if (str[i] == 0)
		i--;
	return (i);
}

char	*check_expansion(char *var, t_env *env)
{
	int		len;
	int		aux;
	char	*name_var;

	if (!var)
		return (ft_strdup(""));
	len = ft_double_len(env->env);
	while (--len >= 0)
	{
		name_var = ft_substr(env->env[len], 0, ft_strlen(var));
		aux = ft_strlen(ft_strchr(env->env[len], '=')) - ft_strlen(env->env[len]);
		if (aux < 0)
			aux *= -1;
		if (!ft_strncmp(name_var, var, ft_strlen(var)) && aux == (int)ft_strlen(var))
			return (ft_strdup(ft_strchr(env->env[len], '=') + 1));
	}
	return (ft_strdup(""));
}

char	*get_var(char *str, t_env *env)
{
	int		i;
	char	*var;
	char	*aux;

	i = 1;
	if (ft_isdigit(str[i]))
		return (ft_strdup(""));
	// if(str[i] = '?')			// cosa de señales
	// 	return (señales);
	while (str[i])
		i++;
	aux = ft_substr(str, 1, i);
	var = check_expansion(aux, env);
	free(aux);
	return (var);
}

char	*get_quoted(char *str, t_env *env)
{
	int		i;
	char	flag;
	char	*aux;

	i = 1;
	flag = str[0];
	aux = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\\' && str[++i])
			aux = build_str(aux, ft_chrdup(str[i]), 1);
		else if (str[i] == flag)
			break ;
		else if (str[i] == '$' && flag == '"')
		{
			if (str[i + 1] == flag)
				aux = build_str(aux, ft_chrdup(str[i]), 1);
			else
				aux = build_str(aux, get_var(&str[i], env), 1);
			i += size_var(aux);
		}
		else if (str[i])
			aux = build_str(aux, ft_chrdup(str[i]), 1);			//comprobar strdup que no pete
		i++;
	}
	return (aux);
}

char	*build_str(char *str_1, char *str_2, int type)
{
	char	*aux;

	if (type == 1)
		aux = ft_strjoin(str_1, str_2);
	else
		aux = ft_strdup("Error parsing\n");
	free(str_1);
	free(str_2);
	return (aux);
}

int	check_closed_coms(char *str)
{
	int		i;
	int		num;
	char	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if(i == 0 || (i > 0 && str[i - 1] != '\\'))
			{
				flag = str[i];
				break ;
			}
		}
	}
	i = -1;
	num = 0;
	while (str[++i] && flag != 0)
	{
		if (str[i] == flag)
			num++;
		if (str[i] == flag && (i > 0 && str[i - 1] == '\\'))
			num--;
	}
	if (num % 2 != 0)
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
	return (0);
}

int	parse_com(t_list *lst, t_env *env)
{
	int		i;
	char	*aux;
	char	*var;

	while (lst)
	{
		var = ft_strdup("");
		i = 0;
		aux = ft_strdup(lst->content);
		if (check_closed_coms(aux))
			return (1);
		while (aux[i])
		{
			if (((aux[i] == '\'' || aux[i] == '"') && aux[i + 1])
				&& (i == 0 || (i > 0 && aux[i - 1] != '\\')))
			{
				var = build_str(var, get_quoted(&(aux[i]), env), 1);
				i += size_quoted(&aux[i]) + 1;
			}
			else if ((aux[i] == '"' || aux[i] == '\'') && i == (int)ft_strlen(aux) - 1)
				break ;
			else if (aux[i] == '$' && aux[i + 1])
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
