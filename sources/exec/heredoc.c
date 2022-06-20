#include "minishell.h"

char	*get_hd(char *eof)
{
	char	*read;
	char	*line;
	char	*aux;
	int 	len;
	int		i;

	i = 0;
	len = ft_strlen(eof);
	line = NULL;
	while(1)
	{
		write(1, "> ", 2);
		read = get_next_line(0);

		printf("comprobaciones bucle\n");
		printf("%d\n", ft_strncmp(read, eof, len));
		printf("%lu  -  %zu\n", (ft_strlen(read) - 1), (ft_strlen(eof)));
		printf("%d\n", read[ft_strlen(eof)]);
		if((ft_strncmp(read, eof, len) == 0) && ((ft_strlen(read) - 1) == ft_strlen(eof))
			&& (read[ft_strlen(eof)] == '\n'))
		{
			printf("NETRO AQUI\n");
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


// static int	loop_heredoc(t_lst *lst, int pos, char *file)
// {
// 	char	*line;
// 	int		f;

// 	line = readline("> ");
// 	if (line == NULL)
// 		return (1);
// 	if (ft_strncmp(line, lst->argv[pos], ft_strlen(lst->argv[pos])) == 0
// 		&& (ft_strlen(line)) == ft_strlen(lst->argv[pos]))
// 	{
// 		free(line);
// 		return (1);
// 	}
// 	f = open(file, O_RDWR | O_APPEND, line);
// 	if (f < 0)
// 		exit(EXIT_FAILURE);
// 	write(f, line, ft_strlen(line));
// 	write(f, "\n", 1);
// 	close(f);
// 	free(line);
// 	return (0);
// }


void	create_file(char *infile, char *line)		//infile nombre de archivo, file relleno
{
	int	fd;
	int	i;

	fd = open(infile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("");
	printf("NETRO AQUI222\n");
	if (line != NULL)
	{
		i = -1;
		printf("PETO AQUI\n");
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
	infile = ft_strjoin("/tmp/.tmp/", num);
	printf("infile: %s\n", infile);
	file = get_hd(eof);								//recojo info de hd
	create_file(infile, file);						//creo archivo con info de hd
	free(infile);
	free(num);
	free(file);


}

void	check_hd(t_def *def)
{
	int n;
	int i;
	
	n = 0;
	while(def)
	{
		i = 0;
		printf("BUCLE 1\n");
		while(def->argv[i])
		{
			printf("BUCLE 2\n");
			if(def->type[i] == 0)
			{
				i++;
				printf("eof num %d is -> %s\n", n, def->argv[i]);
				create_hd(n, def->argv[i]);
				n++;
			}
			i++;
		}
		def = def->next;
	}
}








// static void	heredoc_loop(t_heredoc *vars)
// {
// 	char	*aux;

// 	aux = ft_strdup(vars->infile);
// 	free(vars->infile);
// 	vars->infile = ft_strjoin(aux, vars->line);
// 	free(vars->line);
// 	free(aux);
// 	vars->line = get_next_line(0);
// }

// void	heredoc(char **argv)
// {
// 	t_heredoc	vars;

// 	vars.len = ft_strlen(argv[2]);
// 	vars.infile = get_next_line(0);
// 	if (ft_strncmp(argv[2], vars.infile, vars.len) != 0
// 		|| vars.infile[vars.len] != '\n')
// 	{
// 		vars.line = get_next_line(0);
// 		while (ft_strncmp(argv[2], vars.line, vars.len) != 0
// 			|| vars.line[vars.len] != '\n')
// 		{
// 			heredoc_loop(&vars);
// 		}
// 		free(vars.line);
// 		free(vars.infile);
// 	}
// 	else
// 	{
// 		free(vars.infile);
// 		vars.infile = 0;
// 	}
// 	create_file(vars.infile);
// }
