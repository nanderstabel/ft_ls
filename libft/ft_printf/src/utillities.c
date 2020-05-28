/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utillities.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/19 12:22:36 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 17:27:42 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This functions clears the variables so it can be used for the next
** conversion.
*/

void	clear_struct(t_flags *conv)
{
	conv->flag = 0;
	conv->width = -1;
	conv->precision = -1;
	conv->specifier = '\0';
}

/*
** This function prints the buf, adds the number of bytes printed to conv->num,
** cleares the buf and sets conv->i to 0;
*/

void	replace_delim(t_flags *conv)
{
	int i;

	i = 0;
	while (conv->buf[i])
	{
		if (conv->buf[i] == -1)
		{
			conv->buf[i] = 0;
		}
		i++;
	}
}

/*
** This function prints the buf in 2 diffrent ways, depending if the
** conv->delim is 1;
*/

void	print_buf(t_flags *conv)
{
	int		i;

	i = 0;
	conv->buf[conv->i] = '\0';
	if (conv->delim)
	{
		i = ft_strlen(conv->buf);
		replace_delim(conv);
		ft_putnstr(conv->buf, (size_t)i);
		conv->delim = 0;
	}
	else
	{
		ft_putstr(conv->buf);
	}
	conv->num = conv->num + conv->i;
	ft_bzero(conv->buf, (BUFF_SIZE_PF));
	conv->i = 0;
}

void	arg_index(t_flags *conv, const char **format, va_list ap)
{
	const char	*tmp;

	(*format)++;
	tmp = *format;
	if (ft_isdigit(*tmp) && *tmp != '0')
	{
		while (ft_isdigit(*tmp))
			tmp++;
		if (*tmp == '$')
		{
			conv->flag |= FLAG_DOL;
			conv->arg_index = ft_atoi(*format);
			va_end(ap);
			va_copy(ap, conv->start);
			while (conv->arg_index > 1)
			{
				va_arg(ap, int);
				conv->arg_index--;
			}
			*format = tmp + 1;
		}
	}
}

/*
** This function picks up the precision from the format string
*/

void	main_precision(t_flags *conv, const char **format, va_list ap)
{
	if (**format == '.' && *(*format + 1) == '*')
	{
		(*format)++;
		conv->precision = va_arg(ap, int);
		if (conv->precision < 0)
			conv->precision = -1;
		(*format)++;
	}
	else if (**format == '.')
	{
		(*format)++;
		if (**format == '0')
		{
			conv->precision = 0;
			(*format)++;
		}
		else if (ft_isdigit(**format) != 1)
			conv->precision = 0;
		else
		{
			conv->precision = ft_atoi(*format);
			while (ft_isdigit(**format) == 1)
				(*format)++;
		}
	}
}
