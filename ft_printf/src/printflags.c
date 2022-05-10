/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 02:00:06 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/28 02:00:06 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	zero_flag(t_params p, int len);

int	print_hash_flag(t_params p, char *arg)
{
	if (((ft_strchr("xX", p.type) && p.hash) || (p.type == 'p'))
		&& (p.zr_or_spaces == '0' && !p.precision_c))
		return (0);
	if (!ft_strcmp(arg, "0") && p.type != 'p')
		return (0);
	if ((p.type == 'x' && p.hash) || (p.type == 'p'))
		return (write(p.fd, "0x", 2));
	if (p.type == 'X' && p.hash)
		return (write(p.fd, "0X", 2));
	return (0);
}

int	print_zeros_or_blank_flag(t_params p, int len, char *arg)
{
	if ((!p.zr_or_spaces && p.width > len)
		|| (ft_strchr("cs", p.type) && p.zr_or_spaces == '0'))
		return (printchar(p.fd, p.width, ' ', len));
	if (p.zr_or_spaces == '0' && p.width > len)
	{
		if (*arg == '-' && ft_strchr("di", p.type))
		{
			if (p.precision_c)
				return (zero_flag(p, len + 1));
			return (write(p.fd, "-", 1) + zero_flag(p, len));
		}
		if (p.plus_or_space && ft_strchr("di", p.type) && !p.precision_c)
			return (write(p.fd, &p.plus_or_space, 1) + zero_flag(p, len));
		return (zero_flag(p, len));
	}
	return (0);
}

static int	zero_flag(t_params p, int len)
{
	if (p.precision <= len && p.precision >= 0 && p.precision_c)
		return (printchar(p.fd, p.width, ' ', len));
	if (p.precision >= p.width && p.precision_c)
		return (printchar(p.fd, p.precision, '0', len));
	if (p.precision < p.width && p.precision >= 0 && p.precision_c)
		return (printchar(p.fd, p.width - p.precision, ' ', 0));
	if ((ft_strchr("xX", p.type) && p.hash) || (p.type == 'p'))
	{
		if (p.type == 'X')
			return (write(p.fd, "0X", 2) + printchar(p.fd, p.width, '0', len));
		return (write(p.fd, "0x", 2) + printchar(p.fd, p.width, '0', len));
	}
	return (printchar(p.fd, p.width, '0', len));
}

int	print_plus_or_space_flag(char arg, t_params p, int len)
{
	if (ft_strchr("diu", p.type) && (arg != '-'))
	{
		if (p.plus_or_space && (p.zr_or_spaces != '0'
				|| p.width <= len
				|| (p.precision <= (len - 1) && p.precision_c)))
			return (write(p.fd, &p.plus_or_space, 1));
	}
	return (0);
}

int	print_precision(char *arg, t_params p)
{
	int		len;
	int		minus;

	if (ft_strchr("cs", p.type) || !p.precision_c)
		return (0);
	minus = (*arg == '-' && ft_strchr("di", p.type));
	len = ft_strlen(arg + minus);
	if (p.precision <= len)
		return (0);
	if (minus)
		return (write(p.fd, "-", 1) + \
			printchar(p.fd, p.precision - len, '0', 0));
	return (printchar(p.fd, p.precision - len, '0', 0));
}
