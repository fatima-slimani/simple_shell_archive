#include "shell.h"

/**
 **_custom_memset - fills memory with a constant byte
 *@destination: the pointer to the memory area
 *@value: the byte to fill *destination with
 *@size: the amount of bytes to be filled
 *Return: (destination) a pointer to the memory area destination
 */
char *_custom_memset(char *destination, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		destination[i] = value;
	return (destination);
}

/**
 * free_string_array - frees an array of strings
 * @str_array: array of strings
 */
void free_string_array(char **str_array)
{
	char **arr = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(arr);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
