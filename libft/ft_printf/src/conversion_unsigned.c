/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_unsigned.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/30 13:09:52 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/01 22:48:32 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function copies the string to buf.
*/

static void					putstr_to_buf(t_flags *conv)
{
	int	i;

	i = 0;
	while (conv->str[i] != '\0')
	{
		conv->buf[conv->i] = conv->str[i];
		conv->i++;
		i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
			print_buf(conv);
	}
}

/*
** This function first checks if the correct flags are on and off, then it
** prepends the neccesary '0's first filling all the width and later on all
** the '0's specified through precision.
*/

static void					zero_precision(t_flags *conv)
{
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && \
		(conv->flag & FLAG_MIN) != FLAG_MIN)
	{
		if (conv->precision != -1)
			while ((conv->width - conv->precision) > (int)ft_strlen(conv->str))
				conv->str = ft_prepend(&conv->str, "0");
		else
			while (conv->width > (int)ft_strlen(conv->str))
				conv->str = ft_prepend(&conv->str, "0");
	}
	while (conv->precision > (int)ft_strlen(conv->str))
		conv->str = ft_prepend(&conv->str, "0");
	if (conv->precision == 0 && conv->str[0] == '0' && \
		!(conv->specifier == 'o' && (conv->flag & FLAG_HASH) == FLAG_HASH))
		conv->str = ft_replace(&conv->str, "", 0, 1);
}

/*
** This function first checks for the hash flag, then it replaces the first 2
** chars if FLAG_ZERO is on or prepends 1 leading '0' with specifier 'o'.
** Then it checks if the width has to be filled with spaces and prepends or
** appends those.
*/

static void					hash_width(t_flags *conv, unsigned long long nb)
{
	int		len;
	char	*temp;

	if ((conv->flag & FLAG_HASH) == FLAG_HASH && nb != 0)
	{
		if (conv->specifier == 'x' || conv->specifier == 'X')
		{
			if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && \
			(int)ft_strlen(conv->str) == conv->width)
				conv->str = ft_replace(&conv->str, "", 0, 2);
			conv->str = ft_prepend(&conv->str, "0x");
		}
		if (conv->specifier == 'o' && conv->str[0] != '0')
			conv->str = ft_prepend(&conv->str, "0");
	}
	len = conv->width - ft_strlen(conv->str);
	if (len > 0)
	{
		temp = ft_strnewfill(len, ' ');
		if ((conv->flag & FLAG_MIN) == FLAG_MIN)
			conv->str = ft_append(&conv->str, temp);
		else
			conv->str = ft_prepend(&conv->str, temp);
		free(temp);
	}
}

/*
** This function typecasts nb to the specified data types to create an
** overflow.
*/

static unsigned long long	overflow(t_flags *conv, unsigned long long nb)
{
	if ((conv->flag & FLAG_L) == FLAG_L)
		nb = (unsigned long)nb;
	else if ((conv->flag & FLAG_H) == FLAG_H)
		nb = (unsigned short)nb;
	else if ((conv->flag & FLAG_HH) == FLAG_HH)
		nb = (unsigned char)nb;
	else if ((conv->flag & FLAG_LL) != FLAG_LL)
		nb = (unsigned int)nb;
	return (nb);
}

/*
** This function gets the nb from va_arg, manages the overflow, initiates
** conv->str and points it to the return value of itoa, depending on which
** specifier is active. Then the precision is managed and after that the
** width. Lastly the string is converted to uppercases if so specified and
** copied to the buf.
*/

void						conversion_unsigned(t_flags *conv, va_list ap)
{
	unsigned long long	nb;

	nb = va_arg(ap, unsigned long long);
	nb = overflow(conv, nb);
	if (nb == 0)
		conv->str = ft_strdup("0");
	if (conv->specifier == 'u' && nb != 0)
		conv->str = ft_itoa_base(nb, 10);
	else if (conv->specifier == 'o')
	{
		if (nb == 0)
			free(conv->str);
		conv->str = ft_itoa_base(nb, 8);
	}
	else if ((conv->specifier == 'x' || conv->specifier == 'X') && nb != 0)
		conv->str = ft_itoa_base(nb, 16);
	zero_precision(conv);
	hash_width(conv, nb);
	if (conv->specifier == 'X')
		new_str(conv);
	putstr_to_buf(conv);
	free(conv->str);
}
