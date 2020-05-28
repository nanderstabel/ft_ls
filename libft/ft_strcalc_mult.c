/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc_mult.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 20:48:51 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 21:03:18 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_solve(char **nb, int len, int save, int add)
{
	while (len > 0)
	{
		if ((*nb)[len - 1] == '.')
			len--;
		save = ((*nb)[len - 1] - '0') * 2;
		(*nb)[len - 1] = (save % 10) + add + '0';
		add = save / 10;
		if (add)
		{
			if (len == 1)
			{
				*nb = ft_prepend(nb, "1");
				if (nb == NULL)
					return (0);
				add = 0;
			}
		}
		len--;
	}
	return (*nb);
}

char		*ft_strcalc_mult(char **nb)
{
	int		len;
	int		save;
	int		add;

	if (!ft_strcalc_valid(*nb))
		return (NULL);
	save = 0;
	add = 0;
	len = ft_strlen(*nb);
	return (ft_solve(nb, len, save, add));
}
