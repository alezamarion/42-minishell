/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:28 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*specifier_p(va_list args)
{
	size_t	nbr;
	char	*arg;

	nbr = va_arg(args, size_t);
	arg = ft_hextoa(nbr);
	if (!arg)
		return (NULL);
	return (arg);
}
