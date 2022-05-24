#include "pruebas_bash.h"

t_env   *get_struct_env(char **environ)
{
    int     i;
    t_env   *env;
    char    *path;

    i = 0;
    env =  malloc(sizeof(t_env));
    env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
    while (environ[i])
    {
        env->env[i] = ft_strdup(environ[i]);
        if (ft_strnstr(environ[i], "PATH=", 5))
			path = ft_strdup(environ[i]);
		i++;
    }
    env->path = ft_split(path, ':');
    free(path);
    return (env);
}

t_cmds  *get_struct_cmds(t_def *def, t_env *env)
{
    t_cmds  *cmds;

    cmds = malloc(sizeof(t_cmds));
    cmds->env = env;
    cmds->num = 0;
    ft_bzero(cmds->pipe_fd, 2);
    cmds->cmds_argv = get_argv(def);
    // cmds->cmds_path = get_path(def);
    // printf("%p   %p \n", cmds->env, env);
    return (cmds);
}

// char    *get_path(t_def *def)
// {




// }

char    *get_argv(t_def *def)
{
    int     i;
    char   *cmd;
    char   *aux;
    char   *temp;

    i = 0;
    cmd = NULL;
    while (def->argv[i])
    {
        if (def->type[i] == 4)
        {
            if (!cmd)
                cmd = ft_strdup(def->argv[i]);
            else
            {
                aux = ft_strjoin(cmd, " ");
                temp = ft_strdup(def->argv[i]);
                free(cmd);
                cmd = ft_strjoin(aux, temp);
                free(aux);
                free(temp);
            }
        }
        i++;
    }
    return (cmd);
}




