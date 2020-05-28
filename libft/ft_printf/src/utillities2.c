/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utillities2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/01 16:38:25 by mgross         #+#    #+#                */
/*   Updated: 2019/06/03 13:28:49 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function initiates the diffrent variables inside the structure.
*/

void		initiate_struct(t_flags *conv)
{
	conv->i = 0;
	conv->num = 0;
	conv->flag = 0;
	conv->width = -1;
	conv->precision = -1;
	conv->specifier = '\0';
}

/*
** This function prints everything thats in the buf and free's the struct.
*/

void		new_str(t_flags *conv)
{
	char	*temp;

	temp = conv->str;
	conv->str = ft_strupr(conv->str);
	free(temp);
}

void		no_conversion(t_flags *conv, const char **format)
{
	if (**format == '{')
		color_output(conv, format);
	conv->buf[conv->i] = **format;
	conv->i++;
	(*format)++;
	if (conv->i == (BUFF_SIZE_PF - 1))
		print_buf(conv);
}
