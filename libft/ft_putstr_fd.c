/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 14:09:35 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/15 10:46:55 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *str, int fd)
{
	int cnt;

	if (str == NULL)
		return ;
	cnt = 0;
	while (str[cnt] != '\0')
	{
		ft_putchar_fd(str[cnt], fd);
		++cnt;
	}
}
