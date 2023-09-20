#include "shell.h"

/**
 * input_buf_custom - buffers chained commands
 * @info_custom: parameter struct
 * @buf_custom: address of buffer
 * @len_custom: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf_custom(shell_info_t *info_custom, char **buf_custom, size_t *len_custom)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len_custom) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf_custom);
		*buf_custom = NULL;
		signal(SIGINT, sigintHandlerCustom);
#if USE_GETLINE
		r = getline(buf_custom, &len_p, stdin);
#else
		r = _getline_custom(info_custom, buf_custom, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf_custom)[r - 1] == '\n')
			{
				(*buf_custom)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info_custom->linecount_flag = 1;
			remove_comments_custom(*buf_custom);
			build_history_list_custom(info_custom, *buf_custom, info_custom->histcount++);
			/* if (_strchr(*buf_custom, ';')) is this a command chain? */
			{
				*len_custom = r;
				info_custom->cmd_buf = buf_custom;
			}
		}
	}
	return (r);
}

/**
 * get_input_custom - gets a line minus the newline
 * @info_custom: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input_custom(shell_info_t *info_custom)
{
	static char *buf_custom; /* the ';' command chain buffer */
	static size_t i_custom, j_custom, len_custom;
	ssize_t r = 0;
	char **buf_p_custom = &(info_custom->arg), *p_custom;

	_putchar(BUF_FLUSH);
	r = input_buf_custom(info_custom, &buf_custom, &len_custom);
	if (r == -1) /* EOF */
		return (-1);
	if (len_custom) /* we have commands left in the chain buffer */
	{
		j_custom = i_custom;			  /* init new iterator to current buf position */
		p_custom = buf_custom + i_custom; /* get pointer for return */

		check_chain_custom(info_custom, buf_custom, &j_custom, i_custom, len_custom);
		while (j_custom < len_custom) /* iterate to semicolon or end */
		{
			if (is_chain_custom(info_custom, buf_custom, &j_custom))
				break;
			j_custom++;
		}

		i_custom = j_custom + 1;	/* increment past nulled ';'' */
		if (i_custom >= len_custom) /* reached end of buffer? */
		{
			i_custom = len_custom = 0; /* reset position and length */
			info_custom->cmd_buf_type = CMD_NORM;
		}

		*buf_p_custom = p_custom;	/* pass back pointer to current command position */
		return (_strlen(p_custom)); /* return length of current command */
	}

	*buf_p_custom = buf_custom; /* else not a chain, pass back buffer from _getline_custom() */
	return (r);					/* return length of buffer from _getline_custom() */
}

/**
 * read_buf_custom - reads a buffer
 * @info_custom: parameter struct
 * @buf_custom: buffer
 * @i_custom: size
 *
 * Return: r
 */
ssize_t read_buf_custom(shell_info_t *info_custom, char *buf_custom, size_t *i_custom)
{
	ssize_t r = 0;

	if (*i_custom)
		return (0);
	r = read(info_custom->readfd, buf_custom, READ_BUF_SIZE);
	if (r >= 0)
		*i_custom = r;
	return (r);
}

/**
 * _getline_custom - gets the next line of input from STDIN
 * @info_custom: parameter struct
 * @ptr_custom: address of pointer to buffer, preallocated or NULL
 * @length_custom: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline_custom(shell_info_t *info_custom, char **ptr_custom, size_t *length_custom)
{
	static char buf_custom[READ_BUF_SIZE];
	static size_t i_custom, len_custom;
	size_t k_custom;
	ssize_t r = 0, s = 0;
	char *p_custom = NULL, *new_p_custom = NULL, *c_custom;

	p_custom = *ptr_custom;
	if (p_custom && length_custom)
		s = *length_custom;
	if (i_custom == len_custom)
		i_custom = len_custom = 0;

	r = read_buf_custom(info_custom, buf_custom, &len_custom);
	if (r == -1 || (r == 0 && len_custom == 0))
		return (-1);

	c_custom = _strchr(buf_custom + i_custom, '\n');
	k_custom = c_custom ? 1 + (unsigned int)(c_custom - buf_custom) : len_custom;
	new_p_custom = _realloc(p_custom, s, s ? s + k_custom : k_custom + 1);
	if (!new_p_custom) /* MALLOC FAILURE! */
		return (p_custom ? free(p_custom), -1 : -1);

	if (s)
		_strncat(new_p_custom, buf_custom + i_custom, k_custom - i_custom);
	else
		_strncpy(new_p_custom, buf_custom + i_custom, k_custom - i_custom + 1);

	s += k_custom - i_custom;
	i_custom = k_custom;
	p_custom = new_p_custom;

	if (length_custom)
		*length_custom = s;
	*ptr_custom = p_custom;
	return (s);
}

/**
 * sigintHandlerCustom - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandlerCustom(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
