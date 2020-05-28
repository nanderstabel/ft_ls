/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc_multexptwo.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 20:47:23 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 20:56:34 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcalc_multexptwo(char **nb, int exponent)
{
	char	*ret;

	if (!ft_strcalc_valid(*nb))
		return (NULL);
	ret = ft_strdup(*nb);
	if (exponent > 0)
	{
		while (exponent)
		{
			ret = ft_strcalc_mult(&ret);
			exponent--;
		}
	}
	else if (exponent < 0)
	{
		exponent *= -1;
		while (exponent)
		{
			ret = ft_strcalc_div(&ret);
			exponent--;
		}
	}
	ft_strdel(nb);
	return (ret);
}
