/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mult_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:32:06 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/15 12:13:22 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_mult_join(unsigned int nbr_of_strs, ...)
{
	va_list			args;
	char			*final_str;
	char			*str_n;
	char			*buf;
	unsigned int	i;

	va_start(args, nbr_of_strs);
	final_str = NULL;
	i = 0;
	while (i < nbr_of_strs)
	{
		str_n = va_arg(args, char *);
		if (!final_str)
			final_str = ft_strdup(str_n);
		else
		{
			buf = ft_strjoin(final_str, str_n);
			free(final_str);
			final_str = ft_strdup(buf);
			free(buf);
		}
		i++;
	}
	va_end(args);
	return (final_str);
}
