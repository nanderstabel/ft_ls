/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nstabel <nstabel@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/08 15:18:01 by nstabel        #+#    #+#                */
/*   Updated: 2019/06/03 13:45:57 by mgross        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** This function searches for specific definition inside the string. If it
** finds a corresponding one, it writes the # define code from the header
** onto the string.
*/

static int	set_style(t_flags *conv, char *style)
{
	if (ft_strequ(style, "bright") || ft_strequ(style, "bold"))
		write(1, BOLD, 4);
	else if (ft_strequ(style, "italics"))
		write(1, ITALICS, 4);
	else if (ft_strequ(style, "underline"))
		write(1, UNDERLINE, 4);
	else if (ft_strequ(style, "eoc"))
		write(1, EOC, 4);
	else
		return (0);
	conv->num += 4;
	return (1);
}

/*
** This function searches for specific definition inside the string. If it
** finds a corresponding one, it writes the # define code from the header
** onto the string.
*/

static int	set_color(t_flags *conv, char *color)
{
	if (ft_strequ(color, "black"))
		write(1, BLACK, 5);
	else if (ft_strequ(color, "red"))
		write(1, RED, 5);
	else if (ft_strequ(color, "green"))
		write(1, GREEN, 5);
	else if (ft_strequ(color, "yellow"))
		write(1, YELLOW, 5);
	else if (ft_strequ(color, "blue"))
		write(1, BLUE, 5);
	else if (ft_strequ(color, "magenta"))
		write(1, MAGENTA, 5);
	else if (ft_strequ(color, "cyan"))
		write(1, CYAN, 5);
	else if (ft_strequ(color, "white"))
		write(1, WHITE, 5);
	else
		return (0);
	conv->num += 5;
	return (1);
}

/*
** This function searches for specific definition inside the string. If it
** finds a corresponding one, it writes the # define code from the header
** onto the string.
*/

static int	set_off(t_flags *conv, char *off)
{
	if (ft_strequ(off, "bright off") || ft_strequ(off, "bold off"))
		write(1, BOLD_OFF, 5);
	else if (ft_strequ(off, "italics off"))
		write(1, ITALICS_OFF, 5);
	else if (ft_strequ(off, "underline off"))
		write(1, UNDERLINE_OFF, 5);
	else
		return (0);
	conv->num += 5;
	return (1);
}

/*
** This function copies the color specifications into a string then empty's
** the buf, and sends the string with the style specification to the diffrent
** functions to write to the buf.
*/

void		color_output(t_flags *conv, const char **format)
{
	char		*ansi;
	const char	*find;
	int			i;
	int			len;

	find = *format;
	len = ft_nchar(find, '}');
	find++;
	ansi = ft_strnew(len);
	i = 0;
	while (*find != '}')
	{
		ansi[i] = *find;
		find++;
		i++;
	}
	print_buf(conv);
	if (set_style(conv, ansi) + set_color(conv, ansi) + set_off(conv, ansi))
	{
		*format = find + 1;
		if (**format == '{')
			color_output(conv, format);
	}
	ft_strdel(&ansi);
}
