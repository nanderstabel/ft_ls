/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strupr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/09 22:13:27 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/10 15:47:15 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupr(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strnew(ft_strlen(s));
	if (s == NULL || str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = ft_toupper(s[i]);
		i++;
	}
	return (str);
}
