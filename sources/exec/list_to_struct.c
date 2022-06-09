#include "minishell.h"

t_env   *get_struct_env(char **environ)
{
    int  i;
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

void init_struct_cmds(t_env *env, t_cmds *cmds, int i)
{
    cmds->env = env;
    cmds->num = 0;
    cmds->pipe_fd = ft_calloc(sizeof(int *), i);
    cmds->fd_in = dup(STDIN_FILENO);
    cmds->fd_out = dup(STDOUT_FILENO);
}

char    *check_valid(char **path, char *cmd)
{
    int i;
    char *cmd_str;
    char *cmd_path;
    char *aux;

    i = 0;
    cmd_path = NULL;
    while (path[i])
    {
        aux = ft_strjoin(path[i], "/");
        cmd_str = ft_strjoin(aux, cmd);
        if (access(cmd_str, F_OK) == 0)
            cmd_path = ft_strdup(aux);
        free(aux);
        free(cmd_str);
        i++;
    }
    if (cmd_path == NULL)
    {
        access(cmd_path, F_OK);
        // perror("este es el error de accesss -> ");
    }
    return (cmd_path);
}

char    *get_path(t_def *def, char **path, char *argvs)
{
    int  i;
    char    *cmd_path;
    char    **split_argv;

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
    return (cmd_path);
}

char    *get_argv(t_def *def)
{
    int  i;
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

char    *get_relative_path(char *cmd)
{
    char    *chr;
    char    *path;
    int  len;

    chr = ft_strrchr(cmd, '/') + 1;
    len = ft_strlen(cmd) - ft_strlen(chr);
    path = ft_substr(cmd, 0, len);
    return (path);
}

char    *get_relative_argv(char *cmd)
{
    char    *chr;

    chr = NULL;
    if (ft_strrchr(cmd, '/') != NULL)
    {
        chr = ft_strdup(ft_strrchr(cmd, '/') + 1);
        free(cmd);
    }
    return (chr);
}

void    wait_process(t_def *def)
{
    int i;
    int *s;

    s = NULL;
    i = mini_lstsize(def);
    while (i)
    {
        waitpid(-1, s, 0);
        i--;
    }
}

char    *join_argv(char *cmd, char **split)
{
    char    *aux;
    char    *temp;
    int  i;

    i = 1;
    temp = cmd;
    while (i < ft_double_len(split))
    {
        aux = ft_strjoin(temp, " ");
        free(temp);
        temp = ft_strjoin(aux, split[i]);
        free(aux);
        free(split[i]);
        i++;
    }
    return (temp);
}

void    get_argv_path(t_def *def, t_cmds *cmds)
{
    char    **split_argv;
    char    *rel_cmd;

    cmds->cmds_argv = get_argv(def);
    split_argv = ft_split(cmds->cmds_argv, ' ');
    if(ft_strrchr(split_argv[0], '/') != NULL)
    {
        cmds->cmds_path = get_relative_path(split_argv[0]);
        rel_cmd = get_relative_argv(split_argv[0]);
        free(cmds->cmds_argv);
        cmds->cmds_argv = join_argv(rel_cmd, split_argv);
        free(split_argv);
    }
    else
    {
        cmds->cmds_path = get_path(def, cmds->env->path, cmds->cmds_argv);
        ft_free_double(split_argv);
    }
}
