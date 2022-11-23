#include "minishell.h"


// str es lst->content por cada uno de las separaciones
void clean_com(char **str, t_env *env)
{
	int i;
	int j;
	char *var;

	j = 0;
	// printf("----- ----- ----- -----\n");
	// print_double(str);
	// printf("%d\n", ft_double_len(str));
	// printf("····· ····· ····· ·····\n");
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
				// printf("%s\t%s\t%c\n", var, str[j], str[j][i]);
				// printf("get_quoted -> %s\n", get_quoted(ft_chrdup(str[j][i]), env));
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
				// printf("%c - %d \n", str[j][i], str[j][i]);
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
