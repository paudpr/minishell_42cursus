/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:10 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/10/03 15:52:11 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define T_HD	0
# define T_RIN	1
# define T_ROUT	2
# define T_APP	3
# define T_CMD	4

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
	char			**argv;
	int				*type;
	struct s_def	*next;
}	t_def;

typedef struct s_env
{
	char			**env;
	int				shlvl;
}	t_env;

typedef struct s_cmds
{
	t_env	*env;
	char	*cmds_path;			//guarda el path con / al final
	char	**cmds_argv;		//guarda el comando con sus flags y argumentos
	int		**pipe_fd;
	int		fd_in;
	int		fd_out;
	int		num;				// posición de comando
	int		hd;
	int		bin;
}	t_cmds;

// env.c
t_env	*get_struct_env(char **environ);
void	build_env(void);
void	copy_environ(char **environ, t_env *env);

// main_exec.c
void	main_exec(t_def *def, t_env *env);
void	exec_cmds(t_def *def, t_cmds *cmds);

// list_to_struct.c
void	get_argv_path(t_def *def, t_cmds *cmds);
char	*get_relative_path(char *cmd);
char	*get_relative_argv(char *cmd);

// init_struct.c
void	init_struct_cmds(t_env *env, t_cmds *cmds, int i);
char	*check_valid(char **path, char *cmd);

// heredoc.c
int		check_hd(t_def *def);

// heredoc_2.c
void	clean_hd(int hd);

// exec.c
void	do_process(t_def *def, t_cmds *cmds);

// redir.c
void	check_redir(t_def *def, t_cmds *cmds);

// builtin.c
void	do_builtin(t_cmds *cmds, int *check);

//utils.c
char	**sort_double(char **str);
void	print_double(char **str);
void	wait_process(t_def *def);
void	print_error(char *str);

//utils_list.c
t_def	*mini_lstnew(void *content, int *array);
void	mini_lstadd_back(t_def **lst, t_def *new);
t_def	*mini_lstlast(t_def *lst);
int		mini_lstsize(t_def *def);

// utils_free.c
void	free_pipe(t_cmds *cmds, int size);
void	free_struct(t_cmds *vals);
void	free_env(t_env *env);
void	free_list(t_def **def);

// bin_.c
void	do_echo(t_cmds *cmds);
int		check_flag_echo(t_cmds *cmds);
void	do_pwd(t_cmds *cmds);
void	do_exit(t_cmds *cmds);
void	do_env(t_cmds *cmds);
void	build_env(void);
void	print_double_env(char **str);
void	do_cd(t_cmds *cmds);
void	cd_move_dir(t_cmds *cmds);
void	cd_return_dir(t_cmds *cmds);
void	do_cd_return_dir(t_cmds *cmds, char *new);
void	cd_back_dir(t_cmds *cmds);
void	cd_home_dir(t_cmds *cmds);
void	change_var(t_env *env, char *var, char *new);
void	do_export(t_cmds *cmds);
void	add_var(t_cmds *cmds, int i);
void	transform_var(t_cmds *cmds, int i, int len);
void	add_new_var(t_cmds *cmds, int i, int len);
char	*clean_var(char *new);
int		check_valid_var(t_cmds *cmds, int i);
void	print_double_export(char **str);
void	do_unset(t_cmds *cmds);
void	del_var(t_cmds *cmds, int i, int len);
int		var_exists(t_cmds *cmds, int i, int len);

/* PARSE */
void	main_parse(t_def **def, char *line);

// luego borrar para poner parse bien
void	get_list(t_def **def, char *argv);	//quitar cuando esté parseo

#endif
