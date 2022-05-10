/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:49:28 by vlima-nu          #+#    #+#             */
/*   Updated: 2022/05/02 22:01:17 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_dollar_sign(char c);
static int	is_quotes_or_space(char c);
static void	cut_dollar(t_data *data, int i);

void	mask_dollar(t_data *data)
{
	int	i;
	int	sign;

	i = -1;
	while (data->input[++i])
	{
		if (is_dollar_sign(data->input[i]))
			cut_dollar(data, i);
		if (data->input[i] == '\'' || data->input[i] == '\"')
		{
			sign = data->input[i++];
			while (data->input[i] != sign && data->input[i])
			{
				if ((is_dollar_sign(data->input[i]) && \
				(sign == '\'' || is_quotes_or_space(data->input[i + 1]))))
					data->input[i] = 7;
				i++;
			}
		}
	}
}

static void	cut_dollar(t_data *data, int i)
{
	int		j;

	if (!data->input[i + 1] || data->input[i + 1] == 1)
		data->input[i] = 7;
	else if (ft_strchr("\'\"@!*", data->input[i + 1]))
	{
		j = (ft_strchr("@!*", data->input[i + 1]) != 0);
		ft_strcut(&data->input, i, i + j + 1);
		i--;
	}
}

static int	is_dollar_sign(char c)
{
	return (c == '$');
}

static int	is_quotes_or_space(char c)
{
	return (ft_strchr("\'\"", c) || c == 1);
}
