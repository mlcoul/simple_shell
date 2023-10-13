#ifndef SHELL_H
#define SHELL_H

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>


void disp_prompt(void);
void mo_print(const char *msg);
void read_cmd(char *command, size_t size);
void exec_command(const char *command);

#endif /* SHELL_H */

