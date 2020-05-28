/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcalc_add.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/23 20:44:43 by nstabel        #+#    #+#                */
/*   Updated: 2019/05/23 20:55:42 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_after(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	save;
	char	*ret;

	i = 1;
	save = 0;
	ret = (ft_strlen(s1) > ft_strlen(s2)) ? ft_strdup(s1) : ft_strdup(s2);
	while (s1[i] && s2[i])
	{
		save = (s1[i] - '0') + (s2[i] - '0');
		ret[i] = (save % 10) + '0';
		j = 1;
		while (save >= 10)
		{
			ret[i - j]++;
			if (ret[i - j] != ':')
				break ;
			ret[i - j] = '0';
			j++;
		}
		i++;
	}
	return ((ret[0] == '/') ? ft_replace(&ret, "1.", 0, 1) : ret);
}

char			*ft_strcalc_add(char **nb, const char *s2)
{
	char	*ret;
	char	*frac;

	if (!ft_strcalc_valid(*nb) || !ft_strcalc_valid((char *)s2))
		return (NULL);
	ret = ft_itoa(ft_atoi(*nb) + ft_atoi(s2));
	if (ft_strchr(*nb, '.') == NULL)
		*nb = ft_append(nb, ".0");
	if (ft_strchr(s2, '.') == NULL)
		frac = ft_strdup(ft_strchr(*nb, '.'));
	else
		frac = ft_after(ft_strchr(*nb, '.'), ft_strchr(s2, '.'));
	if (frac[0] == '1')
	{
		ret = ft_itoa(ft_atoi(ret) + 1);
		frac = ft_replace(&frac, "", 0, 1);
	}
	ret = ft_append(&ret, frac);
	ft_strdel(nb);
	ft_strdel(&frac);
	return (ret);
}
