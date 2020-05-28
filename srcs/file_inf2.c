/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_inf2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/10 15:44:45 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/25 14:42:48 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			set_time(t_ls *struc, t_files *flist)
{
	time_t	date;

	time(&date);
	flist->time = ft_strdup(ctime(&flist->sfile->st_mtimespec.tv_sec));
	if (struc->flags & T_UP_FLAG)
	{
		flist->time = ft_select(&flist->time, 4, 20);
		return ;
	}
	flist->time = ft_select(&flist->time, 4, 20);
	if (flist->sfile->st_mtimespec.tv_sec > date - SIX_MONTH)
		flist->time = ft_select(&flist->time, 0, 12);
	else
		flist->time = ft_replace(&flist->time, "", 7, 8);
}
