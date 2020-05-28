/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/08 09:57:33 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/30 13:43:58 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		print_normal(t_ls *struc, t_files *flist, int ret)
{
	if (struc->flags & M_FLAG)
	{
		ret -= ft_printf("%s", flist->sdirinf->d_name);
		if (flist->next)
			ret -= ft_printf(", ");
		if (flist->next)
		{
			if (ret - (int)ft_strlen(flist->next->sdirinf->d_name) - 2 < 0)
			{
				ft_putchar(10);
				ret = struc->w.ws_col;
			}
		}
	}
	else
	{
		ret -= ft_printf("%-*s", struc->width + 1, flist->sdirinf->d_name);
		if (ret < struc->width && flist->next)
		{
			ft_putchar(10);
			ret = struc->w.ws_col;
		}
	}
	return (ret);
}

static void		print_flist(t_ls *struc, t_files *flist, int ret)
{
	while (flist)
	{
		while (!(struc->flags & A_FLAG) && flist->sdirinf->d_name[0] == '.')
		{
			flist = flist->next;
			if (!flist)
				return ;
		}
		struc->tsize = 1;
		if ((struc->flags & L_FLAG) == L_FLAG && !flist->special)
			ft_printf("%-11s %*i %-*s%-*s %*lli %s %s%s\n", flist->mode, \
			struc->nlink_width, flist->nlink, struc->user_width, flist->user, \
			struc->group_width, flist->group, struc->size_width, flist->size, \
			flist->time, flist->sdirinf->d_name, flist->symlink);
		else if ((struc->flags & L_FLAG) == L_FLAG && flist->special)
			ft_printf("%-11s %*i %-*s%-*s%4i,%4i %s %s%s\n", flist->mode, \
			struc->nlink_width, flist->nlink, struc->user_width, flist->user, \
			struc->group_width, flist->group, flist->major, flist->minor, \
			flist->time, flist->sdirinf->d_name, flist->symlink);
		else
			ret = print_normal(struc, flist, ret);
		flist = flist->next;
	}
}

static int		print_normal_spec(t_ls *struc, t_files *flist, int ret)
{
	if (struc->flags & M_FLAG)
	{
		ret -= ft_printf("%s", flist->name);
		if (flist->next)
			ret -= ft_printf(", ");
		if (flist->next)
		{
			if (ret - (int)ft_strlen(flist->next->name) - 2 < 0)
			{
				ft_putchar(10);
				ret = struc->w.ws_col;
			}
		}
	}
	else
	{
		ret -= ft_printf("%-*s", struc->width + 1, flist->name);
		if (ret < struc->width && flist->next)
		{
			ft_putchar(10);
			ret = struc->w.ws_col;
		}
	}
	return (ret);
}

static void		print_flist_spec(t_ls *struc, t_files *flist)
{
	int		ret;

	ret = struc->w.ws_col;
	while (flist)
	{
		if ((struc->flags & L_FLAG) == L_FLAG && !flist->special)
			ft_printf("%-11s %*i %-*s%-*s %*lli %s %s%s\n", flist->mode, \
			struc->nlink_width, flist->nlink, struc->user_width, flist->user, \
			struc->group_width, flist->group, struc->size_width, flist->size, \
			flist->time, flist->name, flist->symlink);
		else if ((struc->flags & L_FLAG) == L_FLAG && flist->special)
			ft_printf("%-11s %*i %-*s%-*s%4i,%4i %s %s%s\n", flist->mode, \
			struc->nlink_width, flist->nlink, struc->user_width, flist->user, \
			struc->group_width, flist->group, flist->major, flist->minor, \
			flist->time, flist->name, flist->symlink);
		else
			ret = print_normal_spec(struc, flist, ret);
		flist = flist->next;
	}
}

void			print_flist_portal(t_ls *struc, t_files *flist)
{
	if ((struc->flags & L_FLAG) == L_FLAG && !struc->no_dirs_spec && \
		flist->name == NULL)
		ft_printf("total %i\n", struc->tsize);
	if (flist->name)
		print_flist_spec(struc, flist);
	else
		print_flist(struc, flist, struc->w.ws_col);
	if (!(struc->flags & L_FLAG) && struc->tsize > 0)
		ft_putchar(10);
}
