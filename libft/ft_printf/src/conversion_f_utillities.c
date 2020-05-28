/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f_utillities.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/13 11:10:08 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 14:05:13 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	**get_fraction_tab(int exponent)
{
	char	*nb;
	char	**tab;
	int		i;

	exponent = (exponent < 0) ? -exponent : 0;
	exponent += 63;
	tab = (char **)malloc(sizeof(char *) * (exponent + 1) + 1);
	if (tab == NULL)
		return (NULL);
	tab[exponent + 1] = 0;
	nb = ft_strdup("1.0");
	i = 0;
	while (i <= exponent)
	{
		tab[i] = ft_strdup(nb);
		nb = ft_strcalc_div(&nb);
		i++;
	}
	ft_strdel(&nb);
	return (tab);
}

int		special_nb(t_float *dbl)
{
	if ((long double)1.0 / dbl->nb == (1.0 / 0.0))
		dbl->output = ft_strdup("0.0");
	else if ((long double)1.0 / dbl->nb == (-1.0 / 0.0))
	{
		dbl->output = ft_strdup("-0.0");
		dbl->sign = 1;
	}
	else if (dbl->nb == -1.0 / 0.0)
		dbl->output = ft_strdup("-inf");
	else if (dbl->nb == 1.0 / 0.0)
		dbl->output = ft_strdup("inf");
	else if (dbl->nb != dbl->nb)
		dbl->output = ft_strdup("nan");
	else
		return (0);
	return (1);
}

void	set_params(t_flags *conv, t_float *dbl)
{
	dbl->sign = 0;
	dbl->params = malloc(sizeof(t_params));
	if ((conv->flag & FLAG_L_UP) == FLAG_L_UP)
	{
		dbl->params->exp_max = 16384;
		dbl->params->exp_min = -16383;
		dbl->params->exp_true_min = -16446;
		dbl->params->exp_field = 15;
		dbl->params->frac_field = 63;
	}
	else
	{
		dbl->nb = (double)dbl->nb;
		dbl->params->exp_max = 1024;
		dbl->params->exp_min = -1023;
		dbl->params->exp_true_min = -1075;
		dbl->params->exp_field = 11;
		dbl->params->frac_field = 52;
	}
}

void	clear_tfloat(t_float *dbl)
{
	ft_strdel(&dbl->output);
	free(dbl->params);
	dbl->params = NULL;
	free(dbl);
}

void	clear_fraction_tab(t_float *dbl)
{
	int		i;

	i = 0;
	while (dbl->frac_tab[i])
	{
		free(dbl->frac_tab[i]);
		dbl->frac_tab[i] = NULL;
		i++;
	}
	free(dbl->frac_tab);
	dbl->frac_tab = NULL;
	ft_strdel(&dbl->bin_exp);
	ft_strdel(&dbl->bin_frac);
}
