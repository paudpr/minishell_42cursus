#include "minishell.h"

int count_hd(t_def *def)
{
	int i;
	int n;

	n = 0;
	while(def)
	{
		i = 0;
		while(def->argv[i])
		{
			if(def->type[i] == 0)
			{
				n++;
				i++;
			}
			i++;
		}
		def = def->next;
	}
	return(n);
}

t_hd	*init_hd(t_def *def)
{
	t_hd	*hd;

	hd = ft_calloc(1, sizeof(t_hd));
	if(hd == NULL)
		return(NULL);
	hd->num = count_hd(def);
	//esto está a medias, para guardar las posiciones con el eof correspondiente



}



void	create_file(char *infile, char *file)		//infile nombre de archivo, file relleno
{
	int	fd;
	int	i;

	fd = open(infile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		print_error(0);
	if (file != NULL)
	{
		i = -1;
		while (file[++i])
			write(fd, &file[i], 1);
	}
}


char *get_hd(t_def *def, int i)
{
	char *file;
	pid_t pid;
	int fd;

	pid = fork();
	if(pid < 0)
		perror("");
	if(pid == 0)
	{
		//file = get_next_line(0); 
		//aqui tener un bucle para ir recogiendo desde fd = 0 y que vaya comprobado que no es eof
	}
	wait(&pid);
	return(file);
}


void create_hd(t_def *def, int n)
{
	char *num;
	char *infile;
	char *file;
	int i;

	i = 0;
	while(i < n)
	{
		num = ft_itoa(i);
		infile = ft_strjoin("/tmp/.temp", num);
		file = get_hd(def, i);		//recojo info de hd
		create_file(infile, file);	//creo archivo con info de hd
		free(infile);
		free(num);
		free(file);
		i++;
	}




}


void check_hd(t_def *def, t_env *env)
{
	int n;
	int pos;
	
	(void)env;
	n = num_hd(def);
	if(n == 0)
		return ;
	while(n)
	{
		create_hd(def, n);
		n--;
	}
}

