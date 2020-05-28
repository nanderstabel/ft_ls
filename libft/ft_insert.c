/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_insert.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 15:55:12 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/11 13:31:52 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_insert(char **str, char const *insert, size_t pos)
{
	char		*ret;
	size_t		i;

	i = 0;
	if (*str == NULL || insert == NULL || pos > ft_strlen(*str))
		return (NULL);
	ret = ft_strnew(pos);
	if (ret == NULL)
		return (NULL);
	while (i < pos)
	{
		ret[i] = (*str)[i];
		i++;
	}
	ret = ft_append(&ret, insert);
	ret = ft_append(&ret, *str + pos);
	ft_strdel(str);
	return (ret);
}
