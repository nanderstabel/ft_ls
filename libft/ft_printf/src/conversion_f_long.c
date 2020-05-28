/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f_long.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/11 14:18:32 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 11:52:35 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Function to take account for special cases.
*/

int				special_nb_long(t_float *dbl)
{
	if ((long double)1.0 / dbl->nb_long == (-1.0 / 0.0))
	{
		dbl->output = ft_strdup("-0.0");
		dbl->sign = 1;
	}
	else if (dbl->nb_long == -1.0 / 0.0)
		dbl->output = ft_strdup("-inf");
	else if (dbl->nb_long == 1.0 / 0.0)
		dbl->output = ft_strdup("inf");
	else if (dbl->nb_long != dbl->nb_long)
		dbl->output = ft_strdup("nan");
	else
		return (0);
	return (1);
}

/*
** Conversion for long doubles.
*/

void			conversion_f_long(t_flags *conv, va_list ap, t_float *dbl)
{
	dbl->nb_long = va_arg(ap, long double);
	set_params(conv, dbl);
	if (!special_nb_long(dbl))
		get_tfloat_long(dbl);
	if (dbl->output[0] == '-')
		clear_plus_space_flags(conv);
	dbl->precision = (conv->precision == -1) ? 6 : conv->precision;
	conversion_f_direct(conv, dbl);
}
