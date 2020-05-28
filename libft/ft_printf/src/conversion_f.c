/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/11 14:18:32 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/01 22:18:07 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		put_flags_to_buf(t_flags *conv)
{
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS && (conv->flag & FLAG_ZERO)
	!= FLAG_ZERO)
	{
		conv->buf[conv->i] = '+';
		conv->i++;
	}
	else if ((conv->flag & FLAG_SPACE) == FLAG_SPACE)
	{
		conv->buf[conv->i] = ' ';
		conv->i++;
	}
	if (conv->i == (BUFF_SIZE_PF - 1))
		print_buf(conv);
}

void		conversion_f_width(t_flags *conv, t_float *dbl)
{
	int		len;
	char	c;
	char	d;

	c = zero_space(conv);
	len = (ft_nchar(dbl->output, '.') + dbl->precision);
	if ((dbl->output[0] == '-' || (conv->flag & FLAG_PLUS) == FLAG_PLUS) &&
	((conv->flag & FLAG_ZERO) == FLAG_ZERO))
	{
		d = plus_min(conv);
		conv->buf[conv->i] = d;
		conv->i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
			print_buf(conv);
		if (dbl->output[0] == '-')
			dbl->output = ft_replace(&dbl->output, "", 0, 1);
	}
	if (len < conv->width)
		conv->width = conv->width - len;
	while_to_buf(conv, conv->width, c);
}

void		conversion_f_precision2(t_flags *conv, t_float *dbl, int rounding)
{
	int		i;

	i = 0;
	while (i < (rounding + dbl->precision))
	{
		if (dbl->output[i] == '\0')
		{
			while (i < (rounding + dbl->precision))
			{
				conv->buf[conv->i] = '0';
				conv->i++;
				i++;
				if (conv->i == (BUFF_SIZE_PF - 1))
					print_buf(conv);
			}
		}
		else
		{
			conv->buf[conv->i] = dbl->output[i];
			conv->i++;
			i++;
			if (conv->i == (BUFF_SIZE_PF - 1))
				print_buf(conv);
		}
	}
}

void		conversion_f_precision(t_flags *conv, t_float *dbl, int min)
{
	int			rounding;
	int			len;
	int			temp;

	temp = 0;
	min = 0;
	len = ft_strlen(dbl->output);
	rounding = ft_nchar(dbl->output, '.');
	if (dbl->output[rounding + dbl->precision] > '4')
	{
		rounding -= 1;
		rounding = (dbl->precision == 0) ? rounding -= 1 : rounding;
		if (dbl->output[rounding + dbl->precision] == '9')
		{
			f_rounding_up(dbl, rounding);
		}
		else
			dbl->output[rounding + dbl->precision]++;
	}
	rounding = (dbl->precision == 0 && (conv->flag & FLAG_HASH) != FLAG_HASH) ?
	(ft_nchar(dbl->output, '.') - 1) :
	ft_nchar(dbl->output, '.');
	conversion_f_precision2(conv, dbl, rounding);
}

void		conversion_f(t_flags *conv, va_list ap, t_float *dbl)
{
	dbl->nb = va_arg(ap, double);
	set_params(conv, dbl);
	if (!special_nb(dbl))
		get_tfloat(dbl);
	if (dbl->output[0] == '-')
		clear_plus_space_flags(conv);
	dbl->precision = (conv->precision == -1) ? 6 : conv->precision;
	conversion_f_direct(conv, dbl);
}
