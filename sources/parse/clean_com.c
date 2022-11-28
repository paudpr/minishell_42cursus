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
	if (i < (int)ft_strlen(str) && (ft_isdigit(str[i])
		|| str[i] == '?' || str[i] == '$' || str[i] == '#' || str[i] == '"' || str[i] == '\''))
		return (1);
	while (i < (int)ft_strlen(str) && ft_isalpha(str[i]))
		i++;
	// if (i == (int)ft_strlen(str) - 1)
	// 	i--;
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
	// free(var);
	return (ft_strdup(""));
}

char	*get_var(char *str, t_env *env)
{
	int		i;
	char	*var;
	char	*aux;

	i = 1;
	if (ft_isdigit(str[i]) || str[i] == '"' || str[i] == '\'')
		return (ft_strdup(""));
	if(str[i] == '$')
		return(ft_itoa(getpid()));
	if(str[i] == '#')
		return(ft_strdup("0"));
	// if(str[i] = '?')			// cosa de señales
	// 	return (señales);
	while (str[i] /*&& str[i] != '"' */&& ft_isalpha(str[i]))
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
				// printf("get var -> %s\n", get_var(&str[i], env));
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

void clean_com(char **str, t_env *env)
{
	int i;
	int j;
	char *var;

	j = 0;
	while(j < ft_double_len(str))
	{
		var = ft_strdup("");
		i = 0;
		while (i < (int)ft_strlen(str[j]))
		{
			// printf("bucle %d -> %c\n", i, str[j][i]);
			if (((str[j][i] == '\'' || str[j][i] == '"') && str[j][i + 1])
				&& (i == 0 || (i > 0 && str[j][i - 1] != '\\')))
			{
				// printf("-----\n");
				// printf("get quoted -> %s\n", get_quoted(&str[j][i], env));
				var = build_str(var, get_quoted(&str[j][i], env), 1);
				i += size_quoted(&str[j][i]) + 1;
			}
			else if ((str[j][i] == '"' || str[j][i] == '\'') && i == (int)ft_strlen(str[j]) - 1)
				break ;
			else if (str[j][i] == '$' && str[j][i + 1])
			{
				// printf("*****\n");
				var = build_str(var, get_var(&str[j][i], env), 1);
				i += size_var(&str[j][i]);
			}
			else
			{
				// printf("·····\n");
				var = build_str(var, ft_chrdup(str[j][i]), 1);
			}
			i++;
		}
		free(str[j]);
		// printf("var -> %s\n", var);
		str[j] = ft_strdup(var);
		free(var);
		j++;
	}
}
