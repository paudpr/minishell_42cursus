/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:28:48 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/29 11:28:49 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*get_quoted(char *str, t_env *env, int i, char flag)
{
	char	*aux;

	aux = ft_strdup("");
	while (i < (int)ft_strlen(str))
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
			{
				aux = build_str(aux, get_var(&str[i], env), 1);
			}
			i += size_var(&str[i + 1]);
		}
		else if (str[i])
			aux = build_str(aux, ft_chrdup(str[i]), 1);
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
	{
		aux = ft_strdup("Error parsing\n");
		g_exit_status = 258;
	}
	free(str_1);
	free(str_2);
	return (aux);
}

char	*clean_com_norm(int j, char **str, t_env *env, int i)
{
	char	*var;

	var = ft_strdup("");
	while (i < (int)ft_strlen(str[j]))
	{
		if (((str[j][i] == '\'' || str[j][i] == '"') && str[j][i + 1])
			&& (i == 0 || (i > 0 && str[j][i - 1] != '\\')))
		{
			var = build_str(var, get_quoted(&str[j][i], env, 1, str[j][i]), 1);
			i += size_quoted(&str[j][i]) + 1;
		}
		else if ((str[j][i] == '"' || str[j][i] == '\'')
				&& i == (int)ft_strlen(str[j]) - 1)
			break ;
		else if (str[j][i] == '$' && str[j][i + 1])
		{
			var = build_str(var, get_var(&str[j][i], env), 1);
			i += size_var(&str[j][i]) - 1;
		}
		else
			var = build_str(var, ft_chrdup(str[j][i]), 1);
		i++;
	}
	return (var);
}

void	clean_com(char **str, t_env *env)
{
	int		j;
	char	*var;

	j = 0;
	while (j < ft_double_len(str))
	{
		var = clean_com_norm(j, str, env, 0);
		free(str[j]);
		if (var[0] != 0)
			str[j] = ft_strdup(var);
		else
			str[j] = NULL;
		free(var);
		j++;
	}
}
