/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f_utillities3.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/01 21:59:19 by mgross         #+#    #+#                */
/*   Updated: 2019/06/01 22:14:19 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	zero_space(t_flags *conv)
{
	int c;

	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && (conv->flag & FLAG_MIN)
		!= FLAG_MIN)
		c = '0';
	else
		c = ' ';
	return (c);
}

char	plus_min(t_flags *conv)
{
	char d;

	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS)
	{
		d = '+';
		conv->width--;
	}
	else
		d = '-';
	return (d);
}

void	f_rounding_up(t_float *dbl, int rounding)
{
	int		temp;

	temp = rounding;
	while (dbl->output[rounding + dbl->precision] == '9' &&
	(rounding + dbl->precision) >= temp)
	{
		dbl->output[rounding + dbl->precision] = '0';
		rounding--;
	}
	if ((rounding + dbl->precision) <= 0)
		dbl->output = ft_prepend(&dbl->output, "1");
	else
		dbl->output[rounding + dbl->precision]++;
}
