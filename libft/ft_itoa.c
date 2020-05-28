/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 13:52:31 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/13 10:57:49 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	size_t	i;
	char	*str;
	int		sign;

	i = 0;
	str = ft_strnew(12);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		return (ft_strdup("0"));
	sign = (n < 0) ? 1 : 0;
	while (n != 0)
	{
		str[i] = (sign) ? (-1 * (n % 10)) + '0' : (n % 10) + '0';
		n /= 10;
		i++;
	}
	if (sign)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
	return (ft_strrev(str));
}
