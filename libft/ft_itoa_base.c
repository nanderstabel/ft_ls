/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 00:36:14 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/10 15:41:58 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long value, int base)
{
	char		*s;
	char		*hex;
	long long	tmp;
	int			len;

	hex = "0123456789abcdef";
	tmp = value;
	len = (value < 0 && base == 10) ? 2 : 1;
	while (tmp /= base)
		len++;
	s = ft_strnew(len);
	if (s == NULL)
		return (NULL);
	if (value < 0 && base == 10)
		s[0] = '-';
	if (value == 0)
		s[0] = '0';
	while (value)
	{
		len--;
		s[len] = hex[(value < 0) ? -(value % base) : value % base];
		value /= base;
	}
	return (s);
}
