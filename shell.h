#ifndef SHELL_H
#define SHELL_H

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

/**
 * struct Alias - a structure for aliases
 * @name: alias name
 * @value: alias value
 * @next: pointer to the next alias
 */
typedef struct Alias
{
    char *name;
    char *value;
    struct Alias *next;
} Alias_t;

/* Global shell state structure */
typedef struct shell_state {
    Alias_t *alias_head;
    int last_exit_status; /* Store the exit status of the last command */
    /* other global states can be added here in the future */
} ShellState;

/* Function Prototypes for your shell */
void disp_prompt(void);
void mo_print(const char *msg);
void read_cmd(char *command, size_t size);
ssize_t mo_getline(char **lineptr, size_t *n, FILE *stream);
char *mo_strsep(char **stringp, const char *delim);
int handle_setenv(char **args);
int handle_unsetenv(char **args);
int handle_cd(char **args);
void execute_commands(char *line, ShellState *shell);
int exec_command(char *command, ShellState *shell);
char **mo_tokenize(char *command);
char **split_commands(char *command);
char **get_operators(char *command);
void handle_exit(char **args, ShellState *shell);
int execute_single_command(char *command, ShellState *shell);

/* Function Prototypes for alias */
void init_alias_list(ShellState *shell);
void handle_alias(char **args, ShellState *shell);
void set_alias(const char *name, const char *value, ShellState *shell);
char *get_alias_value(const char *name, ShellState *shell);
void print_alias(const char *name, ShellState *shell);
void print_all_aliases(ShellState *shell);
void free_aliases(ShellState *shell);

/* Function Prototypes for string operations */
char *str_replace(const char *orig, const char *rep, const char *with);

char *replace_variable(char *input, char *variable, char *replacement);
char *handle_replacements(char *input, ShellState *shell);

void strip_comments(char *cmd);



#endif /* SHELL_H */

