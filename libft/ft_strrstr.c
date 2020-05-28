/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 15:27:02 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/17 15:51:56 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(haystack);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (i)
	{
		--i;
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			++j;
		}
	}
	return (NULL);
}
