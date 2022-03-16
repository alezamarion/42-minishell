/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:07:23 by azamario          #+#    #+#             */
/*   Updated: 2021/10/14 18:00:54 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*src_aux;

	if (!dst || !src)
		return (0);
	src_aux = (const char *)src;
	if (size > 0)
	{
		while (size > 1 && *src_aux)
		{
			*(dst++) = *(src_aux++);
			size--;
		}
		*dst = '\0';
	}
	return (ft_strlen(src));
}
