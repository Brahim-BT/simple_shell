#include "main.h"

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @my_sigment: Signal handler
 */
void get_sigint(int my_sigment)
{
    (void)my_sigment;
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
