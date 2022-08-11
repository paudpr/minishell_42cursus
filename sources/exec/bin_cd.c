#include "minishell.h"

void	change_var(t_env *env, char *var, char *new)
{
	int		i;
	char	*copy;

	i = 0;
	while (i < ft_double_len(env->env))
	{
		if (ft_strncmp(env->env[i], var, ft_strlen(var)) == 0)
		{
			copy = ft_strjoin(var, new);
			free(env->env[i]);
			env->env[i] = ft_strdup(copy);
			free(copy);
			return ;
		}
		i++;
	}
}

//va al home. cd
void	cd_home_dir(t_cmds *cmds)	// tener en cuenta que pasa si no existe $HOME
{
	int		i;
	char	*home;
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	i = 0;
	home = NULL;
	while (i < ft_double_len(cmds->env->env))
	{
		if (ft_strncmp(cmds->env->env[i], "HOME=", ft_strlen("HOME=")) == 0)
			home = ft_strchr(cmds->env->env[i], '/');
		i++;
	}
	if (home != NULL)
	{
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(home);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
	}
	else
		printf("minishell: cd: HOME not set\n");
}

//va un directorio hacia atrás. cd ..
void	cd_back_dir(t_cmds *cmds)
{
	char	dir[PATH_MAX];
	char	*last;
	char	*new_dir;

	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "OLDPWD=", dir);
	last = ft_strrchr(dir, '/') + 1;
	new_dir = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(last));
	chdir(new_dir);
	change_var(cmds->env, "PWD=", new_dir);
	free(new_dir);
}

// norminette
void	do_cd_return_dir(t_cmds *cmds, char *new) // comprobar
{
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "OLDPWD=", dir);
	chdir(ft_strchr(new, '/'));
	free(new);
	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "PWD=", dir);
	printf("%s\n", dir);
}

//vuelve al ultimo directorio donde ha estado. cd -
void	cd_return_dir(t_cmds *cmds)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = NULL;
	while (++i < ft_double_len(cmds->env->env))
	{
		if (ft_strncmp(cmds->env->env[i], "PWD=", ft_strlen("PWD=")) == 0)
			j++;
		if (ft_strncmp(cmds->env->env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
			new = ft_strdup(cmds->env->env[i]);
	}
	if (j != 1 || new == NULL)
		printf("minishell: cd: OLDPWD not set\n");
	else
		do_cd_return_dir(cmds, new);
}

char	*cd_rel_dir(t_cmds *cmds)
{
	char	*start;
	char	*new;

	start = ft_strdup("/Users/pdel-pin");
	new = ft_strjoin(start, ft_strchr(cmds->cmds_argv[1], '/'));
	free(start);
	return (new);
}

//va al directorio indicado. cd (path)
void	cd_move_dir(t_cmds *cmds)
{
	char	*new;
	char	dir[PATH_MAX];

	new = NULL;
	if (cmds->cmds_argv[1][0] == '~')
		new = cd_rel_dir(cmds);
	else
		new = ft_strdup(cmds->cmds_argv[1]);
	getcwd(dir, sizeof(dir));
	if (chdir(new) != 0)
		perror("minishell: cd");
	else
	{
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(new);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
	}
	free(new);
}

void	do_cd(t_cmds *cmds)			//revisar. no funciona igual cuando eliminas directorio anterior al directorio en el que estás
{
	size_t	len;

	len = ft_strlen(cmds->cmds_argv[1]);
	if (ft_double_len(cmds->cmds_argv) == 1)
		cd_home_dir(cmds);
	else if (ft_double_len(cmds->cmds_argv) > 1)
	{
		if (ft_strncmp(cmds->cmds_argv[1], "..", len) == 0
			&& len == ft_strlen(".."))
			cd_back_dir(cmds);
		else if (ft_strncmp(cmds->cmds_argv[1], ".", len) == 0
			&& len == ft_strlen("."))
			return ;
		else if (ft_strncmp(cmds->cmds_argv[1], "-", len) == 0
			&& len == ft_strlen("-"))
			cd_return_dir(cmds);
		else
			cd_move_dir(cmds);
	}
}
