#include "minishell.h"

// char	*get_hd(char *eof)
// {
// 	char	*read;
// 	char	*line;
// 	char	*aux;
// 	unsigned int 	len;
// 	int		i;

// 	i = 0;
// 	len = ft_strlen(eof);
// 	line = NULL;
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		read = get_next_line(0);

// 		if((ft_strncmp(read, eof, len) == 0) && ((ft_strlen(read) - 1) == len)
// 			&& (read[len] == '\n'))
// 		{
// 			free(read);
// 			return(line);
// 		}
// 		if(i == 0)
// 			line = ft_strdup(read);
// 		else
// 		{
// 			aux = ft_strdup(line);
// 			free(line);
// 			line = ft_strjoin(aux, read);
// 			free(aux);
// 		}
// 		free(read);
// 		i++;
// 	}
// }

// void	create_file(char *infile, char *line)		//infile nombre de archivo, file relleno
// {
// 	int	fd;
// 	int	i;

// 	fd = open(infile, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		perror("");
// 	if (line != NULL)
// 	{
// 		i = -1;
// 		while (line[++i])
// 			write(fd, &line[i], 1);
// 	}
// 	close(fd);
// }

// void check_hd(t_def *def, t_cmds *cmds)
// {
// 	int i;
// 	char *file;
// 	char *infile;

// 	i = 0;
// 	file = NULL;
// 	infile = NULL;
// 	while(def->argv[i])
// 	{
// 		if (def->type[i] == 0)
// 		{
// 			dup2(cmds->fd_in, STDIN_FILENO);			//limpia la entrada y salida de heredoc
//     		dup2(cmds->fd_out, STDOUT_FILENO);
// 			i++;
// 			infile = "/tmp/heredoc";
// 			file = get_hd(def->argv[i]);
// 			create_file(infile, file);
// 			free(file);
// 		}
// 		i++;
// 	}
// }





























































char	*get_hd(char *eof)
{
	char	*read;
	char	*line;
	char	*aux;
	unsigned int 	len;
	int		i;

	i = 0;
	len = ft_strlen(eof);
	line = NULL;
	while(1)
	{
		write(1, "> ", 2);
		read = get_next_line(0);

		if((ft_strncmp(read, eof, len) == 0) && ((ft_strlen(read) - 1) == len)
			&& (read[len] == '\n'))
		{
			free(read);
			return(line);
		}
		if(i == 0)
			line = ft_strdup(read);
		else
		{
			aux = ft_strdup(line);
			free(line);
			line = ft_strjoin(aux, read);
			free(aux);
		}
		free(read);
		i++;
	}
}

void	create_file(char *infile, char *line)		//infile nombre de archivo, file relleno
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
	char *num;
	char *infile;
	char *file;

	num = ft_itoa(n);
	infile = ft_strjoin("/tmp/heredoc", num);
	// printf("infile: %s\n", infile);
	file = get_hd(eof);								//recojo info de hd
	create_file(infile, file);						//creo archivo con info de hd
	free(infile);
	free(num);
	free(file);
}

void	check_hd(t_def *def, t_cmds *cmds)
{
	int i;
	int  hd;
	
	hd = 0;
	while(def)
	{
		i = 0;
		while(def->argv[i])
		{
			if(def->type[i] == 0)
			{
				dup2(cmds->fd_in, STDIN_FILENO);
				dup2(cmds->fd_out, STDOUT_FILENO);
				i++;
				create_hd(hd, def->argv[i]);
				hd++;
			}
			i++;
		}
		def = def->next;
	}
}
