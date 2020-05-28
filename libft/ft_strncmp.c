/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 14:42:05 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/13 13:39:30 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[i] != '\0')
	{
		if (i == n)
			return (0);
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		++i;
	}
	if (p2[i] != '\0' && i != n)
		return (0 - p2[i]);
	return (0);
}
