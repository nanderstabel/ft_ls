/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc_valid.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 20:43:17 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 20:43:41 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcalc_valid(char *s)
{
	size_t	dotcount;

	dotcount = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '.')
		{
			dotcount++;
			if (dotcount > 1)
				return (0);
		}
		if (!ft_isdigit(*s) && *s != '.')
			return (0);
		s++;
	}
	return (1);
}
