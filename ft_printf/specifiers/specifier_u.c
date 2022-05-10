/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:44 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:44 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*specifier_u(va_list args, t_params p)
{
	unsigned int	nbr;
	char			*arg;

	nbr = va_arg(args, unsigned int);
	if (!nbr && !p.precision && p.precision_c)
		return (ft_strdup(""));
	arg = ft_utoa(nbr);
	if (!arg)
		return (NULL);
	return (arg);
}
