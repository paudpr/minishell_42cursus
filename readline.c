#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *line;

	line = readline("test > ");
	printf("%s\n", line);
	if(line != NULL)
		add_history(line);
	free(line);
	return(0);
}