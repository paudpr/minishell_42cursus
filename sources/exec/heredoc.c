#include "minishell.h"

void	get_hd_norm(char *line, char *read)
{
	char	*aux;

	aux = ft_strdup(line);
	free(line);
	line = ft_strjoin(aux, read);
	free(aux);
}

char	*get_hd(char *eof)
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
		if (i == 0)
			line = ft_strdup(read);
		else
			get_hd_norm(line, read);
		free(read);
		i++;
	}
}

void	create_file(char *infile, char *line)
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

void	create_hd(int n, char *eof)
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
			if (def->type[i] == 0)
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

void	clean_hd(int hd)
{
	int		i;
	char	*num;
	char	*name;

	i = 0;
	while (i < hd)
	{
		num = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc", num);
		unlink(name);
		free(name);
		free(num);
		i++;
	}
}
