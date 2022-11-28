#include "minishell.h"

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