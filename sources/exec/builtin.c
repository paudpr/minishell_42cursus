#include "minishell.h"

void do_builtin(t_cmds *cmds, int *check)
{
	// printf("entro en función builtin\n");
	check_bin(cmds);
	check_bin2(cmds);
	*check = 1;
	// printf("valor de bin -> %d\n", cmds->bin);
}

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
	if (ft_strncmp(cmds->cmds_argv[0], "export", ft_strlen("export")) == 0
		&& ft_strlen("export") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_export(cmds);
	}
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
	if (ft_strncmp(cmds->cmds_argv[0], "exit", ft_strlen("exit")) == 0
		&& ft_strlen("exit") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_exit(cmds);
	}
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

void build_env(void)
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
			build_env();
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

//va al home. cd
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

//va un directorio hacia atrás. cd ..
void cd_back_dir(t_cmds *cmds)
{
	char dir[PATH_MAX];
	char *last;
	char *new_dir;

	getcwd(dir, sizeof(dir));
	change_var(cmds->env, "OLDPWD=", dir);
	last = ft_strrchr(dir, '/') + 1;
	new_dir = ft_substr(dir, 0, ft_strlen(dir) - ft_strlen(last));
	chdir(new_dir);
	change_var(cmds->env, "PWD=", new_dir);
	free(new_dir);
}

//vuelve al ultimo directorio donde ha estado. cd -
void	cd_return_dir(t_cmds *cmds)
{
	int		i;
	int		j;
	char	*new;
	char	dir[PATH_MAX];

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
	{
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "OLDPWD=", dir);
		chdir(ft_strchr(new, '/'));
		free(new);
		getcwd(dir, sizeof(dir));
		change_var(cmds->env, "PWD=", dir);
		printf("%s\n", dir);
	}
}

char *cd_rel_dir(t_cmds *cmds)
{
	char *start;
	char	*new;

	start = ft_strdup("/Users/pdel-pin");
	new = ft_strjoin(start, ft_strchr(cmds->cmds_argv[1], '/'));
	free(start);
	return(new);
}

//va al directorio indicado. cd (path)
void cd_move_dir(t_cmds *cmds)
{
	char *new;
	char dir[PATH_MAX];

	new = NULL;
	if(cmds->cmds_argv[1][0] == '~')
		new = cd_rel_dir(cmds);
	else
		new = ft_strdup(cmds->cmds_argv[1]);
	getcwd(dir, sizeof(dir));
	if(chdir(new) != 0)
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

void do_cd(t_cmds *cmds)			//revisar. no funciona igual cuando eliminas directorio anterior al directorio en el que estás
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

void do_exit(t_cmds *cmds)
{
	int len;
	int code;

	len = ft_double_len(cmds->cmds_argv);
	printf("exit\n");
	if(len > 2)
		printf("minishell: exit: too many arguments\n");
	else if(len == 2)
	{
		code = ft_atoi(cmds->cmds_argv[1]);
		exit(code);
	}
	else if(len == 1)
		exit(0);
}




void	print_double_export(char **str)
{
	int i;
	int j;

	if (str == NULL)
		return ;
	i = 0;
	while(str[i])
	{
		j = -1;
		printf("declare -x ");
		while(str[i][++j] != '=')
			printf("%c", str[i][j]);
		if(ft_strchr(str[i], '=') != NULL)
		{
			printf("=\"");
			printf("%s", ft_strchr(str[i], '=') + 1);
			printf("\"\n");
		}
		i++;
	}
}

void add_var(t_cmds *cmds, int i)
{
	if(ft_strchr(cmds->cmds_argv[i], "") != NULL)




}

void do_export(t_cmds *cmds)
{	
	int i;
	int len;
	char **copy;
	
	i = 1;
	copy = NULL;
	len = ft_double_len(cmds->cmds_argv);
	if(len == 1)
	{
		copy = sort_double(cmds->env->env);
		print_double_export(copy);
		ft_free_double(copy);
	}
	else
	{
		while(i < len)
		{
			add_var(cmds, i);
			i++;
		}
	}
}