/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_signed_utillities.c                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/01 18:10:10 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 14:06:39 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function cleares the flags FLAG_PLUS and FLAG_SPACE if they are
** activated.
*/

void		clear_plus_space_flags(t_flags *conv)
{
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS)
		conv->flag ^= FLAG_PLUS;
	if ((conv->flag & FLAG_SPACE) == FLAG_SPACE)
		conv->flag ^= FLAG_SPACE;
}

/*
** This function adapts the flags depending n the combination they come in.
*/

void		clear_plus_space_flags2(t_flags *conv, long long nb)
{
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS && (conv->flag & FLAG_ZERO) ==
	FLAG_ZERO && conv->precision != -1)
		conv->flag ^= FLAG_ZERO;
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && (conv->flag & FLAG_MIN) ==
	FLAG_MIN && conv->precision == -1)
		conv->flag ^= FLAG_ZERO;
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && conv->precision != -1)
		conv->flag ^= FLAG_ZERO;
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS && (conv->flag & FLAG_SPACE) ==
	FLAG_SPACE)
		conv->flag ^= FLAG_SPACE;
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS && nb < 0)
		conv->flag ^= FLAG_PLUS;
}

/*
** this functions puts specifies char into conv->buf while checking if its full
*/

void		while_to_buf(t_flags *conv, int number, char c)
{
	while (number > 0)
	{
		conv->buf[conv->i] = c;
		conv->i++;
		number--;
		if (conv->i == (BUFF_SIZE_PF - 1))
			print_buf(conv);
	}
}

/*
** This function copies the string to the buf while checking if conv->buf
** is full.
*/

void		putnbr_to_buf(t_flags *conv)
{
	int		i;

	i = 0;
	if (conv->str[i] == '-')
		i = 1;
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
** This function checks which flag is on and typecasts for overfow
*/

long long	length_overflow_di(t_flags *conv, long long nb)
{
	if ((conv->flag & FLAG_L) == FLAG_L)
		nb = (long)nb;
	else if ((conv->flag & FLAG_H) == FLAG_H)
		nb = (short)nb;
	else if ((conv->flag & FLAG_HH) == FLAG_HH)
		nb = (signed char)nb;
	else if ((conv->flag & FLAG_LL) != FLAG_LL)
		nb = (int)nb;
	return (nb);
}
