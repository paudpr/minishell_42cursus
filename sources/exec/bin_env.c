#include "minishell.h"

void	build_env(void)
{
	char	cwd[PATH_MAX];
	char	*shlvl;
	t_env	*copy;

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
	print_double(copy->env);
	ft_free_double(copy->env);
	free(copy);
}

void	do_env(t_cmds *cmds)
{
	t_env	*copy;

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
