/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgross <mgross@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/11 12:53:48 by mgross         #+#    #+#                */
/*   Updated: 2019/06/08 08:17:14 by nstabel       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define BUFF_SIZE_PF	4096
# define FLAG_L			(1 << 0)
# define FLAG_LL		(1 << 1)
# define FLAG_H			(1 << 2)
# define FLAG_HH		(1 << 3)
# define FLAG_HASH		(1 << 4)
# define FLAG_MIN		(1 << 5)
# define FLAG_PLUS		(1 << 6)
# define FLAG_ZERO		(1 << 7)
# define FLAG_SPACE		(1 << 8)
# define FLAG_PSTAR		(1 << 9)
# define FLAG_WSTAR 	(1 << 10)
# define FLAG_L_UP		(1 << 11)
# define FLAG_DOL		(1 << 12)

# define BOLD			"\x1B[1m"
# define ITALICS		"\x1B[3m"
# define UNDERLINE		"\x1B[4m"
# define INVERSE		"\x1B[7m"
# define BOLD_OFF		"\x1B[22m"
# define ITALICS_OFF	"\x1B[23m"
# define UNDERLINE_OFF	"\x1B[24m"
# define INVERSE_OFF	"\x1B[27m"
# define BLACK 			"\x1B[30m"
# define RED 			"\x1B[31m"
# define GREEN 			"\x1B[32m"
# define YELLOW 		"\x1B[33m"
# define BLUE 			"\x1B[34m"
# define MAGENTA 		"\x1B[35m"
# define CYAN 			"\x1B[36m"
# define WHITE 			"\x1B[37m"
# define EOC 			"\e[0m"

typedef struct	s_flags
{
	va_list		start;
	short		flag;
	int			arg_index;
	int			width;
	int			num;
	int			delim;
	int			i;
	int			precision;
	char		specifier;
	char		*str;
	char		buf[BUFF_SIZE_PF];
}				t_flags;

typedef struct	s_params
{
	int			exp_max;
	int			exp_min;
	int			exp_true_min;
	int			exp_field;
	int			frac_field;
}				t_params;

typedef struct	s_float
{
	t_params	*params;
	long double	nb_long;
	double		nb;
	int			sign;
	int			dec_exp;
	char		*bin_exp;
	long double	dec_frac_long;
	double		dec_frac;
	char		*bin_frac;
	char		**frac_tab;
	int			extension;
	char		*output;
	int			precision;
}				t_float;

void			main_conversion(t_flags *conv, va_list ap);
void			clear_struct(t_flags *conv);
void			print_buf(t_flags *conv);
void			conversion_c(t_flags *conv, va_list ap);
void			conversion_c(t_flags *conv, va_list ap);
void			conversion_s(t_flags *conv, va_list ap);
void			conversion_p(t_flags *conv, va_list ap);
void			conversion_unsigned(t_flags *conv, va_list ap);
void			clear_plus_space_flags(t_flags *conv);
void			clear_plus_space_flags2(t_flags *conv, long long nb);
void			conversion_signed(t_flags *conv, va_list ap);
void			conversion_f(t_flags *conv, va_list ap, t_float *dbl);
void			get_tfloat(t_float *dbl);
char			**get_fraction_tab(int exponent);
int				special_nb(t_float *dbl);
void			set_params(t_flags *conv, t_float *dbl);
void			while_to_buf(t_flags *conv, int number, char c);
void			putnbr_to_buf(t_flags *conv);
long long		length_overflow_di(t_flags *conv, long long nb);
void			color_output(t_flags *conv, const char **format);
void			conversion_f_redirect(t_flags *conv, t_float *dbl);
char			*strcalc_add(char **nb, const char *s2);
char			*strcalc_mult(char **nb);
char			*strcalc_div(char **nb);
char			*strcalc_multexptwo(char **nb, int exponent);
void			conversion_f_precision(t_flags *conv, t_float *dbl, int min);
void			clear_tfloat(t_float *dbl);
void			arg_index(t_flags *conv, const char **format, va_list ap);
void			conversion_e(t_flags *conv, va_list ap);
void			conversion_e_long(t_flags *conv, va_list ap);
void			main_precision(t_flags *conv, const char **format, va_list ap);
void			conversion_f_infnan(t_flags *conv, t_float *dbl);
void			conversion_f_direct(t_flags *conv, t_float *dbl);
void			conversion_f_width(t_flags *conv, t_float *dbl);
void			put_flags_to_buf(t_flags *conv);
void			conversion_f_precision2(t_flags *conv, t_float *dbl,
				int rounding);
int				special_nb_long(t_float *dbl);
void			get_tfloat_long(t_float *dbl);
void			get_output(t_float *dbl);
void			get_fraction(t_float *dbl);
void			get_exponent(t_float *dbl);
void			conversion_f_long(t_flags *conv, va_list ap, t_float *dbl);
void			specifier_g_adjust(t_float *dbl);
void			put_e_to_buf(t_flags *conv, char *str);
void			conversion_e_flags(t_flags *conv, t_float *dbl);
void			conversion_e_width(t_flags *conv, t_float *dbl);
void			clear_tfloat_e(t_float *dbl);
void			conversion_c_special(t_flags *conv);
void			replace_delim(t_flags *conv);
void			initiate_struct(t_flags *conv);
void			redirect2(t_flags *conv, int len, long long nb);
void			conversion_signed_width(t_flags *conv, int len, long long nb);
void			putflags_and_precision_to_buf(t_flags *conv, int min);
void			precision_signed(t_flags *conv, int len, long long nb);
void			redirect(t_flags *conv, long long nb);
char			zero_space(t_flags *conv);
char			plus_min(t_flags *conv);
void			f_rounding_up(t_float *dbl, int rounding);
void			new_str(t_flags *conv);
void			clear_fraction_tab(t_float *dbl);
void			no_conversion(t_flags *conv, const char **format);

#endif
