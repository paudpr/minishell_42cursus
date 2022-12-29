/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:29:06 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 11:29:07 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_var(char *str)
{
	int	i;

	i = 1;
	if (i < (int)ft_strlen(str) && (ft_isdigit(str[i])
			|| str[i] == '?' || str[i] == '"' || str[i] == '\''))
		return (1);
	if (str[i] == '#' || str[i] == '$' || str[i] == '_'
		|| str[i] == '-' || str[i] == '.')
		return (2);
	while (i < (int)ft_strlen(str) && ft_isalpha(str[i]))
		i++;
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
		aux = ft_strlen(ft_strchr(env->env[len], '='))
			- ft_strlen(env->env[len]);
		if (aux < 0)
			aux *= -1;
		if (!ft_strncmp(name_var, var, ft_strlen(var))
			&& aux == (int)ft_strlen(var))
		{
			free(name_var);
			return (ft_strdup(ft_strchr(env->env[len], '=') + 1));
		}
		free(name_var);
	}
	return (ft_strdup(""));
}

static char	*get_last_exec(t_env *env, char *exec)
{
	int		i;
	char	*aux;
	char	*aux_e;

	i = ft_double_len(env->env) - 1;
	while (i >= 0)
	{
		if (!ft_strncmp(env->env[i], "_=", 2))
		{
			aux = ft_strdup(env->env[i]);
			aux_e = ft_strrchr(aux, '.');
			if (ft_strrchr(aux, ' '))
				exec = ft_strdup(ft_strrchr(aux, ' ') + 1);
			else if (aux_e == NULL)
				exec = ft_strdup(ft_strrchr(aux, '/') + 1);
			else if (aux_e[1] == '/')
				exec = ft_strdup(aux_e);
			else
				exec = ft_strdup(ft_strrchr(aux, '/') + 1);
			free(aux);
			return (exec);
		}
		i--;
	}
	return (ft_strdup(""));
}

static char	*get_g_exit_status(void)
{
	char	*code;

	code = ft_itoa(g_exit_status);
	return (code);
}

char	*get_var(char *str, t_env *env)
{
	int		i;
	char	*var;
	char	*aux;

	i = 1;
	if (ft_isdigit(str[i]) || str[i] == '"' || str[i] == '\'')
		return (ft_strdup(""));
	if (str[i] == '$')
		return (ft_itoa(getpid()));
	if (str[i] == '#')
		return (ft_strdup("0"));
	if (str[i] == '-')
		return (ft_strdup("himBH"));
	if (str[i] == '_')
		return (get_last_exec(env, NULL));
	if (str[i] == '.')
		return (ft_strdup("$."));
	if (str[i] == '?')
		return (get_g_exit_status());
	while (str[i] && ft_isalpha(str[i]))
		i++;
	aux = ft_substr(str, 1, i - 1);
	var = check_expansion(aux, env);
	free(aux);
	return (var);
}
