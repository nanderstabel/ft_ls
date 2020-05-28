/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_signed_utillities2.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/01 21:15:08 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 14:07:51 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function directs the operation of processing
*/

void	redirect2(t_flags *conv, int len, long long nb)
{
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && conv->precision == -1)
	{
		redirect(conv, nb);
		conversion_signed_width(conv, len, nb);
		precision_signed(conv, len, nb);
		putnbr_to_buf(conv);
	}
	else
	{
		conversion_signed_width(conv, len, nb);
		redirect(conv, nb);
		precision_signed(conv, len, nb);
		putnbr_to_buf(conv);
	}
}
