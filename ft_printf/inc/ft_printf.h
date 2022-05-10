/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:15:39 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/16 20:15:39 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../../libft/libft.h"

# define STDOUT 1
# define STDIN 0
# define STDERR 2
# define LIMIT 2147483614
# define TYPES "cspdiuxX%"
# define FLAGS "# +0-"

typedef const char	t_str;

typedef struct s_params
{
	int		fd;
	char	type;
	char	hash;
	char	plus_or_space;
	char	zr_or_spaces;
	char	precision_c;
	int		precision;
	int		width;
}	t_params;

int		ft_printf(int fd, t_str *format, ...);
int		print_args(t_params params, va_list args);
int		is_valid(t_str *format, t_params *p, va_list args);

char	*specifier_c(va_list args);
char	*specifier_p(va_list args);
char	*specifier_s(va_list args, t_params params);
char	*specifier_u(va_list args, t_params params);
char	*specifier_d_or_i(va_list args, t_params params);
char	*specifier_x_or_upper_x(va_list args, t_params params);

char	*ft_utoa(unsigned int nbr);
char	*ft_hextoa(size_t nbr);

int		printchar(int fd, int width, char c, int offset);
t_str	*toward_specifier(t_str *format);

int		print_hash_flag(t_params params, char *arg);
int		print_precision(char *arg, t_params params);
int		print_plus_or_space_flag(char arg, t_params params, int len);
int		print_zeros_or_blank_flag(t_params params, int len, char *arg);

#endif