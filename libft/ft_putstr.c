/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 14:09:35 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/15 10:45:59 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *str)
{
	int cnt;

	if (str == NULL)
		return ;
	cnt = 0;
	while (str[cnt] != '\0')
	{
		ft_putchar(str[cnt]);
		++cnt;
	}
}
