#include "minishell.h"

static char	get_flag_com(char *str)
{
	int		i;
	char	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '"' | str[i] == '\'')
		{
			if (i == 0 || (i > 0 && str[i - 1] == '\\'))
			{
				flag = str[i];
				break ;
			}
		}
	}
	return (flag);
}

int	check_closed_coms(char *str)
{
	int		i;
	int		num;
	char	flag;

	flag = get_flag_com(str);
	i = -1;
	num = 0;
	while (str[++i] && flag != 0)
	{
		if (str[i] == flag)
			num++;
		if (str[i] == flag && (i > 0 && str[i - 1] == '\\'))
			num--;
	}
	// if(num % 2 != 0)
		// wait_close_coms(str, num, flag);
	if (num % 2 != 0)
	{
		printf("minishell: syntax error near unexpected token '%c'\n", flag);
		g_exit_status = 258;
		free(str);
		return (1);
	}
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
