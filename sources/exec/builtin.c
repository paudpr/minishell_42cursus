#include "minishell.h"

void	do_builtin(t_cmds *cmds, int *check)
{
	check_bin(cmds);
	check_bin2(cmds);
	*check = 1;
}

void	check_bin(t_cmds *cmds)
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

void	check_bin2(t_cmds *cmds)
{
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
