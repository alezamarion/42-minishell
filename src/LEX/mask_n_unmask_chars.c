/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_n_unmask_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 22:18:03 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/24 21:12:44 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	Replace characters ' ', '>', '<', '|' and '$' for a non-printable one.
*/
int	mask_all_chars(t_data *data)
{
	if (mask_character(data->input, ' ', 1))
	{
		g_status_code = SINTAX_ERR;
		return (FAILURE);
	}
	mask_character(data->input, '&', 8);
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
