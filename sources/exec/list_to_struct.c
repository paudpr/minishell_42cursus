#include "pruebas_bash.h"

t_env   *get_struct_env(char **environ)
{
    int     i;
    t_env   *env;
    char    *path;
    char    *aux;

    i = 0;
    env =  malloc(sizeof(t_env));
    env->env = ft_calloc(sizeof(char *), ft_double_len(environ) + 1);
    while (environ[i])
    {
        env->env[i] = ft_strdup(environ[i]);
        if (ft_strnstr(environ[i], "PATH=", 5))
			aux = ft_strdup(environ[i]);
		i++;
    }
    path = ft_strchr(aux, '/');
    env->path = ft_split(path, ':');
    free(aux);
    return (env);
}

void get_struct_cmds(t_env *env, t_cmds *cmds, int i)
{
    cmds->env = env;
    cmds->num = 0;
    // cmds->pipe_fd = malloc(sizeof(int *) * i + 1);
    cmds->pipe_fd = malloc(sizeof(int *) * (i + 1));
    // ft_bzero(cmds->pipe_fd, 2 * i * sizeof(int));
    // printf("get-struct-cmds -> pipe -> %d\n", cmds->pipe_fd[0][0]);
    // cmds->cmds_argv = get_argv(def);
    // cmds->cmds_path = get_path(def, env->path, cmds->cmds_argv);
}

char *check_valid(char **path, char *cmd)
{
    int i;
    char *cmd_str;
    char *cmd_path;
    char *aux;

    i = 0;
    cmd_path = NULL;
    while(path[i])
    {
        aux = ft_strjoin(path[i], "/");
        cmd_str = ft_strjoin(aux, cmd);
        if(access(cmd_str, F_OK) == 0)
            cmd_path = ft_strdup(aux);
        free(aux);
        free(cmd_str);
        i++;
    }
    if(cmd_path == NULL)
    {
        access(cmd_path, F_OK);
        perror("");
    }
    return(cmd_path);
}

char    *get_path(t_def *def, char **path, char *argvs)
{
    int i;
    char *cmd_path;
    char **split_argv;

    i = 0;
    split_argv = NULL;
    cmd_path = NULL;
    while(def->argv[i])
    {
        if(def->type[i] == 4)
        {
            split_argv = ft_split(argvs, ' ');
            cmd_path = check_valid(path, split_argv[0]);
            break ;
        }
        i++;
    }
    ft_free_double(split_argv);
    return(cmd_path);
}

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

   


