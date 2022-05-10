/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_d_or_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:21 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:21 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*specifier_d_or_i(va_list args, t_params params)
{
	int		nbr;
	char	*arg;

	nbr = va_arg(args, int);
	if (!params.precision && !nbr && params.precision_c)
		return (ft_strdup(""));
	arg = ft_itoa(nbr);
	if (!arg)
		return (NULL);
	return (arg);
}
