#include "minishell.h"

void check_redir(t_def *def, t_cmds *cmds)
{
    int i;
    int fd;

    i = 0;
    while(def->argv[i] && (def->type[i] == 0 || def->type[i] == 1))
    {
        if(def->type[i] == 0)
        {
            i++;
            fd = open("/tmp/heredoc", O_RDONLY);

        }
        else if(def->type[i] == 1)
        {
            i++;
            fd = open(def->argv[i], O_RDONLY);
        }
        i++;
    }
    cmds->pipe_fd[cmds->num][0] = fd;
    dup2(cmds->pipe_fd[cmds->num][0], STDIN_FILENO);
    // cmds->pipe_fd[cmds->num][0] = fd;
}