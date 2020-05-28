/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_words.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/13 15:09:57 by nstabel        #+#    #+#                */
/*   Updated: 2019/02/22 13:03:51 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_words(char const *s, char c)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
			if (s[i] != c && s[i] != '\0')
				cnt++;
		}
		i++;
	}
	if (s[0] != c && s[0] != '\0')
		cnt++;
	return (cnt);
}
