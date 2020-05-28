/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fat_prepend.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 15:36:50 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/10 15:37:19 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_prepend(char **str, char const *prepend)
{
	char		*ret;
	size_t		i;
	size_t		j;

	if (*str == NULL || prepend == NULL)
		return (NULL);
	ret = ft_strnew(ft_strlen(*str) + ft_strlen(prepend));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (prepend[i])
	{
		ret[i] = prepend[i];
		i++;
	}
	while ((*str)[j])
	{
		ret[i + j] = (*str)[j];
		j++;
	}
	ft_strdel(str);
	return (ret);
}
