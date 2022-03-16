/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:03:11 by azamario          #+#    #+#             */
/*   Updated: 2021/10/14 17:58:39 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src_aux;
	char		*dst_aux;

	if (dst == src)
		return (dst);
	src_aux = (const char *)src;
	dst_aux = (char *)dst;
	while (n > 0)
	{
		*(dst_aux++) = *(src_aux++);
		n--;
	}
	return (dst);
}
