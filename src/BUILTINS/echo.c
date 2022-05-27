/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:11:16 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 20:33:01 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(t_data *data, int id, int *index);
static int	is_n_str(char *s);

void	echo(t_data *data, int id)
{
	int	break_line;
	int	index;

	index = 1;
	if (data->argve[id][index])
	{
		break_line = is_n_flag(data, id, &index);
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

static int	is_n_flag(t_data *data, int id, int *index)
{
	int	break_line;

	break_line = 1;
	while (data->argve[id][*index])
	{
		if (!ft_strncmp(data->argve[id][*index], "-n", 2))
		{
			if (data->argve[id][*index][2] == '\0' ||
				is_n_str(data->argve[id][*index] + 2))
			{
				break_line = 0;
				(*index)++;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (break_line);
}

static int	is_n_str(char *s)
{
	while (*s)
	{
		if (*s != 'n')
			return (FALSE);
		s++;
	}
	return (TRUE);
}
