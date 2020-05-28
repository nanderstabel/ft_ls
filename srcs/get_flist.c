/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_flist.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/26 16:10:30 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/29 11:51:38 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files			*flist_new(struct dirent *sdirinf)
{
	t_files	*flist;

	flist = (t_files *)malloc(sizeof(t_files));
	if (flist == NULL)
		return (NULL);
	if (sdirinf == NULL)
		flist->sdirinf = NULL;
	else
	{
		flist->sdirinf = (struct dirent *)malloc(sizeof(struct dirent));
		flist->sfile = (struct stat *)malloc(sizeof(struct stat));
		if (flist->sdirinf == NULL)
			return (NULL);
		ft_memcpy(flist->sdirinf, sdirinf, sizeof(struct dirent));
		flist->symlink = ft_strnew(256);
		flist->special = 0;
		flist->name = NULL;
	}
	flist->next = NULL;
	return (flist);
}

void			flist_append(t_ls *struc, t_files **flist, \
			struct dirent *sdirinf, char *dpath)
{
	t_files		*add;
	t_files		*tmp;

	add = flist_new(sdirinf);
	get_file_inf(struc, add, ft_strjoin(dpath, "/"));
	tmp = *flist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	add = NULL;
}

void			flist_del(t_files **flist)
{
	t_files		*tmp;

	while (*flist)
	{
		tmp = (*flist)->next;
		ft_bzero((void *)((*flist)->sdirinf), sizeof(struct dirent));
		free((*flist)->sdirinf);
		ft_bzero((void *)((*flist)->sfile), sizeof(struct stat));
		free((*flist)->sfile);
		ft_strdel(&(*flist)->symlink);
		ft_strdel(&(*flist)->mode);
		ft_strdel(&(*flist)->user);
		ft_strdel(&(*flist)->group);
		ft_strdel(&(*flist)->time);
		ft_memdel((void **)flist);
		*flist = tmp;
	}
	ft_memdel((void **)flist);
}

t_files			*get_flist(t_ls *struc, DIR *dir, char *dpath)
{
	struct dirent	*dirinf;
	t_files			*flist;

	dirinf = readdir(dir);
	struc->width = dirinf->d_namlen;
	flist = flist_new(dirinf);
	get_file_inf(struc, flist, ft_strjoin(dpath, "/"));
	while (dirinf)
	{
		dirinf = readdir(dir);
		if (dirinf)
		{
			flist_append(struc, &flist, dirinf, dpath);
			if (!(dirinf->d_name[0] == '.' && (struc->flags & A_FLAG) \
				!= A_FLAG))
				if (struc->width < dirinf->d_namlen)
					struc->width = dirinf->d_namlen;
		}
	}
	struc->width += (7 - (struc->width % 8));
	ft_strdel(&dpath);
	return (flist);
}
