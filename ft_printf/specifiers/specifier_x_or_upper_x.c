/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_x_or_upper_x.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:24:50 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/11/01 17:24:50 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*specifier_x_or_upper_x(va_list args, t_params p)
{
	int				s_nbr;
	unsigned int	u_nbr;
	char			*arg;

	s_nbr = va_arg(args, int);
	if (s_nbr < 0)
		u_nbr = (4294967296 + s_nbr);
	else
		u_nbr = s_nbr;
	if (!u_nbr && !p.precision && p.precision_c)
		return (ft_strdup(""));
	arg = ft_hextoa(u_nbr);
	if (!arg)
		return (NULL);
	if (p.type == 'X')
	{
		u_nbr = -1;
		while (arg[++u_nbr])
			arg[u_nbr] = ft_toupper(arg[u_nbr]);
	}
	return (arg);
}
