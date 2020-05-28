/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc_div.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 20:46:07 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 20:49:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcalc_div(char **nb)
{
	int		len;

	if (!ft_strcalc_valid(*nb))
		return (NULL);
	len = ft_strlen(*nb);
	while (len > 0)
	{
		if ((*nb)[len - 1] == '.')
			len--;
		if (((*nb)[len - 1] - '0') % 2 == 1)
		{
			if ((*nb)[len] == 0)
				*nb = ft_append(nb, "5");
			else if ((*nb)[len] == '.')
				(*nb)[len + 1] += 5;
			else
				(*nb)[len] += 5;
		}
		(*nb)[len - 1] = (((*nb)[len - 1] - '0') / 2) + '0';
		len--;
	}
	if ((*nb)[0] == '0' && (*nb)[1] != '.')
		*nb = ft_replace(nb, "", 0, 1);
	return (*nb);
}
