/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_take_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:56:26 by ebresser          #+#    #+#             */
/*   Updated: 2022/05/24 21:20:00 by ebresser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *data)
{
	char	cwd[1024];
	char	*prompt_str;
	char	*username;

	username = getenv("USER");
	getcwd(cwd, sizeof(cwd));
	prompt_str = ft_mult_join(7, "\e[32m", username, ":", \
							"\e[35m", cwd, "\e[0m", "$ ");
	data->input = readline(prompt_str);
	free(prompt_str);
}

/** Function to take input - MALLOC input*/
int	take_input(t_data *data)
{
	prompt(data);
	if (!data->input)
		exit_minishell(data, SUCCESS);
	if (ft_strlen(data->input) != 0)
	{
		if (is_space_str(data->input))
			return (FAILURE);
		put_on_history(data->input, data->old_input);
		if (data->old_input)
			free(data->old_input);
		data->old_input = ft_strdup(data->input);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
