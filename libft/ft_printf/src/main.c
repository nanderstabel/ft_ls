/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 12:56:21 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 13:03:08 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function checks for the flags and if it finds any, activates
** them.
*/

void		flags(t_flags *conv, const char **format)
{
	while (**format == '-' || **format == '+' || **format == '0' \
		|| **format == '#' || **format == ' ')
	{
		if (**format == '#')
			conv->flag |= FLAG_HASH;
		else if (**format == '-')
			conv->flag |= FLAG_MIN;
		else if (**format == '+')
			conv->flag |= FLAG_PLUS;
		else if (**format == ' ')
			conv->flag |= FLAG_SPACE;
		else if (**format == '0')
			conv->flag |= FLAG_ZERO;
		(*format)++;
	}
}

/*
** This function checks for the width flags and if it finds any,
** activates them, then sends it to function main_precision and checks
** for precision flags.
*/

void		width_precision(t_flags *conv, const char **format, va_list ap)
{
	if (**format == '*')
	{
		conv->width = va_arg(ap, int);
		(*format)++;
		if (conv->width < 0)
		{
			conv->flag |= FLAG_MIN;
			conv->width = conv->width * -1;
		}
	}
	else if (ft_isdigit(**format) == 1)
	{
		conv->width = ft_atoi(*format);
		while (ft_isdigit(**format) == 1)
			(*format)++;
	}
	main_precision(conv, format, ap);
}

/*
** This function checks for the length flags and if it finds any, activates
** them.
*/

void		length(t_flags *conv, const char **format)
{
	if (**format == 'l' && *(*format + 1) == 'l')
	{
		conv->flag |= FLAG_LL;
		(*format) = (*format) + 2;
	}
	else if (**format == 'l')
	{
		conv->flag |= FLAG_L;
		(*format)++;
	}
	else if (**format == 'h' && *(*format + 1) == 'h')
	{
		conv->flag |= FLAG_HH;
		(*format) = (*format) + 2;
	}
	else if (**format == 'h')
	{
		conv->flag |= FLAG_H;
		(*format)++;
	}
	else if (**format == 'L')
	{
		conv->flag |= FLAG_L_UP;
		(*format)++;
	}
}

/*
** This function first checks if there are two '%' signs. If so it puts one in
** the buf. if not it sends the string to diffrent functions to activate flags,
** width, precision, length and caputres the specifier. After this it
** sends the struct and "ap" to the function main_conversion for further
** processing and clears the struct once it's done with main_conversion.
*/

void		conversion(t_flags *conv, const char **format, va_list ap)
{
	if (*(*format + 1) == '%')
	{
		conv->buf[conv->i] = '%';
		conv->i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
			print_buf(conv);
		(*format) = (*format) + 2;
	}
	else
	{
		arg_index(conv, format, ap);
		if (**format == '\0')
			return ;
		flags(conv, format);
		width_precision(conv, format, ap);
		length(conv, format);
		conv->specifier = **format;
		(*format)++;
		main_conversion(conv, ap);
		clear_struct(conv);
	}
}

/*
** This function mallocs the struct, initiates the varibles inside the struct
** then loops through the whole string format until everything is read. If he
** finds a '{' it goes to a function to activate colors if nessecary. It a '%'
** is found he sends the string plus struct to the function 'conversion'
** for further processing.
*/

int			ft_printf(const char *format, ...)
{
	t_flags		*conv;
	va_list		ap;
	int			ret;

	conv = malloc(sizeof(t_flags));
	initiate_struct(conv);
	va_start(ap, format);
	va_copy(conv->start, ap);
	while (*format)
	{
		if (*format != '%')
			no_conversion(conv, &format);
		else
			conversion(conv, &format, ap);
	}
	print_buf(conv);
	ret = conv->num;
	free(conv);
	va_end(ap);
	return (ret);
}
