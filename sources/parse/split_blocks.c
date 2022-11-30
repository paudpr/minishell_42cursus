#include "minishell.h"

int	ignore_spaces(char *line, int i)
{
	while (i < (int)ft_strlen(line))
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
	while (i + len < (int)ft_strlen(line))
	{
		if (line[i + len] == 34 || line [i + len] == 39)
		{
			if (i + len == 0 || (i + len > 0 && line[i + len - 1] != '\\'))
			{
				flag = line[i + len];
				len++;
				while (line[i + len])
				{
					if (flag == line[i + len] && line[i + len - 1] != '\\')
					{
						len++;
						while (line[i + len])
						{
							if (line[i + len] == ' '
								|| line[i + len] == '<' || line[i + len] == '>'
								|| line[i + len] == '|')
								return (len);
							len++;
						}
					}
					len++;
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

int	check_next(char *line, int i, char flag)
{
	i++;
	(void)flag;
	if (line[i] && line[i] != '<' && line[i] != '>')
	{
		if (line[i] == ' ')
		{
			i = ignore_spaces(line + i, i);
			if (line[i] && (line[i] == '<' || line[i] == '>'))
			{
				printf("minishell: ");
				printf("syntax error near unexpected token '%c'\n", line[i]);
				return (1);
			}
		}
	}
	return (0);
}

t_list	*split_blocks(char *line)
{
	t_list	*lst;
	int		i;
	int		len;

	i = 0;
	len = 0;
	lst = ft_lstnew(ft_strdup(line));
	while (i < (int)ft_strlen(line))
	{	
		i = ignore_spaces(line, i);
		if (line[i] && (line[i] == '<' || line[i] == '>' || line[i] == '|'))
		{
			len = 1;
			if (check_next(line, i + 1, line[i]))
			{
				free_lst(lst);
				return (NULL);
			}
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
