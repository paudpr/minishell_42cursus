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
	// printf("ES BUILTIN \n");
	if (ft_strncmp(cmds->cmds_argv[0], "unset", ft_strlen("unset")) == 0
		&& ft_strlen("unset") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_unset(cmds);
	}
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
// 	if (cmds->cmds_argv[1][i])
// 	{
// 		printf("dentro del bucle\n");
// 		if (i == 0 && cmds->cmds_argv[1][i] == '-')
// 			i++;
// 		if (cmds->cmds_argv[1][i] == 'i')
// 			i++;
// 		else
// 			return (0);
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
// 	if (flag == 1)
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
	if (copy == NULL)
		return ;
	copy->env = ft_calloc(sizeof(char *), 3);
	if (copy->env == NULL)
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
	if (copy == NULL)
		print_error("memoria");
	if (ft_double_len(cmds->cmds_argv) == 1)
	{
		if (ft_double_len(cmds->env->env) == 0)
			build_env();
		else
			print_double(cmds->env->env);
	}
	else
	{
		if (ft_double_len(cmds->cmds_argv) > 1)
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
		if (i == 0 && cmds->cmds_argv[1][i] == '-')
			i++;
		if (cmds->cmds_argv[1][i] == 'n')
			i++;
		else
			return (0);
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
		if (flag == 0)
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
	return (new);
}

//va al directorio indicado. cd (path)
void cd_move_dir(t_cmds *cmds)
{
	char *new;
	char dir[PATH_MAX];

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

void do_cd(t_cmds *cmds)			//revisar. no funciona igual cuando eliminas directorio anterior al directorio en el que estás
{
	if (ft_double_len(cmds->cmds_argv) == 1)
		cd_home_dir(cmds);
	else if (ft_double_len(cmds->cmds_argv) > 1)
	{
		if (ft_strncmp(cmds->cmds_argv[1], "..", ft_strlen(cmds->cmds_argv[1])) == 0 
			&& ft_strlen(cmds->cmds_argv[1]) == ft_strlen(".."))
			cd_back_dir(cmds);
		else if (ft_strncmp(cmds->cmds_argv[1], ".", ft_strlen(cmds->cmds_argv[1])) == 0
			&& ft_strlen(cmds->cmds_argv[1]) == ft_strlen("."))
			return;
		else if (ft_strncmp(cmds->cmds_argv[1], "-", ft_strlen(cmds->cmds_argv[1])) == 0 
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
	if (len > 2)
		printf("minishell: exit: too many arguments\n");
	else if (len == 2)
	{
		code = ft_atoi(cmds->cmds_argv[1]);
		exit(code);
	}
	else if (len == 1)
		exit(0);
}


void	print_double_export(char **str)
{
	int i;
	int j;
	int len;

 	if (str == NULL)
		return ;
	i = 0;
	len = ft_double_len(str);
	while(i < len)
	{
		j = -1;
		printf("declare -x ");
		while(str[i][++j] != '=' && str[i][j])
			printf("%c", str[i][j]);
		if (ft_strchr(str[i], '=') != 0) 
		{
			printf("=\"");
			printf("%s", ft_strchr(str[i], '=') + 1);
			printf("\"");
		}
		printf("\n");		//REVISAR
		i++;
	}
}

int check_valid_var(t_cmds *cmds, int i)
{
	int j;

	if (ft_isalpha(cmds->cmds_argv[i][0]) != 1)
	{
		perror("minishell: export: not a valid identifier");
		return (0);
	}
	j = 1;
	while(j < (int)ft_strlen(cmds->cmds_argv[i]) && cmds->cmds_argv[i][j] != '=')
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

char *clean_var(char *new)
{
	int i;
	int length;
	char *var;
	char aux;
	
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
		while(++i < length)
		{
			if (new[i] == 34 || new[i] == 39)
				i++;
			var[i] = new[i];
		}
	}
	return (var);
}

void add_new_var(t_cmds *cmds, int i, int len)
{
	int j;
	char **new;
	
	j = -1;
	new = ft_calloc(len + 2, sizeof(char *));
	if (new == NULL)
		exit(0);
	while(++j < len)			//volver a probar esta mierda a ver si se estan guardando todos o si hay que hacer len - 1 para que no copie el nulo  y  luego asignar a mano el nulo
		new[j] = ft_strdup(cmds->env->env[j]);
	new[j] = clean_var(cmds->cmds_argv[i]);
	ft_free_double(cmds->env->env);
	cmds->env->env = new;

}

void transform_var(t_cmds *cmds, int i, int len)
{
	int j;
	int length;
	char *other;

	other = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(other);
	j = 0;
	while(j < len)
	{
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0)
		{
			free(cmds->env->env[j]);
			cmds->env->env[j] = clean_var(cmds->cmds_argv[i]);
		}
		j++;
	}
}

int var_exists(t_cmds *cmds, int i, int len)
{
	int j;
	int length;
	int flag;
	char *other;

	j = 0;
	flag = 0;
	other = ft_strchr(cmds->cmds_argv[i], '=');
	length = ft_strlen(cmds->cmds_argv[i]) - ft_strlen(other);
	while(j < len)
	{
		if (ft_strncmp(cmds->cmds_argv[i], cmds->env->env[j], length) == 0)
			flag = 1;
		j++;
	}
	return (flag);
}

void add_var(t_cmds *cmds, int i)
{
	int len;

	len = ft_double_len(cmds->env->env);
	if (check_valid_var(cmds, i) != 0)
	{
		if (var_exists(cmds, i, len) == 1)
			transform_var(cmds, i, len);
		else
			add_new_var(cmds, i, len);
	}
}

void do_export(t_cmds *cmds)
{	
	int i;
	int len;
	char **copy;
	
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
		while(i < len)
		{
			add_var(cmds, i);
			i++;
		}
	}
}






char *get_var_name(char *var)
{
	int length;
	char *aux;

	if(ft_strchr(var, '=') == 0)
		return(ft_strdup(var));
	else
	{
		aux = ft_strchr(var, '=');
		length = ft_strlen(var) - ft_strlen(aux);
		return(ft_substr(var, 0, length));
	}
}

void do_unset(t_cmds *cmds)
{
	int i;
	int j;
	int k;
	char *var;
	char **copy;

	copy = NULL;
	if(ft_double_len(cmds->cmds_argv) == 1)
		return ;
	i = 1;
	j = 0;
	k = 0;
	copy = ft_calloc(ft_double_len(cmds->env->env), sizeof(char *));
	while(cmds->cmds_argv[i])
	{
		while(j < ft_double_len(cmds->env->env))
		{
			var = get_var_name(cmds->env->env[j]);
			if(ft_strncmp(cmds->cmds_argv[i], var, ft_strlen(cmds->cmds_argv[i])) == 0 
				&& ft_strlen(cmds->cmds_argv[i]) == ft_strlen(var))
			{
				printf("\nvariable que me salto -> %s\n\n", var);
				j++;
			}
			free(var);
			copy[k] = ft_strdup(cmds->env->env[j]);
			printf("%s\n", copy[k]);
			k++;
			j++;

		}
		i++;
	}
	ft_free_double(cmds->env->env);
	cmds->env->env = copy;
}