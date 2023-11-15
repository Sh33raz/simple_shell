#include “shell.h”

int main(void)
{
	while (1)
	{
		printf("$ ");
		char stat[1024];

		if (fgets(stat, sizeof(stat), stdin) == NULL)
		{
			printf("\n");
			break;
		}
		stat[strcspn(stat, "\n")] = 0;

		char *argzz[1024];
		int i = 0;
		char *tkn = strtok(stat, " ");

		while (tkn != NULL)
		{
			argzz[i++] = tkn;
			tkn = strtok(NULL, " ");
		}
		argzz[i] = NULL;
		pid_t pid = fork();

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
