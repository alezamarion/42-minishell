/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_n_unmask_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 22:18:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/02 22:22:25 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define UNCLOSED_QUOTES "Minishell: Sintaxe Error: Unclosed quotes `%c'\n"

char	*reverse_quotes_treat(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 3)
		{
			str[i] = '\'';
		}
		else if (str[i] == 2)
		{
			str[i] = '\"';
		}
		i++;
	}
	return (str);
}

void	unmask_character(char *cmd, int nbr, char c)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == nbr)
			cmd[i] = c;
		i++;
	}
}

/*
	Substitui os caracteres ' ', '>', '<', '|' e '$' por um não imprimível.
	E.g
	echo "'jorge ale"\0
	echo "'jorge1ale"\0
*/
int	mask_all_chars(t_data *data)
{
	if (mask_character(data->input, ' ', 1))
		return (FAILURE);
	mask_character(data->input, '|', 6);
	mask_character(data->input, '>', 4);
	mask_character(data->input, '<', 5);
	mask_dollar(data);
	return (SUCCESS);
}

int	mask_character(char *str, char c, int number)
{
	int	i;
	int	sign;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			sign = str[i++];
			while (str[i] != sign && str[i])
			{
				if (str[i] == c)
					str[i] = number;
				i++;
			}
			if (!str[i])
			{
				ft_printf(STDERR, UNCLOSED_QUOTES, sign);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}
