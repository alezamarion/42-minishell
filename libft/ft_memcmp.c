/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:27:58 by azamario          #+#    #+#             */
/*   Updated: 2021/10/14 18:07:50 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*t1;
	const char	*t2;

	t1 = (const char *)s1;
	t2 = (const char *)s2;
	while (n > 0)
	{
		if (*t1 != *t2)
			return ((unsigned char)*t1 - (unsigned char)*t2);
		t1++;
		t2++;
		n--;
	}
	return (0);
}
