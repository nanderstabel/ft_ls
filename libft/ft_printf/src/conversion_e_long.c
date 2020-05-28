/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_e_long.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/31 13:47:07 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 13:39:01 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This file is a copy of conversion_e.c The only difference is that long
** doubles are used instead of doubles. Check the conversion_e.c file for
** explanations on the functions beneath.
*/

static void		get_exponent_e(t_float *dbl)
{
	dbl->extension = 0;
	dbl->dec_exp = 0;
	if (ft_strequ("0.0", dbl->output))
		dbl->output = ft_select(&dbl->output, 0, 1);
	else if (dbl->output[0] != '0')
	{
		dbl->dec_exp = ft_nchar(dbl->output, '.') - 2;
		dbl->output = ft_replace(&dbl->output, "", dbl->dec_exp + 1, 1);
	}
	else
	{
		while (dbl->output[dbl->dec_exp] == '0' || \
			dbl->output[dbl->dec_exp] == '.')
			dbl->dec_exp++;
		dbl->output = ft_replace(&dbl->output, "", 0, dbl->dec_exp);
		dbl->dec_exp--;
		dbl->extension = 1;
	}
	while ((int)ft_strlen(dbl->output) < dbl->precision + 2)
		dbl->output = ft_append(&dbl->output, "0");
	dbl->dec_exp = (dbl->extension) ? -dbl->dec_exp : dbl->dec_exp;
}

static void		round_frac(t_float *dbl)
{
	char	*tmp;

	if (dbl->output[dbl->precision + 1] > '5')
		dbl->output[dbl->precision]++;
	else if (dbl->output[dbl->precision + 1] == '5' && \
			dbl->output[dbl->precision + 2])
		dbl->output[dbl->precision]++;
	dbl->output = ft_select(&dbl->output, 0, dbl->precision + 1);
	while (ft_strchr(dbl->output, ':'))
	{
		tmp = ft_strchr(dbl->output, ':');
		if (tmp == dbl->output)
		{
			dbl->output = ft_prepend(&dbl->output, "1");
			dbl->output = ft_select(&dbl->output, 0, dbl->precision + 1);
			dbl->dec_exp++;
			if (ft_strlen(dbl->output) == 1)
				break ;
		}
		(*(tmp - 1))++;
		*tmp = '0';
	}
}

static void		add_exponent(t_float *dbl)
{
	char	*temp;

	temp = ft_itoa(dbl->dec_exp);
	if (dbl->extension)
		dbl->output = ft_append(&dbl->output, "e-");
	else
		dbl->output = ft_append(&dbl->output, "e+");
	if (dbl->dec_exp < 10)
		dbl->output = ft_append(&dbl->output, "0");
	dbl->output = ft_append(&dbl->output, temp);
	ft_strdel(&temp);
}

void			e_long_specifier(t_float *dbl)
{
	if (dbl->sign || ft_strequ("-0.0", dbl->output))
		dbl->output = ft_replace(&dbl->output, "", 0, 1);
	get_exponent_e(dbl);
	dbl->dec_exp = (dbl->extension) ? -dbl->dec_exp : dbl->dec_exp;
	round_frac(dbl);
	add_exponent(dbl);
	if (dbl->precision)
		dbl->output = ft_insert(&dbl->output, ".", 1);
}

void			conversion_e_long(t_flags *conv, va_list ap)
{
	long double	nb;
	t_float		*dbl;

	nb = va_arg(ap, long double);
	dbl = malloc(sizeof(t_float));
	dbl->nb_long = nb;
	set_params(conv, dbl);
	if (!special_nb_long(dbl))
		get_tfloat_long(dbl);
	if (dbl->output[0] == '-')
		clear_plus_space_flags(conv);
	dbl->precision = (conv->precision == -1) ? 6 : conv->precision;
	if (!ft_strstr("-infnan", dbl->output))
		e_long_specifier(dbl);
	conversion_e_flags(conv, dbl);
	conversion_e_width(conv, dbl);
	put_e_to_buf(conv, dbl->output);
	clear_tfloat_e(dbl);
}
