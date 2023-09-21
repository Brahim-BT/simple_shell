#include "main.h"

/**
 * aux_help - Help information for the builtin help.
 * Return: no return
 */
void aux_help(void)
{
	char *may_be_some_help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}
/**
 * aux_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_alias(void)
{
	char *may_be_some_help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}
/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_cd(void)
{
	char *may_be_some_help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}
