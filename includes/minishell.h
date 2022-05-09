#ifndef MINISHELL_H
# define MMINISHELL_H

# define T_HD	0
# define T_RIN	1
# define T_ROUT	2
# define T_APP	3
# define T_CMD	4
# define T_ARG	5
# define T_BIN	6

#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_def
{
	char **argv;
	int *type;
	t_def *next;
}	t_def;



#endif
