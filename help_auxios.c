#include "main.h"

/**
 * aux_help_env - Help information for the builtin env
 * Return: no return
 */
void aux_help_env(void)
{
	char *may_be_some_help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));

}
/**
 * aux_help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void aux_help_setenv(void)
{

	char *may_be_some_help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "int replace)\n\t";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}
/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv(void)
{
	char *may_be_some_help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}


/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general(void)
{
	char *may_be_some_help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
	may_be_some_help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, may_be_some_help, _strlen(may_be_some_help));
}
/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */
void aux_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
