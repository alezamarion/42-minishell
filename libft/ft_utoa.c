/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:40:08 by vlima-nu          #+#    #+#             */
/*   Updated: 2021/10/07 00:40:44 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int nbr)
{
	unsigned int	temp;
	int				size;
	char			*string;

	temp = nbr;
	size = 0;
	while (temp || !size)
	{
		temp /= 10;
		size++;
	}
	string = (char *)malloc(size + 1);
	string[size--] = 0;
	while (size >= 0)
	{
		string[size--] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (string);
}
