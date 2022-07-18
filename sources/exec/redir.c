#include "minishell.h"

void	redir_in(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		perror("");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_out(char *outfile)
{
	int	fd;

	fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_app(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	check_redir(t_def *def, t_cmds *cmds)
{
	int		i;
	char	*num;
	char	*heredoc;

	i = 0;
	while (def->argv[i])
	{
		if (def->type[i] == 0)
		{
			i++;
			num = ft_itoa(cmds->hd);
			heredoc = ft_strjoin("/tmp/heredoc", num);
			redir_in(heredoc);
			free(num);
			free(heredoc);
			cmds->hd++;
		}
		if (def->type[i] == 1)
			redir_in(def->argv[++i]);
		if (def->type[i] == 2)
			redir_out(def->argv[++i]);
		if (def->type[i] == 3)
			redir_app(def->argv[++i]);
		i++;
	}
}
