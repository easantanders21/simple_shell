#include "main.h"
/**
 * main - main
 *
 * @argc: unused
 * @argv: unused
 * @env: unused
 * Return: Always 0
 */
int main(int argc, char **argv, char **env)
{
	ssize_t status_read, tty = 1;
	char *line = NULL, *cpline = NULL, **args = NULL, *putline;
	int status_execve, status, status_trans;
	pid_t pid;
	size_t lineSize = 0;
	args_t *list = NULL;

	UNUSED(env), UNUSED(argv), UNUSED(argc);
	isatty(STDIN_FILENO) == 0 ? tty = 0 : tty;
	do {
		tty == 1 ? write(STDOUT_FILENO, "($) ", 4) : tty;
		fflush(stdin), status_read = getline(&line, &lineSize, stdin);
		if (status_read == EOF)
		{ free(line);
			break; }
		if (*line == '\n' || *line == '\t' || *line == ' ')
			continue;
		_strdup(line, &cpline),	putline = cpline;
		create_list(cpline, &putline, &list), status_trans = built_in(&list);
		if (status_trans == 0)
		{_free_list(&list), free(putline);
			continue; }
		if (status_trans == 2)
		{_free_list(&list), free(putline);
			continue; }
		args = transform(&list);
		if (args == NULL)
			return (-1);
		pid = fork();
		if (pid == 1)
			return (-1);
		else if (pid == 0)
		{
			status_execve = execve(args[0], args, env), exit(status_execve);
		} else
			wait(&status), _free_list(&list), free(args);
		free(putline), free(line), list = NULL, line = NULL;
		if (status_trans == 3)
			free(list->arg);
	} while (1);
	return (0);
}
