#include "pruebas_bash.h"


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


	printf("INIT_VALS AQUI\n");
	// vals->cmds_path = get_path(vals, def);
	vals->cmds_argv = get_argv(def);
	printf("En init vals -> %s\n", vals->cmds_argv[0]);
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
	cmd_argv = malloc(sizeof(char *) * (ft_lstsize(*def)) + 1);
	while(copy && copy->type[i]) //aqui me puede dar error de recorrer el array por ser números
	{
		i = 0;
		printf("len -> %d\n", ft_double_len(copy->argv));
		while(copy->type[i] && i < ft_double_len(copy->argv))
		{
			if(copy->type[i] != 4)
				i++;
			else if(copy->type[i] == 4)
			{
				printf("%d\n", i);
				if(!cmd_argv[j])
					cmd_argv[j] = copy->argv[i];
				else
				{
					printf("command es tipo 4\n");
					aux = ft_strjoin(cmd_argv[j], " ");
					temp = copy->argv[i];
					printf("%s\n", aux);
					printf("%s\n", temp);
					cmd_argv[j] = ft_strjoin(aux, temp);
					free(aux);
					free(temp);
				}
				printf("--------> %s\n", cmd_argv[j]);
			}
			i++;
		}
		j++;
		copy = copy->next;
	}
	return(cmd_argv);
}



/*
char	**get_argv(t_vals *vals, char **argv, int argc)
{
	char	**cmd_argv;
	int		i;
	int		j;

	(void)vals;
	cmd_argv = malloc(sizeof(char *) * argc - 3 + 1);
	if (cmd_argv == NULL)
		print_error(0);
	i = 2;
	j = 0;
	while (argv[i] && i > 1 && i < argc - 1)
	{
		cmd_argv[j] = argv[i];
		i++;
		j++;
	}
	cmd_argv[j] = NULL;
	return (cmd_argv);
}



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

char	*check_valid(char *path, char *argv)
{
	int		i;
	char	**path_div;
	char	*aux;
	char	*str_cmd;
	char	*cmd_path;

	path_div = ft_split(path, ':');
	cmd_path = NULL;
	i = 0;
	while (path_div[i])
	{
		aux = ft_strjoin(path_div[i], "/");
		str_cmd = ft_strjoin(aux, argv);
		if (access(str_cmd, F_OK) == 0)
			cmd_path = ft_strdup(aux);
		free(aux);
		free(str_cmd);
		i++;
	}
	ft_free_double(path_div);
	if (cmd_path == NULL)
		print_error(0);
	return (cmd_path);
}

char	**get_path(t_vals *vals, int argc, char **argv)
{
	int		i;
	int		j;
	char	*path;
	char	**cmd_path;
	char	**argv_split;

	path = find_path(vals->env);
	if (path == NULL)
		print_error(0);
	cmd_path = malloc(sizeof(char *) * (argc - 3 + 1));
	if (cmd_path == NULL)
		print_error(0);
	i = 2;
	j = 0;
	while (argv[i] && i > 1 && i < argc - 1)
	{
		argv_split = ft_split(argv[i], ' ');
		cmd_path[j] = check_valid(path, argv_split[0]);
		j++;
		i++;
		ft_free_double(argv_split);
	}
	cmd_path[j] = NULL;
	return (cmd_path);
}*/