/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 21:32:08 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/09 14:46:32 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls			*set_struct(void)
{
	t_ls	*struc;

	struc = (t_ls *)malloc(sizeof(t_ls));
	struc->flags = 0;
	struc->multargs = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &struc->w);
	struc->width = 0;
	struc->nlink_width = 0;
	struc->user_width = 0;
	struc->group_width = 0;
	struc->size_width = 0;
	struc->tsize = 0;
	struc->no_dirs_spec = 0;
	struc->name = NULL;
	return (struc);
}

void			struc_zero(t_ls *struc)
{
	struc->nlink_width = 0;
	struc->user_width = 0;
	struc->group_width = 0;
	struc->size_width = 0;
	struc->tsize = 0;
	struc->no_dirs_spec = 0;
	struc->name = NULL;
}

static void		set_permissions(size_t mode, char *ret)
{
	if ((mode & S_IRUSR) == S_IRUSR)
		ret[1] = 'r';
	if ((mode & S_IWUSR) == S_IWUSR)
		ret[2] = 'w';
	if ((mode & S_IXUSR) == S_IXUSR)
		ret[3] = 'x';
	if ((mode & S_IRGRP) == S_IRGRP)
		ret[4] = 'r';
	if ((mode & S_IWGRP) == S_IWGRP)
		ret[5] = 'w';
	if ((mode & S_IXGRP) == S_IXGRP)
		ret[6] = 'x';
	if ((mode & S_IROTH) == S_IROTH)
		ret[7] = 'r';
	if ((mode & S_IWOTH) == S_IWOTH)
		ret[8] = 'w';
	if ((mode & S_IXOTH) == S_IXOTH)
		ret[9] = 'x';
}

char			*set_mode(size_t type, size_t mode, char *list)
{
	char	*ret;

	ret = ft_strnewfill(10, '-');
	if (type == DT_DIR)
		ret[0] = 'd';
	else if (type == DT_FIFO)
		ret[0] = 'p';
	else if (type == DT_SOCK)
		ret[0] = 's';
	else if (type == DT_CHR)
		ret[0] = 'c';
	else if (type == DT_BLK)
		ret[0] = 'b';
	else if (type == DT_LNK)
		ret[0] = 'l';
	set_permissions(mode, ret);
	if (*list)
		ret = ft_append(&ret, "@");
	return (ret);
}
