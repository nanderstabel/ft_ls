/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_conversion.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 11:42:30 by mgross         #+#    #+#                */
/*   Updated: 2019/06/01 22:14:11 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** These functions redirect to the correct function depending on the specifier,
** for further processing.
*/

static void		main_conversion2(t_flags *conv, va_list ap)
{
	t_float		*dbl;

	dbl = NULL;
	if (conv->specifier == 'f' && (conv->flag & FLAG_L_UP) == FLAG_L_UP)
	{
		dbl = malloc(sizeof(t_float));
		conversion_f_long(conv, ap, dbl);
		clear_tfloat(dbl);
	}
	else if (conv->specifier == 'f')
	{
		dbl = malloc(sizeof(t_float));
		conversion_f(conv, ap, dbl);
		clear_tfloat(dbl);
	}
	else if (conv->specifier == 'e' && (conv->flag & FLAG_L_UP) == FLAG_L_UP)
		conversion_e_long(conv, ap);
	else if (conv->specifier == 'e')
		conversion_e(conv, ap);
	else
	{
		conversion_c_special(conv);
	}
}

void			main_conversion(t_flags *conv, va_list ap)
{
	if (conv->specifier == 'c')
	{
		conversion_c(conv, ap);
	}
	else if (conv->specifier == 's')
	{
		conversion_s(conv, ap);
	}
	else if (conv->specifier == 'p')
	{
		conversion_p(conv, ap);
	}
	else if (conv->specifier == 'd' || conv->specifier == 'i')
	{
		conversion_signed(conv, ap);
	}
	else if (conv->specifier == 'u' || conv->specifier == 'o' || \
		conv->specifier == 'x' || conv->specifier == 'X')
		conversion_unsigned(conv, ap);
	else
	{
		main_conversion2(conv, ap);
	}
}
