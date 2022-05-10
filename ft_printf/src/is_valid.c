/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:18:08 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:18:08 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static t_str	*set_precision(t_str *format, t_params *p, va_list args);
static t_str	*set_width(t_str *format, t_params *p, va_list args);
static t_str	*set_flags(t_str *format, t_params *p);
static int		find_error(t_str *format, t_params *p);

int	is_valid(t_str *format, t_params *p, va_list args)
{
	if (*(format - 1) == '%')
	{
		ft_bzero(p, sizeof(t_params));
		format = set_flags(format, p);
		format = set_width(format, p, args);
		if (*format == '.')
			format = set_precision(++format, p, args);
		if (p->precision <= LIMIT && p->width <= LIMIT && p->precision >= 0)
		{
			if (ft_strchr(TYPES, *format) && *format)
			{
				p->type = *format;
				return (1);
			}
		}
		return (find_error(format, p));
	}
	return (0);
}

static t_str	*set_flags(t_str *format, t_params *p)
{
	while (ft_strchr(FLAGS, *format))
	{
		if (*format == '#')
			p->hash = '#';
		else if (*format == '+')
			p->plus_or_space = '+';
		else if (*format == ' ' && !p->plus_or_space)
			p->plus_or_space = ' ';
		else if (*format == '-')
			p->zr_or_spaces = '-';
		else if (*format == '0' && !p->zr_or_spaces)
			p->zr_or_spaces = '0';
		format++;
	}
	return (format);
}

static t_str	*set_width(t_str *format, t_params *p, va_list args)
{
	if (*format == '*' && (ft_strchr(TYPES, *(format + 1)) || \
		*(format + 1) == '.'))
	{
		p->width = va_arg(args, int);
		if (p->width < 0 && p->zr_or_spaces != '-')
		{
			p->width *= -1;
			p->zr_or_spaces = '-';
		}
		format++;
	}
	while (ft_isdigit(*format))
	{
		p->width = p->width * 10 + *format - 48;
		format++;
	}
	return (format);
}

static t_str	*set_precision(t_str *format, t_params *p, va_list args)
{
	p->precision_c = 1;
	if (*format == '*' && ft_strchr(TYPES, *(format + 1)))
	{
		p->precision = va_arg(args, int);
		if (p->precision < 0)
			p->precision = 1;
		return (format += 2);
	}
	while (ft_isdigit(*format))
	{
		p->precision = p->precision * 10 + *format - 48;
		format++;
	}
	return (format);
}

static int	find_error(t_str *format, t_params *p)
{
	if (p->width > LIMIT || p->precision > LIMIT)
		return (-1);
	if (!*format)
		return (-1);
	return (0);
}
