/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcut.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/10 15:12:00 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/10 15:34:04 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcut(char **str, size_t start, size_t len)
{
	char	*cut;
	char	*tmp;

	tmp = ft_strdup(*str);
	if (*str == NULL || tmp == NULL)
		return (NULL);
	cut = ft_strsub(*str, start, len);
	ft_strdel(str);
	*str = ft_strsub(tmp, 0, start);
	*str = ft_append(str, tmp + start + len);
	ft_strdel(&tmp);
	return (cut);
}
