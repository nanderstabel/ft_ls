/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 08:26:50 by mgross         #+#    #+#                */
/*   Updated: 2019/05/30 11:37:24 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnstr(char const *str, size_t len)
{
	int i;

	i = 0;
	if (str == NULL)
		return ;
	while (i < (int)len)
	{
		ft_putchar(str[i]);
		i++;
	}
}
