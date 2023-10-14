#include "shell.h"

/**
 * get_alias_value - Retrieves the value of an alias by its name.
 * @name: Name of the alias.
 * @shell: A pointer to the ShellState struct.
 * Return: Value of the alias or NULL if not found.
 */
char *get_alias_value(const char *name, ShellState *shell)
{
	Alias_t *tmp = shell->alias_head;

	while (tmp)
	{
		if (strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * print_alias - Prints the name and value of an alias.
 * @name: Name of the alias.
 * @shell: A pointer to the ShellState struct.
 */
void print_alias(const char *name, ShellState *shell)
{
	char *value = get_alias_value(name, shell);

	if (value)
		printf("%s='%s'\n", name, value);
}

/**
 * print_all_aliases - Prints all the aliases with their values.
 * @shell: A pointer to the ShellState struct.
 */
void print_all_aliases(ShellState *shell)
{
	Alias_t *tmp = shell->alias_head;

	while (tmp)
	{
		printf("%s='%s'\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

