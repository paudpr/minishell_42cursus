#include "pruebas_bash.h"

/*
cat Makefile > salida | ls | cat << eof >> salida2
*/

void print_node(t_def *node, int i)
{
	int j;

	printf("\nNODE %d \n -------------------------- \n", i);
	j = 0;
	while(node->argv[j])
	{
		printf("argv[%d] -> %s\n", j, node->argv[j]);
		printf("%d\n", node->type[j]);
		j++;
	}
}

int *get_array(char *pipes)
{
	char **split;
	int i;
	int j;
	int *array;

	i = 0;
	split = ft_split(pipes, ' ');
	while(split[i])
		i++;
	array = malloc(sizeof(int) * i + 1);
	if(array == NULL)
		print_error("memory alloc");
	j = 0;
	while(j < i)
	{
		if(ft_strncmp("<<", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_HD;
			array[j + 1] = T_HD;
			j += 2;
		}
		else if(ft_strncmp("<", split[j], ft_strlen(split[j])) == 0)
		{
			array[j] = T_RIN;
			array[j + 1] = T_RIN;
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
			array[j] = T_ROUT;
			array[j + 1] = T_ROUT;
			j += 2;
		}
		else
		{
			array[j] = 4;
			j++;
		}
	}
	array[j] = '\0';
	return(array);
}


int main(int argc, char **argv)
{
	char **split;
	t_def	*def;
	int i;
	int j;

	if(argc != 2)
		print_error("Error. Arguments");

	split = ft_split(argv[1], '|');
	j = 0;
	while(split[j])
		j++;

	i = 0;
	while(i < j)
	{
		if(i == 0)
			def = ft_lstnew(split[i], get_array(split[i]));
		else
			ft_lstadd_back(&def, ft_lstnew(split[i], get_array(split[i])));
		i++;
	}

	// while(i)
	// {
	// 	print_node(def, i);
	// 	def = def->next;
	// 	i--;
	// }

	pipex(def)


}
