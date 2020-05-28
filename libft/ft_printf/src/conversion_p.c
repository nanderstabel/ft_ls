/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_p.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/29 14:21:36 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/01 17:24:20 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function takes the width, corrects it with the string len of the string
** to be printed and prints as many spaces as possible, while checking if
** conv->buf isn't full.
*/

static void		conversion_width(t_flags *conv, int len)
{
	conv->width = conv->width - len;
	while (conv->width > 0)
	{
		conv->buf[conv->i] = ' ';
		conv->i++;
		conv->width--;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** This function copies the string from the argument of ft_printf to conv->buf
** and prints the conv->buf if it's full.
*/

static void		putstr_to_buf(t_flags *conv, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		conv->buf[conv->i] = str[i];
		conv->i++;
		i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** This function produces a string consisting a memory address (including
** "0x" notation at the front of the string), which is sent to putstr_to_buf.
** First the data is retrieved via va_arg into addr. If addr equals 0,
** this means the pointer is pointing to NULL, so the address is 0x0.
** However, if precision is set to zero, the final 0 is not included into
** the notation (so it is not necessary to use itoa_base).
** In all the other cases, addr is just the number, but this number needs
** to be converted into hexadecimal (using itoa_base with base 16).
** This number is stored into str. After that the "0x" notation is
** prepended to str. Depending on FLAG_MIN, str is sent to putstr_to_buf.
*/

void			conversion_p(t_flags *conv, va_list ap)
{
	long long	addr;
	char		*str;
	int			len;

	addr = va_arg(ap, long long);
	if (!addr && conv->precision == 0)
		str = ft_strnew(0);
	else
		str = ft_itoa_base(addr, 16);
	while ((int)ft_strlen(str) < conv->precision)
		str = ft_prepend(&str, "0");
	str = ft_prepend(&str, "0x");
	len = ft_strlen(str);
	if ((conv->flag & FLAG_MIN) == FLAG_MIN)
	{
		putstr_to_buf(conv, str);
		conversion_width(conv, len);
	}
	else
	{
		conversion_width(conv, len);
		putstr_to_buf(conv, str);
	}
	free(str);
}
