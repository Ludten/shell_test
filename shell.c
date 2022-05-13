#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *line;
	size_t lline = 1024;
	ssize_t chars;
	int i;
	char **argv;
	char *token;
	pid_t childpid;

	line = malloc(sizeof(char) * lline);
	if (line == NULL)
		exit(1);

	while (1)
	{
		printf("$ ");
		chars = getline(&line, &lline, stdin); /*get command*/
		if (!chars)
			break;			/*if user hits ^D*/
		if (line[chars - 1] == '\n')
			line[chars - 1] = '\0';
		if (strcmp(line, "exit") == 0)
			break;

		argv = malloc(sizeof(char *) * 32);
		token = strtok(line, " ");
		i = 0;
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;

		childpid = fork();
		if (childpid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (childpid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

