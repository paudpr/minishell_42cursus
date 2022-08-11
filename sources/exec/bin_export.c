#include "minishell.h"

void	print_double_export(char **str)
{
	int	i;
	int	j;
	int	len;

	if (str == NULL)
		return ;
	i = 0;
	len = ft_double_len(str);
	while (i < len)
	{
		j = -1;
		printf("declare -x ");
		while (str[i][++j] != '=' && str[i][j])
			printf("%c", str[i][j]);
		if (ft_strchr(str[i], '=') != 0)
		{
			printf("=\"");
			printf("%s", ft_strchr(str[i], '=') + 1);
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	check_valid_var(t_cmds *cmds, int i)
{
	int	j;

	if (ft_isalpha(cmds->cmds_argv[i][0]) != 1)
	{
		perror("minishell: export: not a valid identifier");
		return (0);
	}
	j = 1;
	while (j < (int)ft_strlen(cmds->cmds_argv[i]) && cmds->cmds_argv[i][j] != '=')
	{
		if (ft_isalnum(cmds->cmds_argv[i][j]) != 1)
		{
			perror("minishell: export: not a valid identifier");
			return (0);
		}
		j++;
	}
	return (1);
}

char	*clean_var(char *new)
{
	int		i;
	int		length;
	char	*var;
	char	aux;

	var = NULL;
	length = ft_strlen(new);
	if (ft_strchr(new, '=') == 0)
		return (ft_strdup(new));				 //REVISAR
	else
	{
		aux = *(ft_strchr(new, '=') + 1);
		if (aux == 34 || aux == 39)
			length = length - 2;
		var = ft_calloc(length + 2, sizeof(char));
		i = -1;
		while (++i < length)
		{
			if (new[i] == 34 || new[i] == 39)
				i++;
			var[i] = new[i];
		}
	}
	return (var);
}

void	add_new_var(t_cmds *cmds, int i, int len)
{
	int		j;
	char	**new;

	j = -1;
	new = ft_calloc(len + 2, sizeof(char *));
	if (new == NULL)
		exit(0);
	while (++j < len)			//volver a probar esta mierda a ver si se estan guardando todos o si hay que hacer len - 1 para que no copie el nulo  y  luego asignar a mano el nulo
		new[j] = ft_strdup(cmds->env->env[j]);
	new[j] = clean_var(cmds->cmds_argv[i]);
	ft_free_double(cmds->env->env);
	cmds->env->env = new;
}

void	transform_var(t_cmds *cmds, int i, int len)
{
	int		j;
	int		length;
	char	*other;

	other = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(other);
	j = 0;
	while (j < len)
	{
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0)
		{
			free(cmds->env->env[j]);
			cmds->env->env[j] = clean_var(cmds->cmds_argv[i]);
		}
		j++;
	}
}

void	add_var(t_cmds *cmds, int i)
{
	int	len;

	len = ft_double_len(cmds->env->env);
	if (check_valid_var(cmds, i) != 0)
	{
		if (var_exists(cmds, i, len) == 1)
			transform_var(cmds, i, len);
		else
			add_new_var(cmds, i, len);
	}
}

void	do_export(t_cmds *cmds)
{	
	int		i;
	int		len;
	char	**copy;

	i = 1;
	copy = NULL;
	len = ft_double_len(cmds->cmds_argv);
	if (len == 1)
	{
		copy = sort_double(cmds->env->env);
		print_double_export(copy);
		ft_free_double(copy);
	}
	else
	{
		while (i < len)
		{
			add_var(cmds, i);
			i++;
		}
	}
}
