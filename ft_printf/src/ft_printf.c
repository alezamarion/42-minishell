/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 20:17:24 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/08/16 20:17:24 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_printf(int fd, const char *format, ...)
{
	int			printed;
	int			option;
	va_list		args;
	t_params	params;

	printed = 0;
	params.fd = fd;
	va_start(args, format);
	while (*format)
	{
		option = is_valid(format + 1, &params, args);
		if (!option)
			printed += (write(params.fd, format++, 1));
		else if (option > 0)
		{
			printed += print_args(params, args);
			format = toward_specifier(format + 1);
		}
		else
			return (-1);
	}
	va_end(args);
	return (printed);
}
