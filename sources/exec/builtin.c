#include "minishell.h"

void check_bin(t_cmds *cmds)
{
	if (ft_strncmp(cmds->cmds_argv[0], "echo", ft_strlen("echo")) == 0
		&& ft_strlen("echo") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_echo(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "cd", ft_strlen("cd")) == 0
		&& ft_strlen("cd") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_cd(cmds);
	}
	if (ft_strncmp(cmds->cmds_argv[0], "pwd", ft_strlen("pwd")) == 0
		&& ft_strlen("pwd") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_pwd(cmds);
	}
	// if (ft_strncmp(cmds->cmds_argv[0], "export", ft_strlen("export")) == 0
	// 	&& ft_strlen("export") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_export(cmds);
	// }
}

void check_bin2(t_cmds *cmds)
{
	(void)cmds;
	// printf("ES BUILTIN \n");
	// if (ft_strncmp(cmds->cmds_argv[0], "unset", ft_strlen("unset")) == 0
	// 	&& ft_strlen("unset") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_unset(cmds);
	// }
	if (ft_strncmp(cmds->cmds_argv[0], "env", ft_strlen("env")) == 0
		&& ft_strlen("env") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_env(cmds);
	}
	// if (ft_strncmp(cmds->cmds_argv[0], "exit", ft_strlen("exit")) == 0
	// 	&& ft_strlen("exit") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_exit(cmds);
	// }
}

// int	check_flag_env(t_cmds *cmds)
// {
// 	int i;

// 	i = 0;
// 	if(cmds->cmds_argv[1][i])
// 	{
// 		printf("dentro del bucle\n");
// 		if(i == 0 && cmds->cmds_argv[1][i] == '-')
// 			i++;
// 		if(cmds->cmds_argv[1][i] == 'i')
// 			i++;
// 		else
// 			return(0);
// 	}
// 	return (1);
// }

// void	do_env(t_cmds *cmds)
// {
// 	int		flag;
// 	t_env	*copy;

// 	flag = 0;
// 	copy = ft_calloc(sizeof(t_env), 1);
// 	if (copy == NULL)
// 		print_error("memoria");
// 	flag = check_flag_env(cmds);
// 	printf("flag -> %d\n", flag);
// 	if (ft_double_len(cmds->env->env) == 0)
// 		build_environ(copy);
// 	else
// 		copy_environ(cmds->env->env, copy);
// 	dprintf(2, "flaag -> %d\n", flag);
// 	dprintf(2, "%s\n", copy->env[0]);
// 	if(flag == 1)
// 	{
// 		free_env(copy);
// 		free(copy);
// 		return ;
// 	}
// 	else
// 		print_double(copy->env);
// 	free_env(copy);
// 	free(copy);
// }

void build_environ(void)
{
	char cwd[PATH_MAX];
	char *shlvl;
	t_env *copy;

	copy = ft_calloc(sizeof(t_env), 1);
	if(copy == NULL)
		return ;
	copy->env = ft_calloc(sizeof(char *), 3);
	if(copy->env == NULL)
		return ;
	getcwd(cwd, sizeof(cwd));
	copy->shlvl = 1;
	shlvl = ft_itoa(copy->shlvl);
	copy->env[0] = ft_strjoin("PWD=", cwd);
	copy->env[1] = ft_strjoin("SHLVL=", shlvl);
	free(shlvl);
	copy->env[2] = ft_strjoin("_=", cwd);
	copy->path = NULL;
	print_double(copy->env);
	ft_free_double(copy->env);
	free(copy);
}

void do_env(t_cmds *cmds)
{
	t_env *copy;

	copy = ft_calloc(sizeof(t_env), 1);
	if(copy == NULL)
		print_error("memoria");
	if(ft_double_len(cmds->cmds_argv) == 1)
	{
		if(ft_double_len(cmds->env->env) == 0)
			build_environ();
		else
			print_double(cmds->env->env);
	}
	else
	{
		if(ft_double_len(cmds->cmds_argv) > 1)
		{
			return ;
			//si es flag
			//si es ejecutable
			//si son las dos cosas
		}
	}
}


int	check_flag_echo(t_cmds *cmds)
{
	int i;

	i = 0;
	while(cmds->cmds_argv[1][i])
	{
		if(i == 0 && cmds->cmds_argv[1][i] == '-')
			i++;
		if(cmds->cmds_argv[1][i] == 'n')
			i++;
		else
			return(0);
	}
	return (1);
}

void	do_echo(t_cmds *cmds)
{
	int	flag;
	int	i;

	flag = 0;
	if (ft_double_len(cmds->cmds_argv) == 1)
		printf("\n");
	if (ft_double_len(cmds->cmds_argv) > 1)
	{
		i = 1;
		flag = check_flag_echo(cmds);
		if (flag > 0)
			i++;
		while(i < ft_double_len(cmds->cmds_argv))
		{
			printf("%s", cmds->cmds_argv[i]);
			if (i + 1 < ft_double_len(cmds->cmds_argv))
				printf(" ");
			i++;
		}
		if(flag == 0)
			printf("\n");
	}
}

void do_pwd(t_cmds *cmds)
{
	char pwd[PATH_MAX];

	(void)cmds;
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	//hacer comparación con variable de entorno pr asegurar, pero gestionar 
	//la actualiación de esa variable en cd
}



void change_var(t_env *env, char *var, char *new)
{
	int		i;
	char *copy;

	i = 0;
	while(i < ft_double_len(env->env))
	{
		if(ft_strncmp(env->env[i], var, ft_strlen(var)) == 0)
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

void cd_home_dir(t_cmds *cmds)		// tener en cuenta que pasa si no existe $HOME
{
	int i;
	char *home;
	char dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	i = 0;
	home = NULL;
	while(i < ft_double_len(cmds->env->env))
	{
		if(ft_strncmp(cmds->env->env[i], "HOME=", ft_strlen("HOME=")) == 0)
			home = ft_strchr(cmds->env->env[i], '/');
		i++;
	}
	if(home != NULL)
	{
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(home);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
	}
	else
		printf("minishell: cd: HOME not set\n");
}

void cd_back_dir(t_cmds *cmds)
{
	char dir[PATH_MAX];
	char *last;
	char *new_dir;

	getcwd(dir, sizeof(dir));
	last = ft_strrchr(dir, '/') + 1;
	new_dir = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(last));
	// printf("%s\n", new_dir);
	change_var(cmds->env, "OLDPWD=", dir);
	change_var(cmds->env, "PWD=", new_dir);
	printf("valor de chdir -> %d\n", chdir(new_dir));
	printf("new_dir -> %s\n", new_dir);
	free(new_dir);
}

void cd_return_dir(t_cmds *cmds)
{
	int i;
	char *old;
	char *dir;

	i = 0;
	old = NULL;
	dir = NULL;
	while(i < ft_double_len(cmds->env->env))
	{
		if(ft_strncmp(cmds->env->env[i], "PWD=", ft_strlen("PWD=")) == 0)
			dir = ft_strdup(cmds->env->env[i]);
		if(ft_strncmp(cmds->env->env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
			old = ft_strdup(cmds->env->env[i]);
		i++;
	}
	if(old == NULL || dir == NULL)
		printf("minishell: cd: OLDPWD not set\n");
	else
	{
		change_var(cmds->env, "OLDPWD=", dir);
		change_var(cmds->env, "PWD=", old);
		chdir(old);
		free(dir);
		free(old);
	}
}

void cd_move_dir(t_cmds *cmds)
{
	(void)cmds;


}

void do_cd(t_cmds *cmds)
{
	if(ft_double_len(cmds->cmds_argv) == 1)
		cd_home_dir(cmds);
	else if (ft_double_len(cmds->cmds_argv) > 1)
	{
		if(ft_strncmp(cmds->cmds_argv[1], "..", ft_strlen(cmds->cmds_argv[1])) == 0 
			&& ft_strlen(cmds->cmds_argv[1]) == ft_strlen(".."))
			cd_back_dir(cmds);
		else if(ft_strncmp(cmds->cmds_argv[1], ".", ft_strlen(cmds->cmds_argv[1])) == 0 
			&& ft_strlen(cmds->cmds_argv[1]) == ft_strlen("."))
			return;
		else if(ft_strncmp(cmds->cmds_argv[1], "-", ft_strlen(cmds->cmds_argv[1])) == 0 
			&& ft_strlen(cmds->cmds_argv[1]) == ft_strlen("-"))
			cd_return_dir(cmds);
		else
			cd_move_dir(cmds);
	}



}
