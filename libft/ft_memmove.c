/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/28 19:09:55 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/01 14:18:26 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (len == 0)
		return (dst);
	if (s < d)
	{
		d += len - 1;
		s += len - 1;
		while (len > 0)
		{
			*d = *s;
			len--;
			d--;
			s--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
