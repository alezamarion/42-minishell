/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:03:07 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 21:19:49 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_id_cmd(t_data *data, int id, int up_to_token);
static void	pull_variables(t_data *data);

// functions for parsing command line
int	parser(t_data *data)
{
	data->exec_flag = (char *)ft_calloc(data->number_of_pipes + 1, \
		sizeof(char));
	pull_variables(data);
	return (SUCCESS);
}

static void	pull_variables(t_data *data)
{
	int		i;
	int		j;
	int		till_i;
	int		till_j;

	i = 0;
	till_i = -1;
	till_j = -1;
	while (data->argve[i])
	{
		j = 0;
		while (data->argve[i][j])
		{
			if (grab_vars(data, data->argve[i][j]))
			{
				data->exec_flag[i] = VAR_DEFINITION;
				till_i = i;
				till_j = j;
			}
			j++;
		}
		if (till_i != -1 && data->argve[till_i][till_j + 1])
			shift_id_cmd(data, till_i, till_j);
		i++;
	}
}

static void	shift_id_cmd(t_data *data, int id, int up_to_token)
{
	char	**aux;
	int		no_str;
	int		index;

	no_str = ft_str_count(data->argve[id]);
	aux = (char **)malloc(sizeof(char *) * (no_str - up_to_token));
	index = 0;
	while (index <= up_to_token)
		free(data->argve[id][index++]);
	index = 0;
	while (data->argve[id][++up_to_token])
	{
		aux[index] = ft_strdup(data->argve[id][up_to_token]);
		free(data->argve[id][up_to_token]);
		data->argve[id][up_to_token] = NULL;
		index++;
	}
	aux[index] = NULL;
	free(data->argve[id]);
	data->argve[id] = aux;
	data->exec_flag[id] = TRUE;
}
