/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:11:16 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/23 13:30:20 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_data *data)
{
	int	break_line;
	int	index;

	break_line = TRUE;
	if (data->argve[0][1]) // parsed_str[0])
	{
		index = 1;
		if (!ft_strncmp(data->argve[0][index], "-n", 3))
		{
			break_line = FALSE;
			index = 2;
		}
		while (data->argve[0][index])
		{
			ft_putstr_fd(data->argve[0][index], 1);
			if (data->argve[0][++index])
				ft_putchar_fd(' ', 1);
		}
		if (break_line)
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}
