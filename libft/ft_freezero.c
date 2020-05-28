/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_freezero.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/16 14:59:49 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/16 14:59:51 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freezero(void *mem, size_t size)
{
	ft_bzero(mem, size);
	ft_memdel(&mem);
}
