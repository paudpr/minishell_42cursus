#include "pruebas_bash.h"

/*
cat Makefile > salida | ls | cat << eof >> salidaT_RIN
*/


void print_node(t_def *node, int i)
{
	int j;

	printf("NODE %d \n -------------------------- \n", i);
	j = 0;
	while(node->argv[j])
	{
		printf("argv[%d] -> %s\n", j, node->argv[j]);
		printf("%d\n", node->type[j]);
		j++;
	}
}


int main(int argc, char **argv)
{
	char **split;
	t_def	*def;
	int i;
	int array0[] = {T_CMD, T_ARG, T_RIN, T_RIN};
	int array1[] = {T_CMD};
	int arrayT_RIN[] = {T_CMD, T_HD, T_RIN, T_APP, T_RIN};

	if(argc != T_RIN)
		print_error("Error. Arguments");

	split = ft_split(argv[1], '|');
	def = ft_lstnew(split[0], array0);
	ft_lstadd_back(&def, ft_lstnew(split[1], array1));
	ft_lstadd_back(&def, ft_lstnew(split[T_RIN], arrayT_RIN));

	i = ft_lstsize(def);
	while(i)
	{
		print_node(def, i);
		def = def->next;
		i--;
	}
	

}
