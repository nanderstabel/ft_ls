/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/10 15:35:50 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/07 13:05:07 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append(char **str, char const *append)
{
	char		*ret;
	size_t		i;
	size_t		j;

	if (*str == NULL || append == NULL)
		return (NULL);
	ret = ft_strnew(ft_strlen(*str) + ft_strlen(append));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		ret[i] = (*str)[i];
		i++;
	}
	while (append[j])
	{
		ret[i + j] = append[j];
		j++;
	}
	ft_strdel(str);
	return (ret);
}
