/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 14:37:13 by nstabel        #+#    #+#                */
/*   Updated: 2019/01/28 09:45:57 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int cnt;

	cnt = 0;
	while (str[cnt] != '\0')
		++cnt;
	return (cnt);
}
