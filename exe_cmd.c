#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

/* Switch variables for separators */
#define NO_SEPARATOR '\0'
#define AND_LOGIC_SEP '&'
#define OR_LOGIC_SEP '|'
#define COMMAND_SEP ';'

int can_execute(command_t *command);
int is_custom_command(char *token);
int execute_normal_command(command_t *command, char *envp[], char *exec_name);
int execute_custom_command(command_t *command, char *envp[],
						   his_q_t *his_q, queue_t *q);

/**
 * execute_commands - Executes a queue of commands in FIFO order.
 * @his_q: History queue.
 * @command_q: Command queue.
 * @envp: Environment variables.
 * @exec_name: Name of the current executable.
 * Return: 1 if successful, 0 otherwise.
 */
int execute_commands(his_q_t *his_q, queue_t *command_q,
					 char *envp[], char *exec_name)
{
	command_t *cur_node = NULL;
	int run_com = 0, is_custom_com = 0;

	cur_node = dequeue(command_q);
	if (!cur_node || !envp)
		return (0);

	while (cur_node)
	{
		run_com = can_execute(cur_node);

		if (run_com)
		{
			is_custom_com = is_custom_command(cur_node->command[0]);
			if (is_custom_com >= 0)
				run_com = execute_custom_command(cur_node, envp, his_q, command_q);
			else
				run_com = execute_normal_command(cur_node, envp, exec_name);
		}

		if (cur_node->next)
			cur_node->next->prev_valid = (run_com == 0) ? 1 : 0;

		free_command(cur_node);
		cur_node = dequeue(command_q);
	}
	return (1);
}

/**
 * can_execute - Exec command

*/

int can_execute(command_t *command)
{
	int run_com = 0;

	switch (command->separator)
	{
	case NO_SEPARATOR:
		run_com = 1;
		break;
	case AND_LOGIC_SEP:
		run_com = (command->prev_valid) ? 1 : 0;
		break;
	case OR_LOGIC_SEP:
		run_com = (command->prev_valid) ? 0 : 1;
		break;
	case COMMAND_SEP:
		run_com = 1;
		break;
	}
	return (run_com);
}

int is_custom_command(char *token)
{
	char *customs[] = {"exit", "env", "setenv", "unsetenv",
					   "cd", "help", "history", NULL};
	int custom_i = 0, j = 0;

	if (!token)
		return (-1);

	while (customs[custom_i])
	{
		j = 0;
		while (token[j] && token[j] == customs[custom_i][j])
			j++;

		if (!customs[custom_i][j] && !token[j])
			return (custom_i);

		custom_i++;
	}
	return (-1);
}

int execute_custom_command(command_t *command, char *envp[],
						   his_q_t *his_q, queue_t *q)
{
	char *cmd_tok;
	int check_fnc = 0, exit_status = 0;

	if (!command)
		return (0);

	cmd_tok = command->command[0];
	if (!cmd_tok)
		return (0);

	switch (cmd_tok[0])
	{
	case 'e':
		if (cmd_tok[1] == 'x')
		{
			exit_status = _atoi(command->command[1]);
			free_command(command);
			exit_shell(his_q, q, exit_status, envp);
		}
		else if (cmd_tok[1] == 'n')
		{
			check_fnc = print_env(envp);
		}
		break;

	case 'h':
		if (cmd_tok[1] == 'i')
		{
			write_h_queue(his_q, STDOUT_FILENO);
		}
		break;
	}

	return ((check_fnc > 0) ? 1 : 0);
}

int execute_normal_command(command_t *command, char *envp[], char *exec_name)
{
	int pid, process_status, wait_err;
	char *file_w_path;

	file_w_path = get_file_path(command->command[0], envp);
	if (!file_w_path)
	{
		print_no_file_error(exec_name);
		return (98);
	}

	pid = fork();
	if (pid < 0)
		return (98);
	else if (pid == 0)
	{
		execve(file_w_path, command->command, envp);
		print_perm_denied(exec_name);
		exit(98);
	}
	else
	{
		wait_err = waitpid(pid, &process_status, 0);
		if (file_w_path != command->command[0])
			free(file_w_path);

		if (wait_err < 0)
			return (98);

		return (process_status);
	}
	return (98);
}

