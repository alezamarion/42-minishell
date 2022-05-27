/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:55:53 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 20:13:11 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create an aux **str based on pipe
int	pull_pipe(t_data *data)
{
	int		i;

	i = 0;
	while (data->input[i] == ' ')
		i++;
	if (data->input[i] == '|')
	{
		ft_printf(STDERR, "Minishell: syntax error near unexpected token `|'\n");
		return (FAILURE);
	}
	data->cmds_piped = ft_split(data->input, '|');
	if (data->cmds_piped == NULL)
	{
		perror("Minishell: Malloc failed in pull_pipe: ");
		exit_minishell(data, FAILURE);
	}
	data->number_of_pipes = ft_str_count(data->cmds_piped) - 1;
	while (data->cmds_piped[i])
		unmask_character(data->cmds_piped[i++], 6, '|');
	return (SUCCESS);
}

// Here it gets the format of the argve structure - That's why n returns,
// move directly in the struct
void	pull_space(t_data *data)
{
	int		i;
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
		i++;
	}
}

int	lexer(t_data *data)
{
	if (pull_quotes(data))
		return (FAILURE);
	if (pull_pipe(data))
		return (FAILURE);
	if (pull_redirects(data))
		return (FAILURE);
	pull_space(data);
	return (SUCCESS);
}
