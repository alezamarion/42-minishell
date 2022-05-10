/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:13 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:13 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*specifier_c(va_list args)
{
	char	*arg;

	arg = (char *)malloc(2 * sizeof(char));
	if (!arg)
		return (NULL);
	*arg = va_arg(args, int);
	*(arg + 1) = 0;
	return (arg);
}
