/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsplit.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/06 18:13:12 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/22 17:35:34 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strsublen(char *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, char c)
{
	int		nwords;
	char	**tab;
	int		i;

	if (s == NULL)
		return (NULL);
	nwords = ft_count_words((char *)s, c);
	tab = (char **)malloc(1 + nwords * sizeof(char *));
	i = 0;
	if (tab == NULL)
		return (NULL);
	while (i < nwords)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		tab[i] = ft_strsub((char *)s, 0, ft_strsublen((char *)s, c));
		s += ft_strsublen((char *)s, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
