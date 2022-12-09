/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:57 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/12/09 16:23:35 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_in(char *infile, int *flag)
{
	int	fd;

	if (access(infile, F_OK | R_OK) == 0)
	{
		fd = open(infile, O_RDONLY);
		if (fd < 0)
			perror("");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		perror("");
		*flag = 1;
		exit(0);
	}
}

static void	redir_out(char *outfile, int *flag)
{
	int	fd;

	if (access(outfile, F_OK | W_OK) == 0 || access(outfile, F_OK) != 0)
	{
		fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			perror("");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		perror("");
		*flag = 1;
		exit(0);
	}
}

static void	redir_app(char *outfile, int *flag)
{
	int	fd;

	if (access(outfile, W_OK) == 0 || access(outfile, F_OK) != 0)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			perror("");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		perror("");
		*flag = 1;
		exit(0);
	}
}

static char	*hd_filename(t_cmds *cmds)
{
	char	*num;
	char	*heredoc;

	num = ft_itoa(cmds->hd);
	heredoc = ft_strjoin("/tmp/heredoc", num);
	free(num);
	return (heredoc);
}

void	check_redir(t_def *def, t_cmds *cmds)
{
	int		i;
	int		flag;
	char	*heredoc;

	i = -1;
	flag = 0;
	while (def->argv[++i])
	{
		if (def->type[i] == T_HD && flag == 0)
		{
			i++;
			heredoc = hd_filename(cmds);
			redir_in(heredoc, &flag);
			free(heredoc);
			cmds->hd++;
		}
		if (def->type[i] == T_RIN && flag == 0)
			redir_in(def->argv[++i], &flag);
		if (def->type[i] == T_ROUT && flag == 0)
			redir_out(def->argv[++i], &flag);
		if (def->type[i] == T_APP && flag == 0)
			redir_app(def->argv[++i], &flag);
	}
}
