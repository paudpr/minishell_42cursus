#include "minishell.h"

void	redir_in(char *infile, int *flag)
{
	int	fd;

	if(access(infile, F_OK | R_OK) != 0)
	{
		fd = open(infile, O_RDONLY);
		if (fd < 0)
			perror("");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		*flag = 1;
}

void	redir_out(char *outfile, int *flag)
{
	int	fd;

	if(access(outfile, W_OK) != 0)
	{
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror("");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		*flag = 1;
}

void	redir_app(char *outfile, int *flag)
{
	int	fd;

	if(access(outfile, W_OK) != 0)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror("");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		*flag = 1;
}

void	check_redir(t_def *def, t_cmds *cmds)
{
	int		i;
	int		flag;
	char	*num;
	char	*heredoc;

	i = 0;
	flag = 0;
	while (def->argv[i])
	{
		if (def->type[i] == 0 && flag == 0)
		{
			i++;
			num = ft_itoa(cmds->hd);
			heredoc = ft_strjoin("/tmp/heredoc", num);
			redir_in(heredoc, &flag);
			free(num);
			free(heredoc);
			cmds->hd++;
		}
		if (def->type[i] == 1 && flag == 0)
			redir_in(def->argv[++i], &flag);
		if (def->type[i] == 2 && flag == 0)
			redir_out(def->argv[++i], &flag);
		if (def->type[i] == 3 && flag == 0)
			redir_app(def->argv[++i], &flag);
		i++;
	}
}
