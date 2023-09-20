#include "shell.h"

/**
 * write_history - creates a file, or appends to an existing file
 * @f: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *f)
{
	list_t *nd = NULL;

	ssize_t file_des;

	char *f_nm = get_history_file(f);

	if (!f_nm)
		return (-1);
	file_des = open(f_nm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_nm);
	if (file_des == -1)
		return (-1);
	for (nd = f->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, file_des);
		_putfd('\n', file_des);
	}
	_putfd(BUF_FLUSH, file_des);
	close(file_des);
	return (1);
}

/**
 * get_history_file - gets the history file
 * @f: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *f)
{
    char *directory;

	char *bfr;
    
	directory = _getenv(f, "HOME=");
	if (!directory)
		return (NULL);
	bfr = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!bfr)
		return (NULL);
	bfr[0] = 0;
	_strcpy(bfr, directory);
	_strcat(bfr, "/");
	_strcat(bfr, HIST_FILE);
	return (bfr);
}

/**
 * read_history - reads history from file
 * @f: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *f)
{
	int n, lst = 0, ln_cnt = 0;

	ssize_t file_des, rdlen, file_size = 0;

	struct stat states;

	char *bfr = NULL, *f_nm = get_history_file(f);

	if (!f_nm)
		return (0);

	file_des = open(f_nm, O_RDONLY);
	free(f_nm);
	if (file_des == -1)
		return (0);
	if (!fstat(file_des, &states))
		file_size = states.st_size;
	if (file_size < 2)
		return (0);
	bfr = malloc(sizeof(char) * (file_size + 1));
	if (!bfr)
		return (0);
	rdlen = read(file_des, bfr, file_size);
	bfr[file_size] = 0;
	if (rdlen <= 0)
		return (free(bfr), 0);
	close(file_des);
	for (n = 0; n < file_size; n++)
		if (bfr[n] == '\n')
		{
			bfr[n] = 0;
			build_history_list(f, bfr + lst, ln_cnt++);
			lst = n + 1;
		}
	if (lst != n)
		build_history_list(f, bfr + lst, ln_cnt++);
	free(bfr);
	f->histcount = ln_cnt;
	while (f->histcount-- >= HIST_MAX)
		delete_node_at_index(&(f->history), 0);
	renumber_history(f);
	return (f->histcount);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @f: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *f)
{
	list_t *node = f->history;

	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (f->histcount = n);
}

/**
 * build_history_list - adds entry to a history linked list
 * @f: Structure containing potential arguments. Used to maintain
 * @bfr: buffer
 * @ln_cnt: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *f, char *bfr, int ln_cnt)
{
	list_t *nd = NULL;

	if (f->history)
		nd = f->history;
	add_node_end(&nd, bfr, ln_cnt);

	if (!f->history)
		f->history = nd;
	return (0);
}
