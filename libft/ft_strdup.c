/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azamario <azamario@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 18:01:14 by azamario          #+#    #+#             */
/*   Updated: 2021/10/14 18:00:17 by azamario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*new;

	i = 0;
	size = ft_strlen(s1);
	new = (char *)ft_calloc(size + 1, sizeof(char));
	if (new != NULL)
	{
		while (i < size)
		{
			new[i] = s1[i];
			i++;
		}
	}
	return (new);
}
