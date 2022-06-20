#include "minishell.h"

/*
"cat Makefile > salida | ls | cat << eof >> salida2"
*/

void print_node(t_def **node, int i)
{
	int j;
	t_def *copy;

	copy = *node;
	while(i)
	{
		printf("\nNODE %d\n -------------------------- \n", i);
		j = 0;
		while(copy->argv[j])
		{
			printf("argv[%d] -> %s\n", j, copy->argv[j]);
			printf("type -> %d\n", copy->type[j]);
			printf("----\n");
			j++;
		}
		copy = copy->next;
		i--;	
	}
	printf("\n");
}

int *get_array(char *pipes)
{
	char **split;
	int i;
	int j;
	int *array = NULL;

	split = ft_split(pipes, ' ');
	i = ft_double_len(split);
	array = ft_calloc(sizeof(int), i + 1);
	if(array == NULL)
		print_error("Error de memoria en get_array");
	j = 0;
	while(j < i)
	{
		if(ft_strncmp("<", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_RIN;
			array[j + 1] = T_RIN;
			j += 2;
		}
		else if (ft_strncmp("<<", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_HD;
			array[j + 1] = T_HD;
			j += 2;
		}
		else if(ft_strncmp(">", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_ROUT;
			array[j + 1] = T_ROUT;
			j += 2;
		}
		else if(ft_strncmp(">>", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_APP;
			array[j + 1] = T_APP;
			j += 2;
		}
		else
		{
			array[j] = 4;
			j++;
		}
	}
	ft_free_double(split);
	return(array);
}

void get_list(t_def **def, char *argv)
{
    int i;
    int j;
    char **split;

    split = ft_split(argv, '|');
    i = ft_double_len(split);
    j = 0;
    while(j < i)
    {
        if(j == 0)
            *def = mini_lstnew(split[j], get_array(split[j]));
        else
            mini_lstadd_back(def, mini_lstnew(split[j], get_array(split[j])));
        j++;
    }
    ft_free_double(split);
}

void check_leaks()
{
	printf("\n");
	system("leaks -q minishell");
}