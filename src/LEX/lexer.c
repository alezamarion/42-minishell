/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima-nu <vlima-nu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/02 23:03:06 by vlima-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Create an aux **str based on pipe
void	pull_pipe(t_data *data)
{
	int		i;

	i = 0;
	data->cmds_piped = ft_split(data->input, '|');
	if (data->cmds_piped == NULL)
	{
		perror("Minishell: Malloc failed in pull_pipe: ");
		exit_minishell(data, FAILURE);
	}
	data->number_of_pipes = ft_str_count(data->cmds_piped) - 1;
	while (data->cmds_piped[i])
		unmask_character(data->cmds_piped[i++], 6, '|');
}

// Aqui ganha o formato da estrutura argve - Por isso n retorna,
// mexe direto na struct
void	pull_space(t_data *data)
{
	int		i;
	int		j;
	int		no_cmds;

	i = 0;
	no_cmds = data->number_of_pipes + 1;
	data->argve = (char ***)ft_calloc((no_cmds + 1), sizeof(char **));
	if (data->argve == NULL)
	{
		perror("Minishell: Malloc failed in pull_space ");
		exit_minishell(data, FAILURE);
	}
	while ((data->cmds_piped)[i])
	{
		data->argve[i] = ft_split((data->cmds_piped)[i], ' ');
		if (data->argve[i] == NULL)
		{
			perror("Minishell: Malloc failed in pull_space ");
			exit_minishell(data, FAILURE);
		}
		j = 0;
		while (data->argve[i][j])
			unmask_character(data->argve[i][j++], 1, ' ');
		i++;
	}
}

int	lexer(t_data *data)
{
	if (pull_quotes(data))
		return (FAILURE);
	pull_pipe(data);
	if (pull_redirects(data))
		return (FAILURE);
	pull_space(data);
	return (SUCCESS);
}
