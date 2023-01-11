/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauladelpinoramirez <pauladelpinoramire    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:52:10 by pdel-pin          #+#    #+#             */
/*   Updated: 2023/01/03 22:49:57 by pauladelpin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define T_HD	1
# define T_RIN	2
# define T_ROUT	3
# define T_APP	4
# define T_CMD	5
# define T_WC	6

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include "../libft/libft.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;90m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define DARKGREEN "\e[0;32;40m"
# define RESET "\033[0m"

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

int		g_exit_status;

/* EXEC */

// env.c
void	change_last_exec(t_cmds *cmds, char *cmd, int type);
t_env	*get_struct_env(char **environ);
void	build_environ(t_env *env);
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
void	do_process(t_def *def, t_cmds *cmds, int check, int i);

// redir.c
void	check_redir(t_def *def, t_cmds *cmds);

// builtin.c
void	do_builtin(t_cmds *cmds, int *check, t_def *def);

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
void	free_def(t_def **def);

// bin_*.c
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

void	main_parse(t_def **def, char *line, t_env *env);

// split_blocks.c
// t_list	*split_blocks(char *line, int i);
t_list	*split_blocks(char *line);
int		check_next(char *line, int i, char flag);
int		len_block(char *line, int i);
int		ignore_spaces(char *line, int i);

// clean_redir.c
int	clean_redir(t_list *lst);

// parse_nodes.c
char	*build_str(char *str_1, char *str_2, int type);
t_def	*parse_nodes(t_list *lst, t_env *env);

// parse_tokens.c
int		parse_tokens(t_list *lst);
int		parse_redir_tokens(t_list *lst);
int		error_redir_tokens(t_list *lst, char flag, int type);
void	print_redir_err_tokens(int i, char type);
int		parse_pipe_tokens(t_list *lst);
int		parse_pipe_aux(int i);

// parse_com.c
int		parse_com(t_list *lst);
int		check_closed_coms(char *str);
char	*build_str(char *str_1, char *str_2, int type);
char	*get_quoted(char *str, t_env *env, int i, char flag);
char	*get_var(char *str, t_env *env);
char	*check_expansion(char *var, t_env *env);
int		size_var(char *str);
int		size_quoted(char *str);

/* clean_com.c */
void	clean_com(char **str, t_env *env);

/* com_close.c */
void	wait_close_coms(char *str, int num, char flag);

/* var_expansion.c */
char	*get_var(char *str, t_env *env);
char	*check_expansion(char *var, t_env *env);
int		size_var(char *str);

/* signal.c */
void	sig_default_sigint(int signal);
void	sig_default(void);
void	sig_process(int pid);
void	sig_process_sigint(int signal);
void	sig_heredoc(void);

/* wildcard.c */
// t_def	*get_wildcard(t_def **node);
t_def	*get_wildcard(t_def **node, char *argv, int type, int *i);

// luego borrar para poner parse bien
void	get_list(t_def **def, char *argv);	//quitar cuando esté parseo
void	print_list(t_list *lst);
void	print_nodes(t_def *def);
void	free_lst(t_list *lst);
#endif
