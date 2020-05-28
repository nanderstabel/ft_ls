/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_select.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 13:25:44 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 13:26:13 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_select(char **str, size_t pos, size_t len)
{
	char		*ret;
	size_t		i;

	i = 0;
	if (*str == NULL || pos + len > ft_strlen(*str))
		return (NULL);
	ret = ft_strnew(len);
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = (*str)[pos + i];
		i++;
	}
	ft_strdel(str);
	return (ret);
}
