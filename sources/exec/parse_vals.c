#include "pruebas_bash.h"

char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void init_vals(t_cmds *vals, char **environ, t_def **def)
{
	int i;

	i = 0;
	while(environ[i])
		i++;
	vals->env = malloc(sizeof(char *) * (i + 1));
	if(vals->env == NULL)
		return ;
	i = 0;
	while(environ[i])
	{
		vals->env[i] = ft_strdup(environ[i]);
		i++;
	}
	vals->env[i] =  NULL;
	ft_bzero(vals->pipe_fd, 2);

	(void)def;
	// vals->cmds_argv = get_argv(def);
	// vals->cmds_path = get_path(vals, def);
}

char *check_valid(char *path, char *command)
{
	int i;
	char **split_path;
	char *cmd_str;
	char *cmd_path;
	char *aux;

	split_path = ft_split(path, ':');
	cmd_path = NULL;
	i = 0;
	while(split_path[i])
	{
		aux = ft_strjoin(split_path[i], "/");
		cmd_str = ft_strjoin(aux, command);
		if(access(cmd_str, F_OK) == 0)
			cmd_path = ft_strdup(aux);
		free(aux);
		free(cmd_str);
		i++;
	}
	ft_free_double(split_path);
	if(cmd_path == NULL)
	{
		access(cmd_path, F_OK);
		perror("");
	}
	return(cmd_path);
}

char **get_path(t_cmds *vals, t_def **def)
{
	int i;
	int j;
	char **split_cmd;
	char *path;
	char **cmd_path;
	t_def *copy;

	copy = *def;
	path = find_path(vals->env);
	if(path == NULL)
		print_error("No path");
	cmd_path = ft_calloc(sizeof(char *), ft_lstsize(copy) + 1);
	if(cmd_path == NULL)
		print_error("Error de memoria en get_path");
	j = 0;

	while(copy)
	{
		i = 0;
		while(i < ft_double_len(copy->argv))
		{
			if (copy->type[i] != 4)
				i++;
			else
			{
				split_cmd = ft_split(vals->cmds_argv[j], ' ');
				cmd_path[j] = check_valid(path, split_cmd[0]);
				i += ft_double_len(copy->argv);
				j++;
			}
		}
		ft_free_double(split_cmd);
		copy = copy->next;
	}
	// cmd_path[j] = NULL;
	return (cmd_path);
}

char **get_argv(t_def **def)
{
	t_def *copy;
	char **cmd_argv;
	char *aux;
	char *temp;
	int i;
	int j;

	j = 0;
	copy = *def;
	cmd_argv = ft_calloc(sizeof(char *), ft_lstsize(copy) + 1);
	while(copy)
	{
		i = 0;
		while(copy->type[i] && i < ft_double_len(copy->argv))
		{
			if(copy->type[i] != 4)
				i++;
			else if(copy->type[i] == 4)
			{
				if(!cmd_argv[j])
					cmd_argv[j] = copy->argv[i];
				else
				{
					aux = ft_strjoin(cmd_argv[j], " ");
					temp = copy->argv[i];
					cmd_argv[j] = ft_strjoin(aux, temp);
					free(aux);
					free(temp);
				}
			}
			i++;
		}
		j++;
		copy = copy->next;
	}
	cmd_argv[j] = NULL;
	return(cmd_argv);
}