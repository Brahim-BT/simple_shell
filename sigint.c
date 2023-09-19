#include "main.h"

/**
 * get_sigint - this function will Handle the crtl + c call in prompt for us.
 * @sig: this will handle the signal
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
