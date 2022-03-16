/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:34:23 by azamario          #+#    #+#             */
/*   Updated: 2021/10/14 17:58:06 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*src_aux;
	unsigned char	*dst_aux;

	src_aux = (unsigned char *)src;
	dst_aux = (unsigned char *)dst;
	while (n > 0)
	{
		*(dst_aux++) = *src_aux;
		if (*src_aux == (unsigned char)c)
			return (dst_aux);
		src_aux++;
		n--;
	}
	return (0);
}
