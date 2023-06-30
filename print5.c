#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buf: Buffer array to handle print
 * @flag:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buf[],
	int flag, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flag & flag_zero)
		padd = '0';

	buf[i++] = c;
	buf[i] = '\0';

	if (width > 1)
	{
		buf[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buf[BUFF_SIZE - i - 2] = padd;

		if (flag & flag_minus)
			return (write(1, &buf[0], 1) +
					write(1, &buf[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buf[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buf[0], 1));
	}

	return (write(1, &buf[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @id: char types.
 * @buf: Buffer array to handle print
 * @flag:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int id, char buf[],
	int flag, int width, int precision, int size)
{
	int length = BUFF_SIZE - id - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flag & flag_zero) && !(flag & flag_minus))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flag & flag_plus)
		extra_ch = '+';
	else if (flag & flag_space)
		extra_ch = ' ';

	return (write_num(id, buf, flag, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @id: Index at which the number starts on the buffer
 * @buf: Buffer
 * @flag: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int id, char buf[],
	int flag, int width, int prec,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && id == BUFF_SIZE - 2 && buf[id] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && id == BUFF_SIZE - 2 && buf[id] == '0')
		buf[id] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buf[--id] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (flag & flag_minus && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buf[--id] = extra_c;
			return (write(1, &buf[id], length) + write(1, &buf[1], i - 1));
		}
		else if (!(flag & flag_minus) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buf[--id] = extra_c;
			return (write(1, &buf[1], i - 1) + write(1, &buf[id], length));
		}
		else if (!(flag & flag_minus) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buf[--padd_start] = extra_c;
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[id], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buf[--id] = extra_c;
	return (write(1, &buf[id], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @id: Index at which the number starts in the buffer
 * @buf: Array of chars
 * @flag: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int id,
	char buf[],
	int flag, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - id - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && id == BUFF_SIZE - 2 && buf[id] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buf[--id] = '0';
		length++;
	}

	if ((flag & flag_zero) && !(flag & flag_minus))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buf[i] = padd;

		buf[i] = '\0';

		if (flag & flag_minus) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buf[id], length) + write(1, &buf[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buf[0], i) + write(1, &buf[id], length));
		}
	}

	return (write(1, &buf[id], length));
}

/**
 * write_pointer - Write a memory address
 * @buf: Arrays of chars
 * @id: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flag: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buf[], int id, int length,
	int width, int flag, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buf[i] = padd;
		buf[i] = '\0';
		if (flag & flag_minus && padd == ' ')/* Asign extra char to left of buffer */
		{
			buf[--id] = 'x';
			buf[--id] = '0';
			if (extra_c)
				buf[--id] = extra_c;
			return (write(1, &buf[3], i - 3) + write(1, &buf[id], length));
		}
		else if (!(flag & flag_minus) && padd == '0')/* extra char to left of padd */
		{
			buf[--id] = 'x';
			buf[--id] = '0';
			if (extra_c)
				buf[--id] = extra_c;
			return (write(1, &buf[3], i - 3) + write(1, &buf[id], length));
		}
		else if (!(flag & flag_minus) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buf[--padd_start] = extra_c;
			buf[1] = '0';
			buf[2] = 'x';
			return (write(1, &buf[padd_start], i - padd_start) +
				write(1, &buf[id], length - (1 - padd_start) - 2));
		}
	}
	buf[--id] = 'x';
	buf[--id] = '0';
	if (extra_c)
		buf[--id] = extra_c;
	return (write(1, &buf[id], BUFF_SIZE - id - 1));
}
