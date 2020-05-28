/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memalloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/01 01:47:07 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/13 10:54:17 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *s;

	s = (char *)malloc(sizeof(char) * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, size);
	return ((void *)s);
}
