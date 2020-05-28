/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_e.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/20 17:50:13 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 13:55:16 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** The exponent is returned to conversion_e().
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

/*
** The string is rounded of depending on the precision given.
*/

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

/*
** The exponent suffix is added to the output string.
*/

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

/*
** In e_specifier the sign is temporarily removed first. The exponent is
** retrieved and adjusted depending on some "float stats". The string is
** rounded of and the exponent notation is added to the string. A dot is
** inserted if the precision is bigger than 0.
*/

void			e_specifier(t_float *dbl)
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

/*
** This function produces a string containing a float written in scientific
** notation. It receives the float/double, mallocs, set the parameters and
** checks for special cases (-0.0, -inf, nan). It receives the float in
** string notation via get_tfloat. In e_specifier this string is converted
** into scientific notation. Some conversions are made depending on
** the flags, the whole string is sent to put_e_to_buf and the structed is
** cleared (and freed);
*/

void			conversion_e(t_flags *conv, va_list ap)
{
	double		nb;
	t_float		*dbl;

	nb = va_arg(ap, double);
	dbl = malloc(sizeof(t_float));
	dbl->nb = nb;
	set_params(conv, dbl);
	if (!special_nb(dbl))
		get_tfloat(dbl);
	if (dbl->output[0] == '-')
		clear_plus_space_flags(conv);
	dbl->precision = (conv->precision == -1) ? 6 : conv->precision;
	if (!ft_strstr("-infnan", dbl->output))
		e_specifier(dbl);
	conversion_e_flags(conv, dbl);
	conversion_e_width(conv, dbl);
	put_e_to_buf(conv, dbl->output);
	clear_tfloat_e(dbl);
}
