/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   merge_flist.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/05 17:59:02 by nstabel        #+#    #+#                */
/*   Updated: 2019/08/29 12:56:46 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		partition(t_files *head, t_files **front, t_files **back)
{
	t_files		*fast;
	t_files		*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

t_files		*merge_flists_reverse(t_files *a, t_files *b)
{
	t_files		*ret;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->sdirinf->d_name, b->sdirinf->d_name) > 0)
	{
		ret = a;
		ret->next = merge_flists_reverse(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge_flists_reverse(a, b->next);
	}
	return (ret);
}

t_files		*merge_flists(t_files *a, t_files *b)
{
	t_files		*ret;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->sdirinf->d_name, b->sdirinf->d_name) < 0)
	{
		ret = a;
		ret->next = merge_flists(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge_flists(a, b->next);
	}
	return (ret);
}

t_files		*merge_flists_time_reverse(t_files *a, t_files *b)
{
	t_files		*ret;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->sfile->st_mtimespec.tv_sec < b->sfile->st_mtimespec.tv_sec)
	{
		ret = a;
		ret->next = merge_flists_time_reverse(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge_flists_time_reverse(a, b->next);
	}
	return (ret);
}

t_files		*merge_flists_time(t_files *a, t_files *b)
{
	t_files		*ret;

	ret = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if ((a->sfile->st_mtimespec.tv_sec > b->sfile->st_mtimespec.tv_sec) || \
		(a->sfile->st_mtimespec.tv_sec == b->sfile->st_mtimespec.tv_sec && \
		ft_strcmp(a->sdirinf->d_name, b->sdirinf->d_name) < 0))
	{
		ret = a;
		ret->next = merge_flists_time(a->next, b);
	}
	else
	{
		ret = b;
		ret->next = merge_flists_time(a, b->next);
	}
	return (ret);
}
