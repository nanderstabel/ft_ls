/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_inf.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 21:35:59 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/10 20:33:22 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		longest_nbr(int width, int nb)
{
	int		count;

	count = 1;
	while (nb /= 10)
		count++;
	if (count > width)
		return (count);
	return (width);
}

static void		set_user_and_group(t_ls *struc, t_files *flist)
{
	struct passwd	*user;
	struct group	*grp;

	user = getpwuid(flist->sfile->st_uid);
	grp = getgrgid(flist->sfile->st_gid);
	if (user == NULL)
		flist->user = ft_itoa(flist->sfile->st_uid);
	else
		flist->user = ft_strdup(user->pw_name);
	if (grp == NULL)
		flist->group = ft_itoa(flist->sfile->st_gid);
	else
		flist->group = ft_strdup(grp->gr_name);
	flist->user = ft_append(&flist->user, "  ");
	flist->group = ft_append(&flist->group, " ");
	if (struc->flags & G_FLAG)
	{
		ft_strdel(&flist->user);
		flist->user = ft_strdup("");
	}
}

static void		use_lstat(t_files *flist, char *sdpath)
{
	int		len;

	lstat(sdpath, flist->sfile);
	len = readlink(sdpath, flist->symlink, 1024);
	flist->symlink[len] = 0;
	flist->symlink = ft_prepend(&flist->symlink, " -> ");
}

static void		get_file_inf_cont(t_ls *struc, t_files *flist)
{
	if (flist->sdirinf->d_type == DT_BLK || \
		flist->sdirinf->d_type == DT_CHR)
	{
		flist->special = 1;
		flist->minor = minor(flist->sfile->st_rdev);
		flist->major = major(flist->sfile->st_rdev);
		struc->size_width = 8;
	}
	if (!(flist->sdirinf->d_name[0] == '.' && (struc->flags & A_FLAG) \
				!= A_FLAG))
	{
		struc->nlink_width = longest_nbr(struc->nlink_width, flist->nlink);
		if (struc->user_width < (int)ft_strlen(flist->user))
			struc->user_width = (int)ft_strlen(flist->user);
		if (struc->group_width < (int)ft_strlen(flist->group))
			struc->group_width = (int)ft_strlen(flist->group);
		struc->size_width = longest_nbr(struc->size_width, flist->size);
	}
}

void			get_file_inf(t_ls *struc, t_files *flist, char *sdpath)
{
	char	*list;

	list = ft_strnew(1024);
	sdpath = ft_append(&sdpath, flist->sdirinf->d_name);
	if (flist->sdirinf->d_type == DT_LNK)
		use_lstat(flist, sdpath);
	else
		stat(sdpath, flist->sfile);
	listxattr(sdpath, list, 1024, XATTR_NOFOLLOW);
	ft_strdel(&sdpath);
	flist->mode = set_mode(flist->sdirinf->d_type, flist->sfile->st_mode, list);
	ft_strdel(&list);
	flist->nlink = flist->sfile->st_nlink;
	set_user_and_group(struc, flist);
	flist->size = flist->sfile->st_size;
	set_time(struc, flist);
	get_file_inf_cont(struc, flist);
	if ((struc->flags & A_FLAG) != A_FLAG && flist->sdirinf->d_name[0] == '.')
		return ;
	struc->tsize += flist->sfile->st_blocks;
}
