#include "shell.h"

int main(void)
{
	char stat[1024];
	char *argzz[1024];
	char *tkn = strtok(stat, " ");
	pid_t pid = fork();
	int i = 0;

	while (1)
	{
		printf("$ ");

		if (fgets(stat, sizeof(stat), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		stat[strcspn(stat, "\n")] = 0;

		while (tkn != NULL)
		{
			argzz[i++] = tkn;
			tkn = strtok(NULL, " ");
		}
		argzz[i] = NULL;

		if (pid == 0)
		{
			if (execvp(argzz[0], argzz) == -1)
			{
				perror("Error");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
