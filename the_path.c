#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @f: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *f, char *path)
{
    struct stat states;

    (void)f;
    if (!path || stat(path, &states))
        return (0);

    if (states.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_string: the PATH string
 * @strt: starting index
 * @stp: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_string, int strt, int stp)
{
    static char bfr[1024];
    int m = 0, o = 0;

    for (o = 0, m = strt; m < stp; m++)
        if (path_string[m] != ':')
            bfr[o++] = path_string[m];
    bfr[o] = 0;
    return (bfr);
}

/**
 * find_path - finds this cmd in the PATH string
 * @f: the info struct
 * @pathstr: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *f, char *pathstr, char *command)
{
    int m = 0, cursor_pos = 0;

    char *pth;

    if (!pathstr)
        return (NULL);
    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_cmd(f, command))
            return (command);
    }
    while (1)
    {
        if (!pathstr[m] || pathstr[m] == ':')
        {
            pth = dup_chars(pathstr, cursor_pos, m);
            if (!*pth)
                _strcat(pth, command);
            else
            {
                _strcat(pth, "/");
                _strcat(pth, command);
            }
            if (is_cmd(f, pth))
                return (pth);
            if (!pathstr[m])
                break;
            cursor_pos = m;
        }
        m++;
    }
    return (NULL);
}
