/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_c.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/24 12:36:39 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 13:52:01 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function checks which char to print, corrects the width with the size
** of the char to be printed and prints as many as possible, while
** checking if conv->buf isn't full.
*/

static void		conversion_width(t_flags *conv, int chr)
{
	char c;

	c = ' ';
	if (chr == -1 && conv->width == -1)
		c = '0';
	if (chr == -1 && (conv->flag & FLAG_ZERO) == FLAG_ZERO)
		c = '0';
	conv->width = conv->width - 1;
	while (conv->width > 0)
	{
		conv->buf[conv->i] = c;
		conv->i++;
		conv->width--;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** This function copies the char from the argument of ft_printf to conv->buf
** and prints the conv->buf if it's full.
*/

static void		putchar_to_buff(t_flags *conv, char chr)
{
	conv->buf[conv->i] = chr;
	conv->i++;
	if (conv->i == (BUFF_SIZE_PF - 1))
		print_buf(conv);
}

/*
** This function takes the char to be printed from conv->specifier.
** If the chr is a 0, it will change the chr to -1. Then
** it checks if the minus flag is on. If so it first goes to func
** putchar_to_buff and after it's done goes to conversion_width.
** If the minus flag is not on, it irst goes to func
** conversion_width and after it's done goes to putchar_to_buff.
*/

void			conversion_c(t_flags *conv, va_list ap)
{
	int		chr;

	chr = va_arg(ap, int);
	if (chr == 0)
	{
		chr = -1;
		conv->delim = 1;
	}
	if ((FLAG_MIN & conv->flag) == FLAG_MIN)
	{
		putchar_to_buff(conv, chr);
		conversion_width(conv, chr);
	}
	else
	{
		conversion_width(conv, chr);
		putchar_to_buff(conv, chr);
	}
}
