#include "main.h"

/**
 * aux_help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void aux_help_setenv(void)
{

    char *help_me = "setenv: setenv (const char *name, const char *value,";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "int replace)\n\t";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Add a new definition to the environment\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
/**
 * aux_help_env - Help information for the builtin env
 * Return: no return
 */
void aux_help_env(void)
{
    char *help_me = "env: env [option] [name=value] [command [args]]\n\t";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Print the enviroment of the shell.\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv(void)
{
    char *help_me = "unsetenv: unsetenv (const char *name)\n\t";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Remove an entry completely from the environment\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}

/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general(void)
{
    char *help_me = "^-^ bash, version 1.0(1)-release\n";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "These commands are defined internally.Type 'help' to see the list";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Type 'help name' to find out more about the function 'name'.\n\n ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "unsetenv [variable]\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */
void aux_help_exit(void)
{
    char *help_me = "exit: exit [n]\n Exit shell.\n";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Exits the shell with a status of N. If N is ommited, the exit";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "statusis that of the last command executed\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
