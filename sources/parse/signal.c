#include "minishell.h"

// SIGINT signal CTRL+C
// param = signal identifier
void	sig_default_sigint(int signal)
{
	(void)signal;
	g_exit_status = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// signal before process fork
void	sig_default(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_default_sigint);
}

// SIGINT signal CTRL+C to exit process
// param = signal identifier
void	sig_process_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (signal == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

// signal after process fork. 
// diferenciates between father and child
void	sig_process(int pid)
{
	if (pid == 0)
		signal(SIGINT, SIG_DFL);
	else
		signal(SIGINT, SIG_IGN);
}
