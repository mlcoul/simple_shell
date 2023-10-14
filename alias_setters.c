#include "shell.h"

/**
 * init_alias_list - Initialize the alias list to NULL.
 * @shell: A pointer to the ShellState struct.
 */
void init_alias_list(ShellState *shell)
{
	shell->alias_head = NULL;
}

/**
 * set_alias - Sets a new alias or updates the value of an existing alias.
 * @name: Name of the alias.
 * @value: Value of the alias.
 * @shell: A pointer to the ShellState struct.
 */
void set_alias(const char *name, const char *value, ShellState *shell)
{
	Alias_t *new_alias = malloc(sizeof(Alias_t));

	if (!new_alias)
		return;

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = shell->alias_head;
	shell->alias_head = new_alias;
}

/**
 * free_aliases - Frees the alias list.
 * @shell: A pointer to the ShellState struct.
 */
void free_aliases(ShellState *shell)
{
	Alias_t *tmp;

	while (shell->alias_head)
	{
		tmp = shell->alias_head;
		shell->alias_head = shell->alias_head->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

