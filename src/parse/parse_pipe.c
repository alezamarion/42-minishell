/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:30:47 by joeduard          #+#    #+#             */
/*   Updated: 2022/03/15 17:21:27 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function for finding pipe
int	parse_pipe(char *str, char **strpiped)
{
	int	i;

	i = 0;
	while (i++ < 2)
	{
		strpiped[i] = strsep(&str, "|");   // ls -l | grep documents
		if (strpiped[i] == NULL)
			break ;
	}
	if (strpiped[1] == NULL)
		return (0);
	else
		return (1);
}
