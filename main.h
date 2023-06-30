#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(&x)
#define BUFF_SIZE 1024

/* FLAGS */
#define flag_minus 1
#define flag_plus 2
#define flag_zero 4
#define flag_hash 8
#define flag_space 16

/* SIZES */
#define size_long 2
#define size_short 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buf[], int flag, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_string(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_percent(va_list type, char buf[],
	int flag, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_binary(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_unsigned(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_octal(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_hexadecimal(va_list type, char buf[],
	int flag, int width, int precision, int size);
int print_hexa_upper(va_list type, char buf[],
	int flag, int width, int precision, int size);

int print_hexa(va_list type, char map[],
char buf[], int flag, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buf[],
	int flag, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list type, char buf[],
	int flag, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list type, char buf[],
	int flag, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list type, char buf[],
	int flag, int width, int precision, int size);

/* width handler */
int handle_write_char(char c, char buf[],
	int flag, int width, int precision, int size);
int write_number(int is_positive, int id, char buf[],
	int flag, int width, int precision, int size);
int write_num(int id, char bff[], int flag, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buf[], int id, int length,
	int width, int flag, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int id,
char buf[],
	int flag, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
