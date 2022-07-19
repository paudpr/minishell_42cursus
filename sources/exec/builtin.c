#include "minishell.h"

void check_bin(t_cmds *cmds)
{
	if (ft_strncmp(cmds->cmds_argv[0], "echo", ft_strlen("echo")) == 0
		&& ft_strlen("echo") == ft_strlen(cmds->cmds_argv[0]))
	{
		cmds->bin = 1;
		do_echo(cmds);
	}
	// if (ft_strncmp(cmds->cmds_argv[0], "cd", ft_strlen("cd")) == 0
	// 	&& ft_strlen("cd") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_cd(cmds);
	// }
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
	// if (ft_strncmp(cmds->cmds_argv[0], "env", ft_strlen("env")) == 0
	// 	&& ft_strlen("env") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_env(cmds);
	// }
	// if (ft_strncmp(cmds->cmds_argv[0], "exit", ft_strlen("exit")) == 0
	// 	&& ft_strlen("exit") == ft_strlen(cmds->cmds_argv[0]))
	// {
	// 	cmds->bin = 1;
	// 	do_exit(cmds);
	// }
}

int	check_flag(t_cmds *cmds)
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
		flag = check_flag(cmds);
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
	char *pwd;

	(void)cmds;
	pwd = getenv("PWD");
	printf("%s\n", pwd);
}