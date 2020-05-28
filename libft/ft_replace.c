/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_replace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/11 13:36:57 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/11 13:56:19 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replace(char **str, char const *insert, size_t pos, size_t len)
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
	if (ft_strlen(*str) - pos > len)
		ret = ft_append(&ret, *str + pos + len);
	ft_strdel(str);
	return (ret);
}
