/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f_tfloat_long.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/13 11:06:40 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 14:17:50 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		get_sign_long(t_float *dbl)
{
	dbl->sign = 0;
	if (dbl->nb_long < 0)
	{
		dbl->sign = 1;
		dbl->dec_frac_long *= -1;
	}
}

static void		get_exponent_long(t_float *dbl)
{
	if (dbl->dec_frac_long >= 2.0)
	{
		while (dbl->dec_frac_long >= 2.0 && dbl->dec_exp < dbl->params->exp_max)
		{
			dbl->dec_frac_long /= 2;
			dbl->dec_exp++;
		}
	}
	else if (dbl->dec_frac_long < 1.0)
	{
		while (dbl->dec_frac_long < 1.0 && dbl->dec_exp > \
			dbl->params->exp_true_min)
		{
			dbl->dec_frac_long *= 2;
			dbl->dec_exp--;
		}
	}
	dbl->extension = (dbl->dec_exp < dbl->params->exp_min) ? \
		-(dbl->dec_exp) - -dbl->params->exp_min : 0;
	if (dbl->dec_exp >= dbl->params->exp_min)
		dbl->bin_exp = ft_itoa_base(-dbl->params->exp_min + dbl->dec_exp, 2);
	else
		dbl->bin_exp = ft_strdup("00000000");
	while ((int)ft_strlen(dbl->bin_exp) < dbl->params->exp_field)
		dbl->bin_exp = ft_prepend(&dbl->bin_exp, "0");
}

static void		get_fraction_long(t_float *dbl)
{
	long double	tmp;

	tmp = 0.5;
	dbl->bin_frac = ft_strnew(0);
	dbl->dec_frac_long -= 1;
	if (dbl->bin_frac == NULL)
		return ;
	if (dbl->extension && dbl->extension < dbl->params->frac_field)
	{
		while ((int)ft_strlen(dbl->bin_frac) < dbl->extension)
			dbl->bin_frac = ft_append(&dbl->bin_frac, "0");
		dbl->bin_frac = ft_append(&dbl->bin_frac, "1");
	}
	while ((int)ft_strlen(dbl->bin_frac) < dbl->params->frac_field)
	{
		if (tmp <= dbl->dec_frac_long)
		{
			dbl->bin_frac = ft_append(&dbl->bin_frac, "1");
			dbl->dec_frac_long -= tmp;
		}
		else
			dbl->bin_frac = ft_append(&dbl->bin_frac, "0");
		tmp /= 2;
	}
}

static void		get_output_long(t_float *dbl)
{
	int		i;

	i = dbl->extension;
	if (dbl->extension)
	{
		while (dbl->bin_frac[i])
		{
			if (dbl->bin_frac[i] == '1')
				dbl->output = ft_strcalc_add(&dbl->output, \
				dbl->frac_tab[-(dbl->dec_exp) - dbl->extension + i]);
			i++;
		}
	}
	else
	{
		dbl->output[0] = '1';
		while (dbl->bin_frac[i])
		{
			if (dbl->bin_frac[i] == '1')
				dbl->output = ft_strcalc_add(&dbl->output, \
				dbl->frac_tab[i + 1]);
			i++;
		}
		dbl->output = ft_strcalc_multexptwo(&dbl->output, dbl->dec_exp);
	}
}

void			get_tfloat_long(t_float *dbl)
{
	dbl->dec_exp = 0;
	dbl->dec_frac_long = dbl->nb_long;
	get_sign_long(dbl);
	dbl->output = ft_strdup("0.0");
	if (dbl->nb_long != (long double)0.0)
	{
		get_exponent_long(dbl);
		get_fraction_long(dbl);
		dbl->frac_tab = get_fraction_tab(dbl->dec_exp);
		get_output_long(dbl);
		clear_fraction_tab(dbl);
	}
	if (dbl->sign)
		dbl->output = ft_prepend(&dbl->output, "-");
}
