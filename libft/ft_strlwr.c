/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlwr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 22:17:43 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/10 15:49:47 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlwr(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strnew(ft_strlen(s));
	if (s == NULL || str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = ft_tolower(s[i]);
		i++;
	}
	return (str);
}
