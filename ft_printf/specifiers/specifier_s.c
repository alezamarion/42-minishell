/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:36 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:36 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static char	*readjusted_str(char *arg, int precision);

char	*specifier_s(va_list args, t_params p)
{
	char	*arg;

	arg = va_arg(args, char *);
	if ((!arg && p.precision_c && p.precision > 0)
		|| (!arg && !p.precision_c))
	{
		if (6 > p.precision && p.precision_c)
			return (readjusted_str("(null)", p.precision));
		return (ft_strdup("(null)"));
	}
	if ((int)ft_strlen(arg) > p.precision && p.precision_c)
		return (readjusted_str(arg, p.precision));
	if (!p.precision && p.precision_c)
		return (NULL);
	return (ft_strdup(arg));
}

static char	*readjusted_str(char *arg, int precision)
{
	char	*ptr;

	ptr = (char *)malloc(precision + 1);
	ft_strlcpy(ptr, arg, (precision + 1));
	if (!ptr)
		return (NULL);
	return (ptr);
}
