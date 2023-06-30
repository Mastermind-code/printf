#include "main.h"

void print_buf(char buf[], int *buff_id);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, print = 0, print_chars = 0;
	int flag, width, precision, size, buff_id = 0;
	va_list list;
	char buf[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buf[buff_id++] = format[i];
			if (buff_id == BUFF_SIZE)
				print_buf(buf, &buff_id);
			/* write(1, &format[i], 1);*/
			print_chars++;
		}
		else
		{
			print_buf(buf, &buff_id);
			flag = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			print = handle_print(format, &i, list, buf,
				flag, width, precision, size);
			if (print == -1)
				return (-1);
			print_chars += print;
		}
	}

	print_buf(buf, &buff_id);

	va_end(list);

	return (print_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buf(char buf[], int *buff_id)
{
	if (*buff_id > 0)
		write(1, &buf[0], *buff_id);

	*buff_id = 0;
}

