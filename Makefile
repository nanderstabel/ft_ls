# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nstabel <nstabel@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/06/08 07:56:59 by nstabel        #+#    #+#                 #
#    Updated: 2019/07/10 16:08:32 by nstabel       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

INCL = -I ./includes/

LIBFT = ./libft/

PRINTF = $(LIBFT)ft_printf/src/

FT_LS = ./srcs/

LIBFT_O = ft_atoi.o ft_bzero.o ft_isalnum.o \
		ft_isalpha.o ft_isascii.o ft_isdigit.o \
		ft_isprint.o ft_itoa.o ft_memalloc.o \
		ft_memccpy.o ft_memchr.o ft_memcmp.o \
		ft_memcpy.o ft_memdel.o ft_memmove.o \
		ft_memset.o ft_putchar_fd.o ft_putchar.o \
		ft_putendl_fd.o ft_putendl.o ft_putnbr_fd.o \
		ft_putnbr.o ft_putstr_fd.o ft_putstr.o \
		ft_skipspc.o ft_strcat.o ft_strchr.o \
		ft_strclr.o ft_strcmp.o ft_strcpy.o \
		ft_strdel.o ft_strdup.o ft_strequ.o \
		ft_striter.o ft_striteri.o ft_strjoin.o \
		ft_strlcat.o ft_strlen.o ft_strmap.o \
		ft_strmapi.o ft_strncat.o ft_strncmp.o \
		ft_strncpy.o ft_strnequ.o ft_strnew.o \
		ft_strnstr.o ft_strrchr.o ft_strrev.o \
		ft_strsplit.o ft_strstr.o ft_strsub.o \
		ft_strtrim.o ft_tolower.o ft_toupper.o \
		ft_end.o ft_start.o ft_lstnew.o \
		ft_lstdelone.o ft_lstdel.o ft_lstadd.o \
		ft_lstiter.o ft_lstmap.o ft_count_words.o \
		ft_itoa_base.o ft_prepend.o ft_append.o \
		ft_strlwr.o ft_strupr.o ft_insert.o \
		ft_replace.o ft_strnewfill.o ft_strcalc_add.o \
		ft_strcalc_mult.o ft_strcalc_div.o \
		ft_strcalc_multexptwo.o ft_strcalc_valid.o \
		ft_select.o ft_nchar.o ft_putnstr.o \
		ft_itoa_long.o ft_swap.o ft_lstpush.o \
		ft_freezero.o ft_strrstr.o ft_rnchar.o \
		ft_strcut.o

PRINTF_O = color_output.o conversion_c_special.o \
		conversion_c.o conversion_e.o \
		conversion_e_utillities.o \
		conversion_e_long.o conversion_f_long.o \
		conversion_f_tfloat_long.o conversion_f.o \
		conversion_f_tfloat.o conversion_p.o \
		conversion_f_utillities.o conversion_s.o \
		conversion_f_utillities2.o main.o \
		conversion_f_utillities3.o utillities.o \
		utillities2.o main_conversion.o \
		conversion_signed_utillities.o \
		conversion_signed_utillities2.o \
		conversion_signed.o conversion_unsigned.o \
		
FTLS_O = ft_ls.o set_flags.o get_flist.o merge_flist.o \
		sort_args.o utilities.o file_inf.o print.o \
		print_no_dirs.o file_inf2.o

SRCS_O = $(LIBFT_O) $(PRINTF_O) $(FTLS_O)

all: $(NAME)

$(NAME): $(SRCS_O)
	@gcc -g $(FLAGS) -o $(NAME) $(SRCS_O)

$(LIBFT_O): %.o: $(LIBFT)/%.c
	@gcc -c -g $(FLAGS) $(INCL) $< -o $@

$(PRINTF_O): %.o: $(PRINTF)/%.c
	@gcc -c -g $(FLAGS) $(INCL) $< -o $@

$(FTLS_O): %.o: $(FT_LS)/%.c
	@gcc -c -g $(FLAGS) $(INCL) $< -o $@

clean:
	@rm -rf $(SRCS_O) $(NAME).dSYM

fclean: clean
	@rm -rf $(NAME)

re: fclean all
