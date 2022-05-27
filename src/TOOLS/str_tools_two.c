/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tools_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 21:53:45 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/17 23:29:51 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_space(int c);

int	is_space_str(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	if (i == ft_strlen(s))
		return (TRUE);
	return (FALSE);
}

static int	is_space(int c)
{
	if (c == ' ')
		return (1);
	return (0);
}
