#include "minishell.h"

void	init_struct_cmds(t_env *env, t_cmds *cmds, int i)
{
	cmds->env = env;
	cmds->num = 0;
	cmds->bin = 0;
	cmds->hd = 0;
	if (i < 0)
		i = 0;
	cmds->pipe_fd = ft_calloc(sizeof(int *), i);
	cmds->fd_in = dup(STDIN_FILENO);
	cmds->fd_out = dup(STDOUT_FILENO);
	
}

char	*check_valid(char **path, char *cmd)
{
	int		i;
	char	*cmd_str;
	char	*cmd_path;
	char	*aux;

	i = 0;
	cmd_path = NULL;
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		cmd_str = ft_strjoin(aux, cmd);
		if (access(cmd_str, F_OK) == 0)
			cmd_path = ft_strdup(aux);
		free(aux);
		free(cmd_str);
		i++;
	}
	if (cmd_path == NULL)
	{
		access(cmd_path, F_OK);
	}
	return (cmd_path);
}

char	*get_path(char **path, char *argvs)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	if (path == NULL)
		return (NULL);
	cmd_path = check_valid(path, argvs);
	if (cmd_path == NULL)
		return (NULL);
	return (cmd_path);
}

int	size_cmds(t_def *def)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (def->argv[i])
	{
		if (def->type[i] == 4)
			size++;
		i++;
	}
	return (size);
}

char	**get_argv(t_def *def)
{
	int		i;
	int		j;
	int		size;
	char	**cmds;

	i = 0;
	j = 0;
	size = size_cmds(def);
	if (size == 0)
		return (NULL);
	cmds = ft_calloc(sizeof(char *), size + 1);
	if (cmds == NULL)
		return (cmds);
	while (def->argv[i])
	{
		if (def->type[i] == 4)
		{
			cmds[j] = ft_strdup(def->argv[i]);
			j++;
		}
		i++;
	}
	return (cmds);
}

char	*get_relative_path(char *cmd)
{
	char	*chr;
	char	*path;
	int		len;

	chr = ft_strrchr(cmd, '/') + 1;
	len = ft_strlen(cmd) - ft_strlen(chr);
	path = ft_substr(cmd, 0, len);
	return (path);
}

char	*get_relative_argv(char *cmd)
{
	char	*chr;

	chr = NULL;
	if (ft_strrchr(cmd, '/') != NULL)
	{
		chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
		// free(cmd);
	}
	return (chr);
}

// char	*join_argv(char *cmd, char **split)
// {
// 	char	*aux;
// 	char	*temp;
// 	int		i;

// 	i = 1;
// 	temp = cmd;
// 	while (i < ft_double_len(split))
// 	{
// 		aux = ft_strjoin(temp, " ");
// 		free(temp);
// 		temp = ft_strjoin(aux, split[i]);
// 		free(aux);
// 		free(split[i]);
// 		i++;
// 	}
// 	return (temp);
// }

void	get_argv_path(t_def *def, t_cmds *cmds)
{
	// char	**split_argv;
	char	*rel_cmd;

	cmds->cmds_argv = get_argv(def);			//aqui revisar
	// printf("denttro de get_argv_path -> %s\n", cmds->cmds_argv);
	if (cmds->cmds_argv == NULL)
	{
		cmds->cmds_path = NULL;
		return ;
	}
	// split_argv = ft_split(cmds->cmds_argv, ' ');
	if (ft_strrchr(cmds->cmds_argv[0], '/') != NULL)
	{
		cmds->cmds_path = get_relative_path(cmds->cmds_argv[0]);
		rel_cmd = get_relative_argv(cmds->cmds_argv[0]);
		// printf("comando relativo en get_argv_path -> %s\n", rel_cmd);
		free(cmds->cmds_argv[0]);														// si hay doble malloc comentar esto
		cmds->cmds_argv[0] = ft_strdup(rel_cmd);
		free(rel_cmd);
		// cmds->cmds_argv[0] = join_argv(rel_cmd, cmds->cmds_argv);					//aqui revisar
		// free(split_argv);
	}
	else
	{
		cmds->cmds_path = get_path(cmds->env->path, cmds->cmds_argv[0]);
		// ft_free_double(split_argv);
	}
}
