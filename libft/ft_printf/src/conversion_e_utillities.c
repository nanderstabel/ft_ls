/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_e_utillities.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 21:18:57 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 14:05:35 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Puts the e specifier output string to buf
*/

void		put_e_to_buf(t_flags *conv, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		conv->buf[conv->i] = str[i];
		conv->i++;
		i++;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** Adjusts the output string depending on the flags that are present.
*/

void		conversion_e_flags(t_flags *conv, t_float *dbl)
{
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO && \
		(conv->flag & FLAG_MIN) != FLAG_MIN)
		while (conv->width - dbl->sign > (int)ft_strlen(dbl->output))
			dbl->output = ft_prepend(&dbl->output, "0");
	if (dbl->sign == 1)
		dbl->output = ft_prepend(&dbl->output, "-");
	if ((conv->flag & FLAG_SPACE) == FLAG_SPACE && dbl->output[0] != '-' && \
		(conv->flag & FLAG_PLUS) != FLAG_PLUS)
		dbl->output = ft_prepend(&dbl->output, " ");
	if ((conv->flag & FLAG_PLUS) == FLAG_PLUS && dbl->output[0] != '-')
	{
		if (dbl->output[0] == '0' && dbl->output[0] == '0')
			dbl->output[0] = '+';
		else
			dbl->output = ft_prepend(&dbl->output, "+");
	}
}

/*
** Adjusts the output string depending on the width
*/

void		conversion_e_width(t_flags *conv, t_float *dbl)
{
	int		len;
	char	*temp;

	len = conv->width - ft_strlen(dbl->output);
	if (len > 0)
	{
		temp = ft_strnewfill(len, ' ');
		if ((conv->flag & FLAG_MIN) == FLAG_MIN)
			dbl->output = ft_append(&dbl->output, temp);
		else
			dbl->output = ft_prepend(&dbl->output, temp);
		free(temp);
	}
}

/*
** Frees all the necessary variables inside the tfloat struct.
*/

void		clear_tfloat_e(t_float *dbl)
{
	ft_strdel(&dbl->output);
	free(dbl->params);
	dbl->params = NULL;
	free(dbl);
	dbl = NULL;
}
