/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rnchar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 16:36:13 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/10 15:01:52 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function searches for the last char c in string str. If it find the char
** it returns the count (incl. the char) in intgers (starting at 1 not 0). If he
** doesnt find c then it returnes a 0.
*/

int		ft_rnchar(const char *str, int c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == ((unsigned char)c))
			count = i;
		++i;
	}
	return (count + 1);
}
