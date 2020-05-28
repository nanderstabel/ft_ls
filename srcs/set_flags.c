/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_flags.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/24 19:31:06 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/25 14:36:02 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		override(t_ls *struc, char *flags)
{
	if (ft_strchr("1Cxl", *flags))
	{
		struc->flags &= ~ONE_FLAG;
		struc->flags &= ~C_UP_FLAG;
		struc->flags &= ~X_FLAG;
		struc->flags &= ~L_FLAG;
	}
	else if (ft_strchr("cu", *flags))
	{
		struc->flags &= ~C_FLAG;
		struc->flags &= ~U_FLAG;
	}
}

static void		check_up(t_ls *struc, char *flags)
{
	if (*flags == '1')
		struc->flags |= ONE_FLAG;
	else if (*flags == 'A')
		struc->flags |= A_UP_FLAG;
	else if (*flags == 'C')
		struc->flags |= C_UP_FLAG;
	else if (*flags == 'F')
		struc->flags |= F_UP_FLAG;
	else if (*flags == 'G')
		struc->flags |= G_UP_FLAG;
	else if (*flags == 'R')
		struc->flags |= R_UP_FLAG;
	else if (*flags == 'S')
		struc->flags |= S_UP_FLAG;
	else if (*flags == 'T')
		struc->flags |= T_UP_FLAG;
	else if (*flags == 'U')
		struc->flags |= U_UP_FLAG;
}

static void		check_lower1(t_ls *struc, char *flags)
{
	if (*flags == 'a')
		struc->flags |= A_FLAG;
	if (*flags == 'c')
		struc->flags |= C_FLAG;
	if (*flags == 'd')
		struc->flags |= D_FLAG;
	if (*flags == 'f')
	{
		struc->flags |= F_FLAG;
		struc->flags |= A_FLAG;
	}
	if (*flags == 'g')
	{
		struc->flags |= G_FLAG;
		struc->flags |= L_FLAG;
	}
	if (*flags == 'i')
		struc->flags |= I_FLAG;
	if (*flags == 'l')
		struc->flags |= L_FLAG;
	if (*flags == 'm')
		struc->flags |= M_FLAG;
}

static void		check_lower2(t_ls *struc, char *flags)
{
	if (*flags == 'n')
		struc->flags |= N_FLAG;
	if (*flags == 'o')
		struc->flags |= O_FLAG;
	if (*flags == 'p')
		struc->flags |= P_FLAG;
	if (*flags == 'r')
		struc->flags |= R_FLAG;
	if (*flags == 't')
		struc->flags |= T_FLAG;
	if (*flags == 'u')
		struc->flags |= U_FLAG;
	if (*flags == 'x')
		struc->flags |= X_FLAG;
}

void			set_flags(t_ls *struc, char *flags)
{
	if (*flags != '-')
		return ;
	flags++;
	while (ft_strchr(FLAGS, *flags) && *flags)
	{
		override(struc, flags);
		check_up(struc, flags);
		check_lower1(struc, flags);
		check_lower2(struc, flags);
		flags++;
	}
	if (*flags)
	{
		ft_printf("%s %c\nusage: ls [-%s] [file ...]\n", \
				ILL_OPT, *flags, FLAGS);
		exit(1);
	}
}
