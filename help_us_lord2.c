#include "main.h"

/**
 * aux_help - Help information for the builtin help.
 * Return: no return
 */
void aux_help(void)
{
    char *help_me = "help: help [-dms] [pattern ...]\n";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "\tDisplay information about builtin commands.\n ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "Displays brief summaries of builtin commands.\n";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
/**
 * aux_help_alias - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_alias(void)
{
    char *help_me = "alias: alias [-p] [name[=value]...]\n";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "\tDefine or display aliases.\n ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
/**
 * aux_help_cd - Help information for the builtin alias.
 * Return: no return
 */
void aux_help_cd(void)
{
    char *help_me = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

    write(STDOUT_FILENO, help_me, _strlen(help_me));
    help_me = "\tChange the shell working directory.\n ";
    write(STDOUT_FILENO, help_me, _strlen(help_me));
}
