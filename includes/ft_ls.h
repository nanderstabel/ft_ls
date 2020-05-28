/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/24 18:03:16 by nstabel        #+#    #+#                */
/*   Updated: 2019/07/11 20:34:01 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "ft_printf.h"
# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <stdio.h>
# include <errno.h>

# define SIX_MONTH	15778463
# define ILL_OPT	"ls: illegal option --"
# define FLAGS		"RTadfglmrt"
# define ONE_FLAG	(1 << 0)
# define A_UP_FLAG	(1 << 1)
# define C_UP_FLAG	(1 << 2)
# define F_UP_FLAG	(1 << 3)
# define G_UP_FLAG	(1 << 4)
# define R_UP_FLAG	(1 << 5)
# define S_UP_FLAG	(1 << 6)
# define T_UP_FLAG	(1 << 7)
# define U_UP_FLAG	(1 << 8)
# define A_FLAG		(1 << 9)
# define C_FLAG		(1 << 10)
# define D_FLAG		(1 << 11)
# define F_FLAG		(1 << 12)
# define G_FLAG		(1 << 13)
# define I_FLAG		(1 << 14)
# define L_FLAG		(1 << 15)
# define M_FLAG		(1 << 16)
# define N_FLAG		(1 << 17)
# define O_FLAG		(1 << 18)
# define P_FLAG		(1 << 19)
# define R_FLAG		(1 << 20)
# define T_FLAG		(1 << 21)
# define U_FLAG		(1 << 22)
# define X_FLAG		(1 << 23)

typedef struct		s_files
{
	struct dirent	*sdirinf;
	struct stat		*sfile;
	char			*name;
	char			*dir;
	char			*file;
	char			*symlink;
	char			special;
	char			minor;
	char			major;
	char			*mode;
	int				nlink;
	char			*user;
	char			*group;
	long long int	size;
	char			*time;
	struct s_files	*next;
}					t_files;

typedef struct		s_ls
{
	unsigned int	flags;
	t_list			*dirs;
	t_list			*no_dirs;
	int				no_dirs_spec;
	t_list			*no_files;
	char			multargs;
	struct winsize	w;
	int				nlink_width;
	int				user_width;
	int				group_width;
	int				size_width;
	int				tsize;
	unsigned short	width;
	char			*name;
}					t_ls;

typedef struct		s_nodirs
{
	struct dirent	*dirinf;
	t_files			*flist;
	t_list			*tmp;
	char			*dir;
	char			*file;
}					t_nodirs;

void				flist_append(t_ls *struc, t_files **flist, \
					struct dirent *sdirinf, char *dpath);
void				flist_del(t_files **flist);
t_files				*flist_new(struct dirent *sdirinf);
void				ft_ls(t_ls *struc, char *dpath);
void				get_file_inf(t_ls *struc, t_files *flist, char *sdpath);
t_files				*get_flist(t_ls *struc, DIR *sdir, char *dpath);
t_files				*merge_flists_time(t_files *a, t_files *b);
t_files				*merge_flists_time_reverse(t_files *a, t_files *b);
t_files				*merge_flists(t_files *a, t_files *b);
t_files				*merge_flists_reverse(t_files *a, t_files *b);
void				partition(t_files *head, t_files **front, t_files **back);
void				print_flist_portal(t_ls *struc, t_files *flist);
void				print_no_dirs(t_ls *struc);
void				set_flags(t_ls *struc, char *flags);
char				*set_mode(size_t type, size_t mode, char *list);
t_ls				*set_struct(void);
void				set_time(t_ls *struc, t_files *flist);
void				sort_args(t_ls *struc, char **argv);
void				sort_flist(t_ls *struc, t_files **flist);
void				struc_zero(t_ls *struc);

#endif
