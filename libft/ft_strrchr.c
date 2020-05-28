/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 14:16:47 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/13 15:05:43 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;

	i = 0;
	last = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last = i;
		++i;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	if (last > -1)
		return ((char *)s + last);
	return (NULL);
}
