/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_f_utillities2.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/13 11:10:08 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/01 18:09:51 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		putstr_to_buf(t_flags *conv, t_float *dbl)
{
	int i;

	i = 0;
	while (dbl->output[i] != '\0')
	{
		conv->buf[conv->i] = dbl->output[i];
		conv->i++;
		i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
			print_buf(conv);
	}
}

void			conversion_f_redirect(t_flags *conv, t_float *dbl)
{
	if (dbl->output[0] == '-')
	{
		conversion_f_precision(conv, dbl, 1);
	}
	else
	{
		conversion_f_precision(conv, dbl, 0);
	}
}

void			conversion_f_infnan(t_flags *conv, t_float *dbl)
{
	int	i;

	i = 0;
	conv->width = (conv->width == -1) ? 0 : (conv->width - \
		ft_strlen(dbl->output));
	if ((conv->flag & FLAG_MIN) == FLAG_MIN)
	{
		putstr_to_buf(conv, dbl);
		while_to_buf(conv, conv->width, ' ');
	}
	else
	{
		while_to_buf(conv, conv->width, ' ');
		putstr_to_buf(conv, dbl);
	}
}

void			conversion_f_direct(t_flags *conv, t_float *dbl)
{
	if (ft_strstr("-infnan", dbl->output))
		conversion_f_infnan(conv, dbl);
	else
	{
		if ((conv->flag & FLAG_MIN) == FLAG_MIN)
		{
			put_flags_to_buf(conv);
			conversion_f_redirect(conv, dbl);
			conversion_f_width(conv, dbl);
		}
		else
		{
			conversion_f_width(conv, dbl);
			put_flags_to_buf(conv);
			conversion_f_redirect(conv, dbl);
		}
	}
}
