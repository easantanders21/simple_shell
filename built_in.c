#include "main.h"
/**
 * envi - list of environment variables
 *
 * Return: list
 */
int envi(void)
{
	size_t i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (0);
}
/**
 * exitt - end of program
 * @lista: lista
 *
 * Return: exit
 */
int exitt(args_t **lista)
{
	free_list(lista);
	free(line);
	free(pl);
	if (count > 1)
		salida = 2;
	exit(salida);
}
