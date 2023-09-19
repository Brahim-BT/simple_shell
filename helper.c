#include "main.h"

/**
 * aux_help_env - this functioni will Help information for the builtin env for us.
 * Return: void
 */
void aux_help_env(void)
{
	char *hlp = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));

}
/**
 * aux_help_setenv - this function will Help information for the builtin setenv for us.
 * Return: void
 */
void aux_help_setenv(void)
{
	char *hlp = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "int replace)\n\t";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * aux_help_unsetenv - this function will help information for the builtin unsetenv for us.
 * Return: void
 */
void aux_help_unsetenv(void)
{
	char *hlp = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}


/**
 * aux_help_general - this function will Entry point for help information for the help builtin for us.
 * Return: void.
 */
void aux_help_general(void)
{
	char *hlp = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "unsetenv [variable]\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
/**
 * aux_help_exit - this function will help information fot the builtin exit for us.
 * Return: no return
 */
void aux_help_exit(void)
{
	char *hlp = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
	hlp = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, hlp, _strlen(hlp));
}
