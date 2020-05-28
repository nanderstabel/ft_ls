/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_args.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/07 10:32:36 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/30 12:11:46 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		reverse_sort(char **argv)
{
	int		i;

	i = 0;
	while (argv[i] && argv[i + 1])
	{
		if (ft_strcmp(argv[i], argv[i + 1]) < 0)
		{
			ft_swap((void *)&argv[i], (void *)&argv[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

static void		sort(char **argv)
{
	int		i;

	i = 0;
	while (argv[i] && argv[i + 1])
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			ft_swap((void *)&argv[i], (void *)&argv[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

static void		time_sort(char **argv)
{
	struct stat		file1;
	struct stat		file2;
	int				i;

	i = 0;
	while (argv[i] && argv[i + 1])
	{
		stat(argv[i], &file1);
		stat(argv[i + 1], &file2);
		if (file1.st_mtimespec.tv_sec < file2.st_mtimespec.tv_sec || \
			(file1.st_mtimespec.tv_sec == file2.st_mtimespec.tv_sec && \
			ft_strcmp(argv[i], argv[i + 1]) > 0))
		{
			ft_swap((void *)&argv[i], (void *)&argv[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

static void		sort_files(t_ls *struc, char **argv)
{
	struct stat		file;
	char			*tmp;

	while (*argv)
	{
		tmp = ft_strdup(*argv);
		if (!ft_strchr(tmp, '/'))
			tmp = ft_prepend(&tmp, "./");
		if (lstat(tmp, &file) == -1)
			ft_lstpush(&struc->no_files, ft_lstnew(*argv, \
			ft_strlen(*argv)));
		else
		{
			if ((file.st_mode & S_IFDIR) == S_IFDIR && \
				(struc->flags & D_FLAG) != D_FLAG)
				ft_lstpush(&struc->dirs, ft_lstnew(*argv, \
				ft_strlen(*argv)));
			else
				ft_lstpush(&struc->no_dirs, ft_lstnew(*argv, \
				ft_strlen(*argv)));
		}
		ft_strdel(&tmp);
		++argv;
	}
}

void			sort_args(t_ls *struc, char **argv)
{
	t_list		*tmp;

	struc->dirs = ft_lstnew("Head", 4);
	struc->no_dirs = ft_lstnew("Head", 4);
	struc->no_files = ft_lstnew("Head", 4);
	if ((struc->flags & F_FLAG) != F_FLAG)
	{
		if (struc->flags & T_FLAG)
			time_sort(argv);
		else
			sort(argv);
		if (struc->flags & R_FLAG)
			reverse_sort(argv);
	}
	if (((struc->flags & D_FLAG) == D_FLAG) && *argv == NULL)
		ft_lstpush(&struc->no_dirs, ft_lstnew(".", 1));
	sort_files(struc, argv);
	tmp = struc->no_files->next;
	while (tmp)
	{
		struc->multargs = 1;
		ft_printf("ft_ls: %s: No such file or directory\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstdel(&struc->no_files, ft_freezero);
}
