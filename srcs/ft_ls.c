/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/24 00:03:01 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/30 12:47:59 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort_flist(t_ls *struc, t_files **flist)
{
	t_files			*head;
	t_files			*a;
	t_files			*b;

	head = *flist;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	sort_flist(struc, &a);
	sort_flist(struc, &b);
	if (struc->flags & T_FLAG)
	{
		if (struc->flags & R_FLAG)
			*flist = merge_flists_time_reverse(a, b);
		else
			*flist = merge_flists_time(a, b);
	}
	else
	{
		if (struc->flags & R_FLAG)
			*flist = merge_flists_reverse(a, b);
		else
			*flist = merge_flists(a, b);
	}
}

void			recursive(t_ls *struc, t_files *flist, char *dpath)
{
	char		*sdpath;
	t_files		*tmp;

	struc_zero(struc);
	if (!ft_strequ("/", dpath))
		dpath = ft_append(&dpath, "/");
	sdpath = ft_strdup(dpath);
	tmp = flist;
	while (tmp)
	{
		if (tmp->sdirinf->d_type == DT_DIR && !ft_strstr("..",  \
			tmp->sdirinf->d_name) && !((struc->flags & A_FLAG) != \
			A_FLAG && tmp->sdirinf->d_name[0] == '.'))
		{
			sdpath = ft_append(&sdpath, tmp->sdirinf->d_name);
			ft_printf("\n%s:\n", sdpath);
			ft_ls(struc, ft_strdup(sdpath));
			ft_strdel(&sdpath);
			sdpath = ft_strdup(dpath);
		}
		tmp = tmp->next;
	}
	flist_del(&flist);
	ft_strdel(&dpath);
	ft_strdel(&sdpath);
}

void			ft_ls(t_ls *struc, char *dpath)
{
	DIR		*cdir;
	t_files	*flist;

	cdir = opendir(dpath);
	if (cdir == NULL)
	{
		if (ft_strrchr(dpath, '/'))
			ft_printf("ft_ls: %s: %s\n", ft_strrchr(dpath, '/') + 1, \
			strerror(errno));
		else
			ft_printf("ft_ls: %s: %s\n", dpath, strerror(errno));
		ft_strdel(&dpath);
		return ;
	}
	flist = get_flist(struc, cdir, ft_strdup(dpath));
	if ((struc->flags & F_FLAG) != F_FLAG)
		sort_flist(struc, &flist);
	print_flist_portal(struc, flist);
	if (struc->flags & R_UP_FLAG)
		recursive(struc, flist, ft_strdup(dpath));
	else
		flist_del(&flist);
	ft_strdel(&dpath);
	closedir(cdir);
}

void			loop_dirs(t_ls *struc)
{
	t_list	*tmp;

	tmp = struc->dirs->next;
	if (struc->no_dirs->next && tmp)
		ft_putchar(10);
	while (tmp)
	{
		struc_zero(struc);
		if (struc->multargs || struc->dirs->next->next)
			ft_printf("%s:\n", tmp->content);
		ft_ls(struc, ft_strdup(tmp->content));
		tmp = tmp->next;
		if (tmp)
			ft_putchar(10);
	}
}

int				main(int argc, char **argv)
{
	t_ls	*struc;
	int		i;

	i = 1;
	struc = set_struct();
	while (i < argc && *argv[i] == '-')
	{
		set_flags(struc, argv[i]);
		i++;
	}
	sort_args(struc, argv + i);
	if (struc->no_dirs->next)
		print_no_dirs(struc);
	loop_dirs(struc);
	if (i == argc && ((struc->flags & D_FLAG) != D_FLAG))
		ft_ls(struc, ft_strdup("."));
	ft_lstdel(&struc->no_dirs, ft_freezero);
	ft_lstdel(&struc->dirs, ft_freezero);
	return (0);
}
