/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_signed.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/29 12:04:47 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 14:10:01 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function checks which char to use for width, then adjusts the width and
** len depending on diffrent factors and proceeds to print the width throug
** while_to_buf;
*/

void		conversion_signed_width(t_flags *conv, int len, long long nb)
{
	char	c;

	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO)
		c = '0';
	else
		c = ' ';
	if (conv->precision > len)
		len = conv->precision;
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS || (conv->flag & FLAG_SPACE)
		== FLAG_SPACE)
		len = len + 1;
	if (conv->precision >= conv->width)
		conv->width = 0;
	else if (conv->width > conv->precision && conv->precision != -1 &&
	len <= conv->precision)
	{
		if ((conv->flag & FLAG_PLUS) == FLAG_PLUS || (conv->flag & FLAG_SPACE)
		== FLAG_SPACE || nb < 0)
			conv->width--;
		conv->width = conv->width - conv->precision;
	}
	else if (conv->precision != 0)
		conv->width = conv->width - len;
	while_to_buf(conv, conv->width, c);
}

/*
** This function puts diffrent signs into string depending which flag is on
** or if nb is negative. The it adjusts size for the number of chars to be
** printed for precision and proceeds to print it at the function while_to_buf.
*/

void		putflags_and_precision_to_buf(t_flags *conv, int min)
{
	if (min)
	{
		conv->buf[conv->i] = '-';
		conv->i++;
	}
	else if ((conv->flag & FLAG_PLUS) == FLAG_PLUS)
	{
		conv->buf[conv->i] = '+';
		conv->i++;
	}
	else if ((conv->flag & FLAG_SPACE) == FLAG_SPACE)
	{
		conv->buf[conv->i] = ' ';
		conv->i++;
	}
	if (conv->i == (BUFF_SIZE_PF - 1))
		print_buf(conv);
}

void		precision_signed(t_flags *conv, int len, long long nb)
{
	int		size;

	if (nb < 0)
		len = len - 1;
	size = (conv->precision - len);
	while_to_buf(conv, size, '0');
}

/*
** This function redirect to a diffrent function with diffrent input
** depending on the value of nb.
*/

void		redirect(t_flags *conv, long long nb)
{
	if (nb >= 0)
	{
		putflags_and_precision_to_buf(conv, 0);
	}
	else
	{
		putflags_and_precision_to_buf(conv, 1);
	}
}

/*
** This function first gets the arg from va_arg, then manages the overflow,
** creates a string from nb, ad adapts the flags. Then it accounts for
**the exception of 0 precision with arg 0 otherwise processes it depending
** on if the FLAG_MIN is on;
*/

void		conversion_signed(t_flags *conv, va_list ap)
{
	long long		nb;
	int				len;

	nb = va_arg(ap, long long);
	nb = length_overflow_di(conv, nb);
	conv->str = ft_itoa_long(nb);
	clear_plus_space_flags2(conv, nb);
	len = ft_strlen(conv->str);
	if (conv->precision == 0 && nb == 0)
		conversion_signed_width(conv, len, nb);
	else if ((conv->flag & FLAG_MIN) == FLAG_MIN)
	{
		redirect(conv, nb);
		precision_signed(conv, len, nb);
		putnbr_to_buf(conv);
		conversion_signed_width(conv, len, nb);
	}
	else
		redirect2(conv, len, nb);
	free(conv->str);
}
