#include "msh.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	while (TRUE)
	{
		char *shell = readline("$ ");
		add_history(shell);
	}

	return (0);
}
