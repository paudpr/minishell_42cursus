#ifndef MINISHELL_H
# define MINISHELL_H

# define T_HD	0
# define T_RIN	1
# define T_ROUT	2
# define T_APP	3
# define T_CMD	4
# define T_BIN	5

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include "../libft/libft.h"

typedef struct s_def
{
	char	**argv;
	int		*type;
	struct s_def *next;
}	t_def;

typedef struct s_env
{
	char	**env;
	char	**path;
	int		shlvl;
}	t_env;

typedef struct s_cmds
{
	t_env	*env;
	char	*cmds_path;			//guarda el path con / al final
	char	**cmds_argv;		//guarda el comando con sus flags y argumentos
	int		**pipe_fd;
	int		fd_in;
	int		fd_out;
	int		num; 				// posición de comando
	int		hd;
	int		bin;
}	t_cmds;



t_def	*mini_lstnew(void *content, int *array);
void	mini_lstadd_back(t_def **lst, t_def *new);
t_def	*mini_lstlast(t_def *lst);
int		mini_lstsize(t_def *def);



t_env	*get_struct_env(char **environ);
void	build_environ(void);
void	copy_environ(char **environ, t_env *env);
int		get_shlvl(char **environ);
void	get_list(t_def **def, char *argv);	//quitar cuando esté parseo
void	main_exec(t_def *def, t_env *env);
void	free_list(t_def **def);

void    init_struct_cmds(t_env *env, t_cmds *cmds, int i);
void	get_argv_path(t_def *def, t_cmds *cmds);
void	exec_cmds(t_def *def, t_cmds *cmds);


int	check_hd(t_def *def);
void	create_file(char *infile, char *line);
char	*get_hd(char *eof);
void	clean_hd(int hd);

void check_redir(t_def *def, t_cmds *cmds);



void wait_process(t_def *def);
void check_leaks();

void do_process(t_def *def, t_cmds *cmds);
void do_commands(t_def *def, t_cmds *cmds, int *check);
void do_one_command(t_def *def, t_cmds *cmds, int *check);
void do_last_command(t_def *def, t_cmds *cmds, int *check);
void wait_process(t_def *def);


void check_bin(t_cmds *cmds);
void check_bin2(t_cmds *cmds);
void	do_echo(t_cmds *cmds);
void do_pwd(t_cmds *cmds);
void do_env(t_cmds *cmds);
void do_cd(t_cmds *cmds);

#endif







void free_env(t_env *env);
int *get_array(char *pipes);
void init_vals(t_cmds *vals, char **environ, t_def **def);
char **get_argv(t_def *def);
void free_struct(t_cmds *vals);
char    *get_path(char **path, char *argvs);
char *check_valid(char **path, char *cmd);
void exec(t_cmds *cmds);
void free_pipe(t_cmds *cmds, int size);
char *get_relative_argv(char *cmd);
char *get_relative_path(char *cmd);
char *join_argv(char *cmd, char **split);
void free_env(t_env *env);
void ft_free_double(char **str);
void print_error(char *str);
void print_node(t_def **node, int i);
void	print_double(char **str);
