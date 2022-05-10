/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:11:16 by ebresser          #+#    #+#             */
/*   Updated: 2022/04/27 22:51:52 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(t_data *data, int id)
{
	int	break_line;
	int	index;

	break_line = TRUE;
	if (data->argve[id][1])
	{
		index = 1;
		if (!ft_strncmp(data->argve[id][index], "-n", 3))
		{
			break_line = FALSE;
			index = 2;
		}
		while (data->argve[id][index])
		{
			ft_putstr_fd(data->argve[id][index], 1);
			if (data->argve[id][++index])
				ft_putchar_fd(' ', 1);
		}
		if (break_line)
			ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("\n", 1);
}
