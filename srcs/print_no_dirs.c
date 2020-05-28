/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_no_dirs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/17 17:15:57 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/11 20:40:19 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					set_dir_and_file(t_list *tmp, char **dir, char **file)
{
	ft_strdel(dir);
	if (ft_strchr(tmp->content, '/'))
	{
		*dir = ft_strsub(tmp->content, 0, ft_rnchar(tmp->content, '/'));
		*file = ft_strrchr(tmp->content, '/') + 1;
	}
	else
	{
		*dir = ft_strdup("./");
		*file = tmp->content;
	}
}

void					flist_append_spec(t_ls *struc, t_files **flist, \
							struct dirent *sdirinf, char *dir)
{
	t_files		*add;
	t_files		*tmp;

	add = flist_new(sdirinf);
	add->name = ft_strdup(struc->name);
	get_file_inf(struc, add, ft_strdup(dir));
	tmp = *flist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add;
	add = NULL;
}

static struct dirent	*get_dirinf(char *dir, char *file)
{
	DIR				*tmp_dir;
	struct dirent	*dirinf;

	tmp_dir = opendir(dir);
	dirinf = readdir(tmp_dir);
	while (!ft_strstr(dirinf->d_name, file))
		dirinf = readdir(tmp_dir);
	return (dirinf);
}

static void				loop_list(t_ls *struc, t_nodirs *nd)
{
	nd->tmp = nd->tmp->next;
	while (nd->tmp)
	{
		struc->multargs = 1;
		set_dir_and_file(nd->tmp, &nd->dir, &nd->file);
		nd->dirinf = get_dirinf(nd->dir, nd->file);
		struc->name = nd->tmp->content;
		flist_append_spec(struc, &nd->flist, nd->dirinf, nd->dir);
		if (struc->width < (int)ft_strlen(nd->tmp->content))
			struc->width = (int)ft_strlen(nd->tmp->content);
		nd->tmp = nd->tmp->next;
	}
}

void					print_no_dirs(t_ls *struc)
{
	t_nodirs	*nd;

	nd = (t_nodirs *)malloc(sizeof(t_nodirs));
	nd->tmp = struc->no_dirs->next;
	nd->dir = ft_strnew(0);
	set_dir_and_file(nd->tmp, &nd->dir, &nd->file);
	nd->dirinf = get_dirinf(nd->dir, nd->file);
	nd->flist = flist_new(nd->dirinf);
	nd->flist->name = ft_strdup(nd->tmp->content);
	struc->width = (int)ft_strlen(nd->tmp->content);
	get_file_inf(struc, nd->flist, ft_strdup(nd->dir));
	loop_list(struc, nd);
	struc->width += (7 - (struc->width % 8));
	print_flist_portal(struc, nd->flist);
	ft_strdel(&nd->dir);
	ft_strdel(&nd->flist->name);
}
