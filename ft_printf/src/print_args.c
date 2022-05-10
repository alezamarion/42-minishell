/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:19:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:19:03 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static char	*apply_args(t_params p, va_list args);
static int	total_length(char *arg, t_params p);
static int	write_out(char *arg, t_params p, int len);

int	print_args(t_params p, va_list args)
{
	int		printed;
	int		length;
	char	*arg;

	if (p.type == '%')
		return (write(p.fd, "%%", 1));
	arg = apply_args(p, args);
	if (!arg)
		return (0);
	length = total_length(arg, p);
	printed = print_zeros_or_blank_flag(p, length, arg);
	printed += print_hash_flag(p, arg);
	printed += print_plus_or_space_flag(*arg, p, length);
	printed += print_precision(arg, p);
	printed += write_out(arg, p, ft_strlen(arg));
	if (p.zr_or_spaces == '-' && p.width > printed)
		printed += printchar(p.fd, p.width, ' ', printed);
	free(arg);
	return (printed);
}

static char	*apply_args(t_params p, va_list args)
{
	if (p.type == 'c')
		return (specifier_c(args));
	if (p.type == 'p')
		return (specifier_p(args));
	if (p.type == 's')
		return (specifier_s(args, p));
	if (p.type == 'u')
		return (specifier_u(args, p));
	if (p.type == 'd' || p.type == 'i')
		return (specifier_d_or_i(args, p));
	return (specifier_x_or_upper_x(args, p));
}

static int	total_length(char *arg, t_params p)
{
	int	len;

	len = ft_strlen(arg);
	if (p.type == 'c' && !*arg)
		return (1);
	if (p.type == 's' || p.type == 'c')
		return (len);
	if (p.precision > len)
		len = p.precision;
	if ((p.plus_or_space && *arg != '-') && (ft_strchr("diu", p.type)))
		len++;
	else if ((p.hash && ft_strchr("xX", p.type)) || (p.type == 'p'))
		len += 2;
	else if (*arg == '-' && p.precision < p.width
		&& (p.precision_c && p.precision < (len - 1)))
		len--;
	return (len);
}

static int	write_out(char *arg, t_params p, int len)
{
	if (!*arg && p.type == 'c')
		return (write(p.fd, "\0", 1));
	else if (*arg == '-' && ft_strchr("di", p.type))
	{
		if ((len > p.precision && len >= p.width) || \
			(len >= p.width && !p.precision_c) || \
			(len > p.precision && p.zr_or_spaces != '0') || \
			(len > p.precision && p.width > len && p.precision_c))
			return (write(p.fd, arg, len));
		return (write(p.fd, arg + 1, len - 1));
	}
	return (write(p.fd, arg, len));
}
