/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_start.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/07 19:02:17 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/08 10:24:09 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_start(char const *s)
{
	size_t	start;

	start = 0;
	while (start < ft_strlen(s) && (s[start] == ' ' || s[start] == '\n' \
		|| s[start] == '\t'))
		start++;
	return ((int)start);
}
