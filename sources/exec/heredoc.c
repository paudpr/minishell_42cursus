/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:47 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/01/02 14:05:36 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_hd_norm(char **read, char **line, int i)
{
	char	*aux;

	if (i == 0)
		*line = ft_strdup(*read);
	else
	{
		aux = ft_strdup(*line);
		free(*line);
		*line = ft_strjoin(aux, *read);
		free(aux);
	}
}

static char	*get_hd(char *eof)
{
	char			*read;
	char			*line;
	unsigned int	len;
	int				i;

	i = 0;
	len = ft_strlen(eof);
	line = NULL;
	while (1)
	{
		write(1, "> ", 2);
		read = get_next_line(0);
		if ((ft_strncmp(read, eof, len) == 0) && ((ft_strlen(read) - 1) == len)
			&& (read[len] == '\n'))
		{
			free(read);
			return (line);
		}
		get_hd_norm(&read, &line, i);
		free(read);
		i++;
	}
}

static void	create_file(char *infile, char *line)
{
	int	fd;
	int	i;

	fd = open(infile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("");
	if (line != NULL)
	{
		i = -1;
		while (line[++i])
			write(fd, &line[i], 1);
	}
}

static void	create_hd(int n, char *eof)
{
	char	*num;
	char	*infile;
	char	*file;

	num = ft_itoa(n);
	infile = ft_strjoin("/tmp/heredoc", num);
	file = get_hd(eof);
	create_file(infile, file);
	free(infile);
	free(num);
	free(file);
}

int	check_hd(t_def *def)
{
	int	i;
	int	hd;

	hd = 0;
	while (def)
	{
		i = 0;
		while (def->argv[i])
		{
			if (def->type[i] == T_HD)
			{
				i++;
				create_hd(hd, def->argv[i]);
				hd++;
			}
			i++;
		}
		def = def->next;
	}
	return (hd);
}
