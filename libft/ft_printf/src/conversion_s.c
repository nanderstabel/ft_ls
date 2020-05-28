/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversion_s.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/29 11:11:25 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 14:05:32 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function takes the width, corrects it with the string len of the string
** to be printed and prints as many char c as possible, while checking if
** conv->buf isn't full.
*/

static void		conversion_width(t_flags *conv, int len)
{
	char	c;

	c = ' ';
	if ((conv->flag & FLAG_ZERO) == FLAG_ZERO)
		c = '0';
	if (conv->precision < len && conv->precision != -1)
	{
		len = conv->precision;
	}
	conv->width = conv->width - len;
	while (conv->width > 0)
	{
		conv->buf[conv->i] = c;
		conv->i++;
		conv->width--;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** This function copies the string from the argument of ft_printf to conv->buf
** and prints the conv->buf if it's full.
*/

static void		putstr_to_buf(t_flags *conv, char *str)
{
	int	i;
	int	p;

	p = conv->precision;
	i = 0;
	while (str[i] != '\0' && p != 0)
	{
		conv->buf[conv->i] = str[i];
		conv->i++;
		i++;
		p--;
		if (conv->i == (BUFF_SIZE_PF - 1))
		{
			print_buf(conv);
		}
	}
}

/*
** This function checks if the string is empty and changes accordingly
** Then it get the length and checkst if the minus flag is on. If so
** it first goes to func putstr_to_buff and after it's done goes to
** conversion_width. If the minus flag is not on, it first goes to func
** conversion_width and after it's done goes to putstr_to_buff.
*/

void			conversion_s(t_flags *conv, va_list ap)
{
	char	*str;
	int		len;

	str = va_arg(ap, char*);
	if (str == NULL)
	{
		str = "(null)";
		len = 0;
		if ((conv->flag & FLAG_ZERO) != FLAG_ZERO)
			conv->width = -1;
	}
	else if (str[0] == '\0')
		len = 0;
	else
		len = ft_strlen(str);
	if ((conv->flag & FLAG_MIN) == FLAG_MIN)
	{
		putstr_to_buf(conv, str);
		conversion_width(conv, len);
	}
	else
	{
		conversion_width(conv, len);
		putstr_to_buf(conv, str);
	}
}
