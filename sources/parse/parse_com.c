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
	if (i < (int)ft_strlen(str) && (ft_isdigit(str[i]) || str[i] == '?' || str[i] == '$'))
		return (1);
	while (i < (int)ft_strlen(str))					// revisar esto esta maaaaaaaaaaaal
		i++;
	if (i == (int)ft_strlen(str) - 1)
		i--;
	return (i);
}

char	*check_expansion(char *var, t_env *env)
{
	int		len;
	int		aux;
	char	*name_var;

	// printf("var -> %p\t%s\n", &var, var);
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
		{
			free(name_var);
			return (ft_strdup(ft_strchr(env->env[len], '=') + 1));
		}
		free(name_var);
	}
	free(var);
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
	if(str[i] == '$')
		return(ft_itoa(getpid()));
	// if(str[i] = '?')			// cosa de señales
	// 	return (señales);
	while (str[i] && str[i] != '"')
		i++;
	aux = ft_substr(str, 1, i - 1);
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
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '\\' && str[++i])				// ignora la contrabarra si la hay
			aux = build_str(aux, ft_chrdup(str[i]), 1);
		else if (str[i] == flag)					// cierra comilla
			break ;
		else if (str[i] == '$' && flag == '"')		// gestiona $ y expansión
		{
			if (str[i + 1] == flag)
				aux = build_str(aux, ft_chrdup(str[i]), 1);
			else
			{
				aux = build_str(aux, get_var(&str[i], env), 1);
			}
			i += size_var(&str[i + 1]);
		}
		else if (str[i])							// continua por caracter
			aux = build_str(aux, ft_chrdup(str[i]), 1);
		i++;
	}
	return (aux);
}

char	*build_str(char *str_1, char *str_2, int type)
{
	char	*aux;

	// printf("%s\t-\t%s\n", str_1, str_2);
	// printf("%d\t-\t%d\n", str_1[0], str_2[0]);
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
		printf("minishell: syntax error near unexpected token '%c'\n", flag);
		free(str);
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

int	parse_com(t_list *lst)
{
	char	*aux;

	while (lst)
	{
		aux = ft_strdup(lst->content);
		if (check_closed_coms(aux))
			return (1);
		free(aux);
		lst = lst->next;
	}
	return (0);
}